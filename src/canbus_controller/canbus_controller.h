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

bool canbus_controller_init(uint16_t id, baudrate_t br);

uint16_t canbus_controller_get_device_id(void);
baudrate_t canbus_controller_get_baudrate(void);

#endif // _CANBUS_CONTROLLER_H
