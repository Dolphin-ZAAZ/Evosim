#include "../include/neural-network/species.h"

Species::Species(byte speciesId, NetworkConfig netConfig, byte individualCount, byte mutationRange) {
    baseNetwork = new Network(netConfig.inputs, netConfig.count, netConfig.sizes);
    for (byte i = 0; i < baseNetwork->layerCount; i++) {
        for (byte j = 0; j < baseNetwork->weights[i]->rows*baseNetwork->weights[i]->columns; j++) {
            geneCount++;
        }
        for (byte j = 0; j < baseNetwork->biases[i]->rows*baseNetwork->biases[i]->columns; j++) {
            geneCount++;
        }
    }
    individuals = new Individual*[individualCount];
    for (byte i = 0; i < individualCount; i++) {
        individuals[i] = new Individual(baseNetwork, id, geneCount);
    }
}

Species::~Species() {
    delete baseNetwork;
    for (byte i = 0; i < numIndividuals; i++) {
        delete individuals[i];
    }
    delete[] individuals;
    delete[] genes;
}

void Species::crossover() {
    Individual cellOne = *selectFittest(0);
    Individual cellTwo = *selectFittest(1);
    for (byte i = 0; i < geneCount; i++) {
        if (rand_within(1000) < 500) {
            genes[i] = cellOne.genes[i];
        } else {
            genes[i] = cellTwo.genes[i];
        }
    }
    for (byte i = 0; i < numIndividuals; i++) {
        individuals[i]->passGenes(genes, mutationRate);
    }
}

Individual* Species::selectFittest(byte position) {
    Individual* fittest = individuals[0];
    Individual* secondFittest = individuals[1];
    if (position = 0) {
        for (byte i = 0; i < numIndividuals; i++) {
            if (individuals[i]->fitness > fittest->fitness) {
                fittest = individuals[i];
            }
        }
        return fittest;
    } else {
        for (byte i = 0; i < numIndividuals; i++) {
            if (individuals[i]->fitness > fittest->fitness) {
                fittest = individuals[i];
            }
        }
        for (byte i = 0; i < numIndividuals; i++) {
            if (individuals[i]->fitness < fittest->fitness && individuals[i]->fitness > secondFittest->fitness) {
                secondFittest = individuals[i];
            }
        }
        return secondFittest;
    }
    delete fittest;
    delete secondFittest;
}