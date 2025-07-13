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

    Population(byte numSpecies, byte numIndividuals, NetworkConfig config, byte muteRate);
    ~Population();

    void nextGeneration();
};

#endif