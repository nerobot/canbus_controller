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

// TODO Check that the below define can be removed. All ID values should be stored
// in the cdf header file.
#define MAX_ID      0x7FF

// TODO Add all the possible baudrates below
typedef enum 
{
    br_5kbpm = 1,
    br_1000kbpm = 18,
    br_num_types,
} baudrate_t;

/**
 * Initalises both the canbus_controller and the mcp2515_driver modules.
 * @warning Init assumes that the SPI driver has already been set up.
 * @warning The init function does not yet use the baudrate. It is stored, but
 *          nothing is done with it.
 * TODO     Add functionality that checks and uses the baudrate that is sent via
 *          this init
 */ 
bool canbus_controller_init(uint16_t id, baudrate_t br);

uint16_t canbus_controller_get_device_id(void);

/**
 * @warning Function will return the baudrate provided in the init function, 
 *          which isn't currently used by the mcp2515 module.
 */
baudrate_t canbus_controller_get_baudrate(void);

bool canbus_controller_send_switch_on(id_t id);

bool canbus_controller_send_switch_off(id_t id);

bool canbus_controller_has_receive_data();

/**
 * Calls the mcp2515 to read the data from rx0.
 * @note    Only rx0 is currently set up to be used. Rx1 will be set up soon.
 */ 
bool canbus_controller_read_buf(void);

uint16_t canbus_controller_get_buf_from_id(void);

uint8_t canbus_controller_get_receive_msg_len(void);

void canbus_controller_get_receive_msg(uint8_t* receive_msg);

command_t canbus_controller_get_receive_command(void);

void canbus_controller_get_receive_params(uint8_t* p_receive_param);

/**
 * Sends a 16bit value as a temperature.
 *
 * The value will have no decoding done to it, so it will be necessary for the
 * receiving node to do something with the value (or just leave it and pass it
 * on as it is).
 *
 * @param 16bit value to be sent as the temperature
 * @warning No checks are done on the value and it will be sent out as it is.
 *
 */
bool canbus_controller_send_temperature(uint16_t temperature);

#endif // _CANBUS_CONTROLLER_H

