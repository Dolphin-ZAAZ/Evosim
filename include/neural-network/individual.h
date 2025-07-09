#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "helper/helper.h"
#include "neural-network/network.h"

struct Individual {
    Network* network;
    sByte* genes;
    byte geneCount;
    byte species;
    byte fitness;

    byte actionCount;
    byte posX;
    byte posY;

    Individual() {}
    Individual(Network* net, byte speciesId, byte numGenes) : species(speciesId), geneCount(numGenes) {}
    Individual(const Individual& other) : species(other.species), geneCount(other.geneCount) {}
    ~Individual() {}

    void readGenes() {}
    void passGenes(sByte* passedGenes, byte mutationRate) {}
    sByte mutate(sByte gene, byte mutationRate) {}
    byte tick(byte* inputs) {}
    void reset() {}
};

#endif