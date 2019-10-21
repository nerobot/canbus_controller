/**
 * @file    cdf.h
 * @author  Steven Daglish
 * @version 0.1
 * @date    21 October 2019
 *
 * This header contains all the typedefs that will be project specific. These 
 * include id and command.
 * 
 */ 

#ifndef _HOME_CDF_H 
#define _HOME_CDF_H   

// For each of the enums below, a "xx_num_types" must be added at the end. This
// is used to check if the given command exists.

/**
 * @enum    id_t
 * @brief   Contains the id value of each node in the network
 */
typedef enum
{
    id_server,          ///< "Master" controller. Sends all data to / from the server via serial
    id_boiler_switch,   ///< Boiler switch. Will switch the boiler on / off as needed. exposes the unused io pins which could be put to use
    id_num_types,       ///< Must be kept at the end. Used to check if a given id is defined correctly
} id_t;

/**
 * @enum    command_t
 * @brief   Contains all the commands that can be sent over the canbus network
 */   
typedef enum
{
    command_no_command, ///< The default command. If this command is sent, then it means a command wasn't setup correctly
    command_switch_pin, ///< Switches a pin on / off
    command_num_types,  ///< Must be kept at the end. Used to check if a given id is defined correctly
} command_t;

#endif
