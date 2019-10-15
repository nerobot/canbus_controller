#include "canbus_controller.h"

static uint16_t device_id = 0xFFFF;

bool canbus_controller_init(uint16_t id)
{
    if (id > MAX_ID)
    {
        return false;
    }
    device_id = id;
    return true;
}

uint16_t canbus_controller_get_device_id(void)
{
    return device_id;
}
