#include "../include/universe/universe.h"
#include "universe.h"

Universe::Universe(UniverseProperties initial_properties) : properties(initial_properties) {
    for(short x = 0; x < properties.xSize; x++) {
        for(short y = 0; y < properties.ySize; y++) {
            space[x][y] = PixelType::Air;
        }
    }
}

void Universe::tick() {

}

void Universe::spawnPixel(PixelType type, short x, short y) {
    space[x][y] = type;
    updatePixel(x, y);
}

void Universe::generateUniverse() {
    for (short x = 0; x < properties.xSize; x++) {
        for (short y = 0; y < properties.xSize; y++) {
            int noise = noiseFunction(128);
            int adjustedValue = noise & 0xF;
            if(noise < properties.energyDensity) {
                spawnPixel(PixelType::Energy, x, y);
            }
        }
    }
}

int Universe::noiseFunction(byte seed) {
    int randomConstant = 1598;
    int value = (randomConstant * seed) & 0xF9D2FFFF;
    return value;
}

void Universe::energyProductionFunction(long time) {

}

void Universe::updatePixel(short x, short y) {
    PixelType type = space[x][y];
}