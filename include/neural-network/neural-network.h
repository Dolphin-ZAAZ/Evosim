#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "../include/helper/helper.h"

typedef unsigned char uint8_t;
typedef signed char int8_t;
using byte = uint8_t;
using sByte = int8_t;

struct Matrix {
    sByte* data;
    byte rows;
    byte columns;

    ~Matrix() { delete[] data; }

    Matrix(byte r, byte c) : rows(r), columns(c) {
        data = new sByte[rows * columns];
        for (int i = 0; i < rows * columns; i++) {
            data[i] = 0;
        }
    }

    Matrix(const Matrix& other) : rows(other.rows), columns(other.columns) {
        data = new sByte[rows*columns];
        for (short i = 0; i < rows * columns; i++) {
            data[i] = other.data[i];
        }
    }

    Matrix& operator=(const Matrix& other) {
        if (this == &other) return *this;
        delete[] data;
        rows = other.rows;
        columns = other.columns;
        data = new sByte[rows*columns];
        for (byte i = 0; i < rows * columns; i++) {
            data[i] = other.data[i];
        }
        
    }

    sByte& operator()(byte r, byte c) {
        return data[r * columns + c];
    }

    sByte* getData() {
        return data;
    }
};

struct Network {
    byte layerCount;
    byte inputs;
    byte* layerSizes;
    Matrix** weights;
    Matrix** biases;

    
    ~Network() {
        delete[] layerSizes;
        for (byte i = 0; i < layerCount; i++) {
            delete weights[i];
            delete biases[i];
        }
        delete[] weights;
        delete[] biases;
    }
    
    Network(byte in, byte count, byte* sizes) :  inputs(in), layerCount(count) {
        layerSizes = new byte[layerCount];
        for (byte i = 0; i < layerCount; i++) {
            layerSizes[i] = sizes[i];
        }
        weights = new Matrix*[layerCount];
        biases = new Matrix*[layerCount];
        weights[0] = new Matrix(inputs, layerSizes[0]);
        biases[0] = new Matrix(1, layerSizes[0]);
        for (byte i = 1; i < layerCount; i++) {
            weights[i] = new Matrix(layerSizes[i-1], layerSizes[i]);
            biases[i] = new Matrix(1, layerSizes[i]);
        }
    }

    Network(const Network& other) : inputs(other.inputs), layerCount(other.layerCount) {
        layerSizes = new byte[layerCount];
        weights = new Matrix*[layerCount];
        biases = new Matrix*[layerCount];
        for (byte i = 0; i < layerCount; i++) {
            layerSizes[i] = other.layerSizes[i];
            weights[i] = new Matrix(*other.weights[i]);
            biases[i] = new Matrix(*other.biases[i]);
        }
    }

    Network& operator=(const Network& other) {
        if (this == &other) return *this;
        delete[] layerSizes;
        for (byte i = 0; i < layerCount; i++) {
            delete weights[i];
            delete biases[i];
        }
        delete[] weights;
        delete[] biases;
        layerCount = other.layerCount;
        inputs = other.inputs;
        layerSizes = new byte[layerCount];
        weights = new Matrix*[layerCount];
        biases = new Matrix*[layerCount];
        for (byte i = 0; i < layerCount; i++) {
            layerSizes[i] = other.layerSizes[i];
            weights[i] = new Matrix(*other.weights[i]);
            biases[i] = new Matrix(*other.biases[i]);
        }
    }

    byte activate(int sum) {
        if (sum <= 0) return 0;
        if (sum >= 2147483647) return 255;
        return (byte)((long long)sum * 255 / 2147483647);
    }
    
    void forward(byte* initial_input, byte* output) {
        byte** layerOutputs = new byte*[layerCount+1];
        layerOutputs[0] =  new byte[inputs];
        for (byte i = 0; i < inputs; i++) {
            layerOutputs[0][i] = initial_input[i];
        }
        for (byte layer = 0; layer < layerCount; layer++) {
            layerOutputs[layer+1] = new byte[layerSizes[layer]];
            for (byte neuron = 0; neuron < layerSizes[layer]; neuron++) {

                Matrix* layerWeights = weights[layer];

                int sum = (*biases[layer])(0, neuron);

                byte inputNeurons = (layer == 0) ? inputs : layerSizes[layer-1];
                for (byte input = 0; input < inputNeurons; input++) {
                    sum += layerOutputs[layer][input] * (*layerWeights)(input, neuron);
                }
                layerOutputs[layer+1][neuron] = activate(sum);
            }
        }

        for (byte i = 0; i < layerSizes[layerCount]; i++) {
            output[i] = layerOutputs[layerCount][i];
        }

        for (byte i = 0; i <= layerCount; i++) {
            delete[] layerOutputs[i];
        }
        delete[] layerOutputs;
    }
};

struct Individual {
    Network* network;
    byte species;
    byte fitness;
    Individual() {
        fitness = 0;
    }
    Individual(Network* net, byte speciesId) : network(net), species(speciesId) {
        fitness = 0;
    }
    ~Individual() {
        delete network;
    }
    void tick() {}
};

struct Population {
    byte speciesCount;
    byte individualCount;
    NetworkConfig netConfig;
    Species** species;

    Population(byte numSpecies, byte numIndividuals, NetworkConfig config) : speciesCount(numSpecies), individualCount(numIndividuals), netConfig(config) {
        species = new Species*[speciesCount];
        byte individualIndex = 0;
        for (byte i = 0; i < speciesCount; i++) {
            species[i] = new Species(i, netConfig, individualCount);
        }
    }
    ~Population() {
        for (byte i = 0; i < speciesCount; i++) {
            delete species[i];
        }
        delete[] species;
    }

    void crossover(Species& speciesOne, Network& speciesTwo) {

    }
    void mutate(Species passed_species);
    void selectFitness(Species* passed_species);
};

struct Species {
    byte id;
    byte numIndividuals;
    sByte* genes;
    Network* network;
    Individual** individuals;

    Species(byte speciesId, NetworkConfig netConfig, byte individualCount) : id(speciesId), numIndividuals(individualCount) {
        network = new Network(netConfig.inputs, netConfig.count, netConfig.sizes);
        individuals = new Individual*[individualCount];
        for (byte i = 0; i < individualCount; i++) {
            individuals[i] = new Individual(network, id);
        }
    }

    ~Species() {
        delete network;
        for (byte i = 0; i < numIndividuals; i++) {
            delete individuals[i];
        }
        delete[] individuals;
        delete[] genes;
    }

    sByte* readGenes() {
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
        return genes;
    }
};

struct NetworkConfig {
    byte inputs;
    byte count;
    byte* sizes;

    NetworkConfig () {
        inputs = 16;
        count = 4;
        sizes = new byte[4];
        sizes[0] = 12;
        sizes[1] = 8;
        sizes[2] = 4;
        sizes[3] = 8;
    }

    NetworkConfig (byte in, byte count, byte size[]) {
        inputs = in;
        count = count;
        sizes = new byte[count];
        for (byte i = 0; i < count; i++) {
            sizes[i] = size[i];
        }
    }
};

#endif