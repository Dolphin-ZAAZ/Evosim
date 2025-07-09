#ifndef POPULATION_H
#define POPULATION_H

#include "helper/helper.h"
#include "neural-network/network.h"
#include "neural-network/species.h"

struct Population {
    byte speciesCount;
    byte individualCount;
    byte mutationRate;
    NetworkConfig netConfig;
    Species** species;

    Population(byte numSpecies, byte numIndividuals, NetworkConfig config, byte muteRate) : speciesCount(numSpecies), individualCount(numIndividuals), netConfig(config), mutationRate(muteRate) {
        species = new Species*[speciesCount];
        byte individualIndex = 0;
        for (byte i = 0; i < speciesCount; i++) {
            species[i] = new Species(i, netConfig, individualCount, mutationRate);
        }
    }
    ~Population() {
        for (byte i = 0; i < speciesCount; i++) {
            delete species[i];
        }
        delete[] species;
    }

    void nextGeneration() {
        for (int i = 0; i < speciesCount; i++) {
            species[i]->crossover();
        }
    }
};


#endif