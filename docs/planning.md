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