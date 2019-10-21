/**
 * @file    canbus_controller.h
 * @author  Steven Daglish
 * @version 0.2
 * @date    October 2019
 *
 * @note    The correct "cdf" file will need to be included below. This will
 *          contain the device IDs and command codes.
 */ 

#ifndef _CANBUS_CONTROLLER_H
#define _CANBUS_CONTROLLER_H

#include <stdbool.h>
#include <stdint.h>
#include "mcp2515_driver.h"
#include "cdf.h"               

#define MAX_ID      0x7FF

// TODO Add all the possible baudrates below
typedef enum 
{
    br_5kbpm,
    br_num_types,
} baudrate_t;

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

command_t canbus_controller_get_receive_command(void);

void canbus_controller_get_receive_params(uint8_t* p_receive_param);

#endif // _CANBUS_CONTROLLER_H

