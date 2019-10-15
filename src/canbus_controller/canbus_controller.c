#include "canbus_controller.h"

static uint16_t device_id = 0xFFFF;
static baudrate_t device_baudrate = br_num_types;

bool canbus_controller_init(uint16_t id, baudrate_t br)
{
    if (id > MAX_ID)
    {
        return false;
    }
    device_id = id;

    if (br >= br_num_types)
    {
        return false;
    }
    device_baudrate = br;

    bool success = mcp2515_init();

    return success;

}

uint16_t canbus_controller_get_device_id(void)
{
    return device_id;
}

baudrate_t canbus_controller_get_baudrate(void)
{
    return device_baudrate;
}
