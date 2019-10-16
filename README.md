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

