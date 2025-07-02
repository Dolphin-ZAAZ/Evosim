#ifndef UNIVERSE_H
#define UNIVERSE_H

enum class PixelType {
    Air,
    Energy,
    Cell
};

class Universe {
    public:
        Universe();
        ~Universe();
    private:
        int speciesCount;
        int speciesPopulation;
        int energyProductionFunction;
        int movementResistance;
        int decayIntensity;
        int metabolicResistance;
        int reproductiveResistance;
        int senseResistance;
        int speciationResistance;
        int sizeResistance;
        int temperature;
        int xAxis[480];
        int yAxis[360];
        void spawnPixel(PixelType type, int xPos, int yPos);
        void generateUniverse();
};

#endif