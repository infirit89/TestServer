//
// Created by georg on 7/17/2023.
//

#include "ps_event_manager_tests.h"

#include "../../src/ps_event_manager.h"
#include "../../src/ps_log.h"

static void event_listener(ps_event event)
{
    PS_TRACE("on exit event");
}

void ps_event_manager_test_1()
{
    ps_log_init("Test");

    ps_event_manager event_manager;

    event_manager_init(&event_manager);

    event_manager_add_listener(&event_manager, PS_EVENT_TYPE_EXIT, event_listener);
    ps_event event =
    {
        .event_type = PS_EVENT_TYPE_EXIT
    };

    event_manager_push_event(&event_manager, event);

    event_manager_dispatch_events(&event_manager);

    event_manager_shutdown(&event_manager);

    ps_log_shutdown();
}
