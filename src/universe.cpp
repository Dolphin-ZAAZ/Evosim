#include "../include/universe/universe.h"
#include "universe.h"

Universe::Universe(UniverseProperties initial_properties) : properties(initial_properties) {
    for(short x = 0; x < properties.xSize; x++) {
        for(short y = 0; y < properties.ySize; y++) {
            space[x][y] = 0;
        }
    }
    tick = 0;
}

void Universe::tickUniverse() {
    
}

void Universe::changeSpace(PixelType type, short x, short y) {
    short xRemainder = x % 4;
    short yRemainder = y % 4;
    short xChunk = x / 4;
    short yChunk = y / 4;
    short chunk = space[xChunk][yChunk];
}

void Universe::spawnEnergy(short x, short y) {
    space[x][y] = PixelType::Energy;
    updatePixel(x, y);
}

void Universe::spawnCell(byte species, short x, short y) {
    activeCells += 1;
    space[x][y] = PixelType::Cell;
    Cell cell;
    cell.species = species;
    cell.id = activeCells-1;
    cells[activeCells-1] = cell;
    updatePixel(x, y);
}

void Universe::generateUniverse() {
    initialiseEnergy();
    initialiseCells();
}

void Universe::initialiseEnergy()
{
    for (short x = 0; x < properties.xSize; x++) {
        for (short y = 0; y < properties.xSize; y++) {
            unsigned int noise = noiseFunction();
            if(noise < properties.energyDensity) {
                spawnEnergy(x, y);
            }
        }
    }
}

// Optimise this
void Universe::initialiseCells()
{
    short totalCellAmount = properties.initialSpeciesCount * properties.initialSpeciesPopulation;
    short noise[properties.xSize][properties.ySize];
    short xPositions[totalCellAmount];
    short yPositions[totalCellAmount];
    // create noise
    for (short x = 0; x < properties.xSize; x++) {
        for (short y = 0; x < properties.ySize; y++) {
            noise[x][y] = noiseFunction();
        }
    }
    // get maximum noise positions
    for (short pos = 0; pos < totalCellAmount; pos++){
        short xPos = 0;
        short yPos = 0;
        for (short x = 0; x < properties.xSize; x++) {
            for (short y = 0; y < properties.ySize; y++) {
                if (noise[x][y] >= noise[xPos][yPos]) {
                    xPos = x;
                    yPos = y;
                }
            }
        }
        noise[xPos][yPos] = 0;
        xPositions[pos] = xPos;
        yPositions[pos] = yPos;
    }
    //spawn pixels
    for (short i = 0; i < totalCellAmount; i++) {
        byte species = i % speciesCount;
        spawnCell(species, xPositions[i], yPositions[i]);
    }
}

byte Universe::noiseFunction() {
    unsigned int multiplier = 1664525;
    unsigned int incremenet = 1013904223;
    unsigned int modulus = 4294967296;
    unsigned int rnd = tick & 0xFFFF;
    unsigned int value = (multiplier * rnd + 1013904223) % modulus;
    return value & 0xFF;
}

void Universe::energyProductionFunction(long time) {
    short xPos = 0;
    short yPos = 0;
    for (short x = 0; x < properties.xSize; x++) {
        for (short y = 0; y < properties.ySize; y++) {
            if (noise[x][y] >= noise[xPos][yPos]) {
                xPos = x;
                yPos = y;
            }
        }
    }
    noise[xPos][yPos] = 0;
    xPositions[pos] = xPos;
    yPositions[pos] = yPos;
    for (short x = 0; x < properties.xSize; x++) {
        for (short y = 0; y < properties.xSize; y++) {
            unsigned int noise = noiseFunction();
            if(noise < properties.energyDensity) {
                spawnEnergy(x, y);
            }
        }
    }
}

void Universe::updatePixel(short x, short y) {
    PixelType type = space[x][y];
}