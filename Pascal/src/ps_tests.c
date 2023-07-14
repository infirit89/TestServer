//
// Created by georg on 7/15/2023.
//

#include "ps_tests.h"

void queue_test()
{
    ps_queue queue;
    queue_init(&queue, 3);



    queue_free(&queue);
}