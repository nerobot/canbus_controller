#ifndef _CANBUS_CONTROLLER_H
#define _CANBUS_CONTROLLER_H

#include <stdbool.h>
#include <stdint.h>
#include "mcp2515_driver.h"

#define MAX_ID      0x7FF

bool canbus_controller_init(uint16_t id);

uint16_t canbus_controller_get_device_id(void);

#endif // _CANBUS_CONTROLLER_H
