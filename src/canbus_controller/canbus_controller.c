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

bool canbus_controller_send_switch_on(id_t id)
{
    if (id >= id_num_types)
    {
        return false;
    }
    uint8_t message[] = {0, 0, (id_boiler_switch & 0x00FF), (id_boiler_switch >> 8), 0, 1};
    bool success = mcp2515_driver_send_msg_buffer(device_id, 0, 6, message);
    return success;
}

bool canbus_controller_send_switch_off(id_t id)
{    
    if (id >= id_num_types)
    {
        return false;
    }
    uint8_t message[] = {0, 0, (id_boiler_switch & 0x00FF), (id_boiler_switch >> 8), 0, 0};
    bool success = mcp2515_driver_send_msg_buffer(device_id, 0, 6, message);
    return success;
}


bool canbus_controller_has_receive_data()
{
    bool rx0_has_data = mcp2515_rx0_is_full();
    return rx0_has_data;
}
