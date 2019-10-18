# canbus_controller

## Device ID

0   home server
1   boiler switch

## Message structure

Byte    
0-1     command
2-6     params    


## Commands

0000    switch pin
            2-3     switch device id
            4       pin to switch
            5       on / off (1 = on, 0 = off)

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
    
