#include "../include/neural-network/individual.h"

Individual::Individual() {
    fitness = 0;
}

Individual::Individual(Network* net, byte speciesId, byte numGenes) {
    network = new Network(*net);
    fitness = 0;
    actionCount = network->layerSizes[network->layerCount];
    readGenes();
}

Individual::Individual(const Individual& other) {
    network = new Network(*other.network);
    genes = new sByte();
    for (byte i = 0; i < geneCount; i++) {
        genes[i] = other.genes[i];
    }
    readGenes();
}

Individual::~Individual() {
    delete network;
    delete[] genes;
}

void Individual::readGenes() {
    byte geneIndex = 0;
    for (byte i = 0; i < network->layerCount; i++) {
        for (byte j = 0; j < network->weights[i]->rows*network->weights[i]->columns; j++) {
            genes[geneIndex] = network->weights[i]->data[j];
            geneIndex++;
        }
        for (byte j = 0; j < network->biases[i]->rows*network->biases[i]->columns; j++) {
            genes[geneIndex] = network->biases[i]->data[j];
            geneIndex++;
        }
    }
}

void Individual::passGenes(sByte* passedGenes, byte mutationRate) {
    byte geneIndex = 0;
    for (byte i = 0; i < network->layerCount; i++) {
        for (byte j = 0; j < network->weights[i]->rows*network->weights[i]->columns; j++) {
            sByte mutated = mutate(passedGenes[geneIndex], mutationRate);
            network->weights[i]->data[j] = mutated;
            geneIndex++;
        }
        for (byte j = 0; j < network->biases[i]->rows*network->biases[i]->columns; j++) {
            sByte mutated = mutate(passedGenes[geneIndex], mutationRate);
            network->biases[i]->data[j] = mutated;
            geneIndex++;
        }
    }
    reset();
}

sByte Individual::mutate(sByte gene, byte mutationRate) {
    if (rand_within(1000) < 500) {
        gene -= mutationRate;
    } else {
        gene += mutationRate;
    }
    return gene;
}

void Individual::tick(byte* inputs) {
    byte* outputs = new byte[actionCount];
    byte bestOutput = 0;
    byte outputIndex = 0;
    network->forward(inputs, outputs);
    for (byte i = 0; i < actionCount; i++) {
        if (outputs[i] > bestOutput) {
            bestOutput = outputs[i];
            outputIndex = i;
        }
    }
    executeOutput(outputIndex);
    delete[] outputs;
}

void Individual::executeOutput(byte outputId) {

}

void Individual::reset() {

}