#ifndef UNIVERSE_H
#define UNIVERSE_H

typedef unsigned char uint8_t;
typedef signed char int8_t;

using byte = uint8_t;

const short xDefaultSize = 480;
const short yDefaultSize = 360;

enum class UniverseSize {
    Small,
    Medium,
    Large
};

enum class PixelType {
    Air,
    Energy,
    Cell
};

struct UniverseProperties {
    byte initialSpeciesCount = 4;
    byte initialSpeciesPopulation = 20;
    byte movementResistance = 128;
    byte decayIntensity = 128;
    byte metabolicResistance = 128;
    byte reproductiveResistance = 128;
    byte senseResistance = 128;
    byte speciationResistance = 128;
    byte sizeResistance = 128;
    byte temperature = 128;
    byte energyDensity = 128;
    short xSize = xDefaultSize;
    byte ySize = yDefaultSize;
};

class Universe {
    public:
        Universe(UniverseProperties initial_properties);
        ~Universe();

        UniverseProperties properties;

        void tick();
        void spawnPixel(PixelType type, short x, short y);
    private:
        byte speciesCount;
        PixelType space[xDefaultSize][yDefaultSize];
        void generateUniverse();
        void energyProductionFunction(long time);
        void updatePixel(short x, short y);
        int noiseFunction(byte seed);
};

#endif