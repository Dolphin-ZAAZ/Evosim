Structure:
    Universe (360x480)
        Properties:
            species count,
            species population,
            energy production structure,
            movement resistance,
            decay intensity,
            metabolic resistance,
            reproductive resistance,
            sense resistance,
            speciation resistance,
            size resistance,
            temperature
        Behaviour:
            spawns cells,
            wraps edges,
            provides energy

    Energy Pixels
        Constants:
            start value,
            start size,
            start lifetime,
            start consumption rate,
        Properties:
            value, 
            size, 
            consumption rate,
            lifetime
        Actions:
            die,
            absorb,
            grow

    Cell Pixels
        Constants:
            start movement difficulty,
            start energy level,
            start decay rate,
            start consumption difficulty,
            start metabolic rate,
            start cell typee,
            start sense type,
            start reproductive cost,
            start speciation rate,
            start sense range,
            start size cost
        Properties:
            cell type,
            movement difficulty,
            metabolic rate,
            energy level,
            decay rate,
            consumption difficulty,
            sense type,
            sense range,
            reproductive cost,
            speciation rate,
            size,
            size cost
        Actions:
            move,
            consume,
            reproduce,
            share,
            combine

Options for memory:

Track everything
2. 240 x 180 = 43 200 positions ~ 5 400 bytes * 2 = 10 800 bytes

Track only entities
Cell: byte type, short id = 3 bytes; 

Inputs:
    position, 2 bytes
    energy level, 2 byte
    sense food, 2 byte
    energy level, 2 byte
    sense mate, 2 byte
    energy level, 2 byte
    sense competition, 2 byte
    energy level, 2 byte

    Total: 16 bytes 

Hidden:
    Basic: 16x12+12+24, 12x8+8+16 8x4+4+8
              228          120     44         392
Outputs:
    up, 1 byte
    down, 1 byte 
    left, 1 byte
    right, 1 byte

    Total: 4 bytes
