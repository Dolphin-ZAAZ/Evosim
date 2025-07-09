#include "../include/neural-network/population.h"

Population::Population(byte numSpecies, byte numIndividuals, NetworkConfig config, byte muteRate) {
    species = new Species*[speciesCount];
    byte individualIndex = 0;
    for (byte i = 0; i < speciesCount; i++) {
        species[i] = new Species(i, netConfig, individualCount, mutationRate);
    }
}

Population::~Population() {
    for (byte i = 0; i < speciesCount; i++) {
        delete species[i];
    }
    delete[] species;
}

void Population::nextGeneration() {
    for (int i = 0; i < speciesCount; i++) {
        species[i]->crossover();
    }
}
