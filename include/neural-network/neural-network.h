#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

typedef unsigned char uint8_t;
typedef signed char int8_t;
using byte = uint8_t;
using sByte = int8_t;

struct Neuron {
    byte* weights;
    byte bias;
    short output;

    Neuron();
    Neuron(byte* old_weights, byte old_bias) : weights(old_weights), bias(old_bias) {
        weights = old_weights;
        bias = old_bias;
    }

    ~Neuron() {
        delete[] weights;
    }

    short activate(int sum) {
        byte shifted = (sum >> 16) & 0xFF;
        return shifted;
    }
};

struct Layer {
    Neuron* neurons;
    byte neuron_count;
    byte input_count;

    Layer();

    Layer(byte count) : neuron_count(count) {
        neurons = new Neuron[neuron_count];
    }

    Layer(Layer& old_layer) : neurons(old_layer.neurons), neuron_count(old_layer.neuron_count), input_count(old_layer.input_count) { }

    ~Layer() {
        delete[] neurons;
    }

    void forward(byte* inputs) {
        for (byte neuron = 0; neuron < neuron_count; neuron++) {
            int sum = neurons[neuron].bias;
            for (byte input = 0; input < input_count; input++) {
                sum += inputs[input] * neurons[neuron].weights[input];
            }
            neurons[neuron].output = neurons[neuron].activate(sum);
        }
    }
};

struct Matrix {
    sByte* data;
    byte rows;
    byte columns;

    Matrix(byte r, byte c) : rows(r), columns(c) {
        data = new sByte[rows * columns];
        for (int i = 0; i < rows * columns; i++) {
            data[i] = 0;
        }
    }

    ~Matrix() { delete[] data; }

    sByte& operator()(byte r, byte c) {
        return data[r * columns + c];
    }
};

struct Network {
    byte* layerSizes;
    byte layerCount;
    byte inputs;
    Matrix** weights;
    Matrix** biases;

    Network(byte in, byte sizes, byte* count) :  inputs(in), layerCount(sizes), layerSizes(count) {
        weights = new Matrix*[layerCount];
        biases = new Matrix*[layerCount];
        weights[0] = new Matrix(inputs, layerSizes[0]);
        biases[0] = new Matrix(1, layerSizes[0]);
        for (byte i = 1; i < layerCount; i++) {
            weights[i] = new Matrix(layerSizes[i-1], layerSizes[i]);
            biases[i] = new Matrix(1, layerSizes[i]);
        }
    }

    ~Network() {
        for (byte i = 0; i < layerCount; i++) {
            delete weights[i];
            delete biases[i];
        }
        delete[] weights;
        delete[] biases;
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
    byte fitness;
    Individual() {
        fitness = 0;
    }
    Individual(Network* net) : network(net) {
        fitness = 0;
    }
    ~Individual() {
        delete network;
    }
};

struct Population {
    Population();
    ~Population();
    void crossover(Network& netOne, Network& netTwo);
    void mutate(Network* net);
    void selectFitness(Network* net);
};

#endif