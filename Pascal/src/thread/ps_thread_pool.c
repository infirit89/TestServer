// HEAVILY inspired by this post:  https://nachtimwald.com/2019/04/12/thread-pool-in-c/

/*
    Copyright John Schember <john@nachtimwald.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy of
    this software and associated documentation files (the "Software"), to deal in
    the Software without restriction, including without limitation the rights to
    use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
    of the Software, and to permit persons to whom the Software is furnished to do
    so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include "ps_thread_pool.h"
#include "ps_thread.h"

#include <stdlib.h>

struct ps_thread_pool_work
{
    ps_thread_pool_func fn;
    void* arg;
    struct ps_thread_pool_work* next;
};

typedef struct ps_thread_pool_work thread_pool_work;

struct ps_thread_pool
{
    thread_pool_work* first_work;
    thread_pool_work* last_work;
    ps_mutex mutex;
    ps_condition_variable work_cond;
    ps_condition_variable working_cond;
    ps_thread* threads;
    u32 working_count;
    u32 thread_count;
    u8 stop;
};

static thread_pool_work* _create_work(ps_thread_pool_func thread_func, void* arg)
{
    if(thread_func == NULL)
        return NULL;

    thread_pool_work* work = (thread_pool_work*)malloc(sizeof(thread_pool_work));
    work->fn = thread_func;
    work->arg = arg;
    work->next = NULL;
    return work;
}

static void _destroy_work(thread_pool_work* work)
{
    if(work == NULL)
        return;

    free(work);
}

static thread_pool_work* _get_first_work(ps_thread_pool* thread_pool)
{
    if(thread_pool == NULL)
        return NULL;

    thread_pool_work* work = thread_pool->first_work;
    if(!work)
        return NULL;

    if(work->next == NULL)
    {
        thread_pool->first_work = NULL;
        thread_pool->last_work = NULL;
    }
    else
        thread_pool->first_work = work->next;

    return work;
}

static void* _thread_pool_worker(void* arg)
{
    ps_thread_pool* thread_pool = arg;

    while(PS_TRUE)
    {
        ps_mutex_lock(&(thread_pool->mutex));

        while (thread_pool->first_work == NULL && !thread_pool->stop)
            ps_condition_variable_wait(&(thread_pool->work_cond), &(thread_pool->mutex));

        if(thread_pool->stop)
            break;

        thread_pool_work* work = _get_first_work(thread_pool);
        thread_pool->working_count++;
        ps_mutex_unlock(&(thread_pool->mutex));

        if(work != NULL)
        {
            work->fn(work->arg);
            _destroy_work(work);
        }

        ps_mutex_lock(&(thread_pool->mutex));
        thread_pool->working_count--;
        if(!thread_pool->stop && thread_pool->first_work == NULL)
            ps_condition_variable_wake(&(thread_pool->working_cond));
        ps_mutex_unlock(&(thread_pool->mutex));
    }

    thread_pool->thread_count--;
    ps_condition_variable_wake(&(thread_pool->working_cond));
    ps_mutex_unlock(&(thread_pool->mutex));

    return NULL;
}

ps_thread_pool* ps_thread_pool_create(u32 thread_num)
{
    ps_thread_pool* thread_pool = calloc(1, sizeof(ps_thread_pool));
    thread_pool->thread_count = thread_num;
    thread_pool->threads = calloc(thread_num, sizeof(ps_thread));

    ps_mutex_init(&(thread_pool->mutex));
    ps_condition_variable_init(&(thread_pool->work_cond));
    ps_condition_variable_init(&(thread_pool->working_cond));

    thread_pool->first_work = NULL;

    for (u32 i = 0; i < thread_num; ++i) {
        ps_thread_start(thread_pool->threads + i, _thread_pool_worker, thread_pool);
        ps_thread_detach(thread_pool->threads + i);
    }

    return thread_pool;
}

void ps_thread_pool_destroy(ps_thread_pool* thread_pool)
{
    if(thread_pool == NULL)
        return;

    ps_mutex_lock(&(thread_pool->mutex));
    thread_pool_work* work = thread_pool->first_work;
    thread_pool_work* temp;

    while (work)
    {
        temp = work->next;
        _destroy_work(work);
        work = temp;
    }

    thread_pool->stop = PS_TRUE;
    ps_condition_variable_wake_all(&(thread_pool->work_cond));
    ps_mutex_unlock(&(thread_pool->mutex));

    ps_thread_pool_wait(thread_pool);

    ps_mutex_destroy(&(thread_pool->mutex));
    ps_condition_variable_destroy(&(thread_pool->work_cond));
    ps_condition_variable_destroy(&(thread_pool->working_cond));

    free(thread_pool->threads);
    free(thread_pool);
}

void ps_thread_pool_stop(ps_thread_pool* thread_pool)
{
    ps_mutex_lock(&(thread_pool->mutex));
    thread_pool->stop = PS_TRUE;
    ps_condition_variable_wake_all(&(thread_pool->work_cond));
    ps_mutex_unlock(&(thread_pool->mutex));
}

u8 ps_thread_pool_add_work(ps_thread_pool* thread_pool, ps_thread_pool_func thread_func, void* arg)
{
    if(thread_pool == NULL)
        return PS_FALSE;

    thread_pool_work* work = _create_work(thread_func, arg);
    if(work == NULL)
        return PS_FALSE;

    ps_mutex_lock(&(thread_pool->mutex));
    if(thread_pool->first_work == NULL)
    {
        thread_pool->first_work = work;
        thread_pool->last_work = thread_pool->first_work;
    }
    else
    {
        thread_pool->last_work->next = work;
        thread_pool->last_work = work;
    }

    ps_condition_variable_wake_all(&(thread_pool->work_cond));
    ps_mutex_unlock(&(thread_pool->mutex));

    return PS_TRUE;
}

void ps_thread_pool_wait(ps_thread_pool* thread_pool)
{
    if(thread_pool == NULL)
        return;

    ps_mutex_lock(&(thread_pool->mutex));
    while(PS_TRUE)
    {
        if((!thread_pool->stop && thread_pool->working_count != 0) || (thread_pool->stop && thread_pool->thread_count != 0))
            ps_condition_variable_wait(&(thread_pool->working_cond), &(thread_pool->mutex));
        else
            break;
    }

    ps_mutex_unlock(&(thread_pool->mutex));
}
