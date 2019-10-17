#ifndef _CANBUS_CONTROLLER_H
#define _CANBUS_CONTROLLER_H

#include <stdbool.h>
#include <stdint.h>
#include "mcp2515_driver.h"

#define MAX_ID      0x7FF

typedef enum 
{
    br_5kbpm,
    br_num_types,
} baudrate_t;

typedef enum
{
    id_server,
    id_boiler_switch,
    id_num_types,
} id_t;

bool canbus_controller_init(uint16_t id, baudrate_t br);

uint16_t canbus_controller_get_device_id(void);

baudrate_t canbus_controller_get_baudrate(void);

bool canbus_controller_send_switch_on(id_t id);

bool canbus_controller_send_switch_off(id_t id);

bool canbus_controller_has_receive_data();

bool canbus_controller_read_buf(void);

uint16_t canbus_controller_get_buf_from_id(void);

uint8_t canbus_controller_get_receive_msg_len(void);

void canbus_controller_get_receive_msg(uint8_t* receive_msg);
#endif // _CANBUS_CONTROLLER_H
