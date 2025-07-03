#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

/*
Inputs:
    position, 2 bytes
    movement difficulty, 1 byte
    metabolic rate, 1 byte
    energy level, 2 byte
    decay rate, 1 byte
    consumption difficulty, 1 byte
    sense food, 1 byte
    sense mate, 1 byte
    sense competition, 1 byte
    reproductive cost, 1 byte
    size, 1 byte
    size cost, 1 byte

    Total: 14 bytes

Hidden:
    Basic: 14x18, 14x9
            270     135     405
    Exploratory: 14x18, 18x24, 24x16, 16x9 
                    270     456     400     153     1279
Outputs:
    idle, 1 byte
    up, 1 byte
    down, 1 byte 
    left, 1 byte
    right, 1 byte
    consume, 1 byte
    reproduce, 1 byte
    share, 1 byte
    combine, 1 byte

    Total: 9 bytes
*/

#endif