# canbus_controller

## Notes

A high level module for use with the lower level mcp2515_driver module. 

This module will control the creation of correct messages for transmission as well as decoding messages to obtain the correct commands.

The device IDs along with the command codes are stored in the header file. This will probably be moved to its own header file so that it can be saved in a similar way to a LIN LDF file. This will also allow the device ids to be project specific.

## Device ID

home server
boiler switch
office temperature sensor

## Message structure

Byte    
0-1     command
2-6     params    


## Commands

no command (used as default, incase nothing has been specified)
switch pin
            2-3     switch device id
            4       pin to switch
            5       on / off (1 = on, 0 = off)
temperature reading 
    2   msb
    3   lsb

## History

### v0.1

#### 17th October 2019

* First version creation and automated testing
* Transmission of data
    * Ability to send switch on / off commands to a given node
    * Only tx0 is currently in use. Tx1 will be implemented in future versions
    * TDD tested, but not system tested
    * Sending a command will automatically send the current devices ID as the message ID
    * Although the init function allows the user to enter the baudrate, this is not used. Instead, the default baudrate is 1000kbps
* Receiving data
    * Ablity to receive commands.
    * Does not convert the messages into any usable commands. At the moment, the user has to convert the messages into a usable command.
    * Transmission ID is stored when the message has been read
    * INT is setup in init, but it currently only works with rx0bf
    * Only rx0 is currently setup for use. rx1 will be implemented in future versions
    
### v0.2-decode_receive_command

#### 18th October 2019

* read_buff will decode the message, storing the msg command and the msg parameters in interal variables
* The above can be called via the appropraite get functions

### v0.3-clf_header_file_test

#### 21st October 2019

This branch is for testing the ability to have a separate header file that contains all the information about the nodes (devices) on the network as well as the commands that can be called and read.

At the moment, all the device ids and command codes are stored in the canbus header file which makes separating different projects difficult.

The file must be called cdf.h for this to work.

* For each project, find and change the cdf.h file as neede for the project.

### v0.4-change_baudrate_during_init

#### 1st November 2019

* mcp2515_driver branch "v0.1b-allowing_baudrate_changes_in_init" has been updated to have a baudrate parameter that is used to set the baudrate at setup.
* canbus_controller will now send its init baudrate value to the mcp init function, allowing the baudrate to be set during init.
    * Functionality added and unit tested.
* baudrate_t values brought in line with the values from mpc2515_driver module.

#### Breaking changes

* canbus_controller will now require a version of mcp2515_driver from v0.1b that contains a version of init that will take a parameter for the baudrate. Make will fail on older versions.

### v0.5-send_16bit-being_added

#### 19th November 2019

To be implemented

