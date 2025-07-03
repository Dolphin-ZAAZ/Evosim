#ifndef UNIVERSE_H
#define UNIVERSE_H

typedef unsigned char uint8_t;
typedef signed char int8_t;

using byte = uint8_t;

const short xDefaultSize = 480; // needs to be divisible by 4
const short yDefaultSize = 360; // needs to be divisible by 4

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
    short xSize = xDefaultSize/4;
    short ySize = yDefaultSize/4;
};

struct Cell {
    byte species;
    short id;
};

class Universe {
    public:
        Universe(UniverseProperties initial_properties);
        ~Universe();

        UniverseProperties properties;

        void tickUniverse();
        void spawnEnergy(short x, short y);
        void spawnCell(byte species, short x, short y);
    private:
        long long tick;
        byte speciesCount;
        short activeCells;
        Cell cells[6000];
        short space[xDefaultSize/4][yDefaultSize/4];
        PixelType readFromSpace(short x, short y);
        void changeSpace(PixelType type, short x, short y);
        void generateUniverse();
        void initialiseEnergy();
        void initialiseCells();
        void energyProductionFunction(long time);
        void updatePixel(short x, short y);
        byte noiseFunction();
};

#endif