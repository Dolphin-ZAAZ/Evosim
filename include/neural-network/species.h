#ifndef SPECIES_H
#define SPECIES_H

#include "helper/helper.h"
#include "neural-network/network.h"
#include "neural-network/individual.h"

struct Species {
    byte id;
    byte numIndividuals;
    byte geneCount;
    byte mutationRate;
    sByte* genes;
    Network* baseNetwork;
    Individual** individuals;

    Species(byte speciesId, NetworkConfig netConfig, byte individualCount, byte mutationRange);
    ~Species();

    void crossover();
    Individual* selectFittest(byte position);
};

#endif