#include "../include/neural-network/network.h"

NetworkConfig::NetworkConfig() {
    inputs = 16;
    count = 4;
    sizes = new byte[4];
    sizes[0] = 12;
    sizes[1] = 8;
    sizes[2] = 4;
    sizes[3] = 8;
}

NetworkConfig::NetworkConfig(byte in, byte num, byte size[]) {
    inputs = in;
    count = num;
    sizes = new byte[count];
    for (byte i = 0; i < count; i++) {
        sizes[i] = size[i];
    }
}

Network::~Network() {
    delete[] layerSizes;
    for (byte i = 0; i < layerCount; i++) {
        delete weights[i];
        delete biases[i];
    }
    delete[] weights;
    delete[] biases;
}

Network::Network(NetworkConfig config) : inputs(config.inputs), layerCount(config.count) {
    layerSizes = new byte[layerCount];
    for (byte i = 0; i < layerCount; i++) {
        layerSizes[i] = config.sizes[i];
    }
    weights = new Matrix*[layerCount];
    biases = new Matrix*[layerCount];
    weights[0] = new Matrix(inputs, layerSizes[0]);
    biases[0] = new Matrix(1, layerSizes[0]);
    for (byte i = 1; i < layerCount; i++) {
        sByte* newWeights = new sByte[layerSizes[i-1]*layerSizes[i]];
        sByte* newBiases = new sByte[layerSizes[i]];
        for (byte j = 0; j < layerSizes[i-1]*layerSizes[i]; j++) {
            newWeights[j] = signed_rand_within(127);
        }
        for (byte j = 0; j < layerSizes[i]; j++) {
            newBiases[j] = signed_rand_within(127);
        }
        weights[i] = new Matrix(layerSizes[i-1], layerSizes[i], newWeights);
        biases[i] = new Matrix(1, layerSizes[i], newBiases);
    }
}

Network::Network(byte in, byte count, byte* sizes) : inputs(in), layerCount(count) {
    layerSizes = new byte[layerCount];
    for (byte i = 0; i < layerCount; i++) {
        layerSizes[i] = sizes[i];
    }
    weights = new Matrix*[layerCount];
    biases = new Matrix*[layerCount];
    weights[0] = new Matrix(inputs, layerSizes[0]);
    biases[0] = new Matrix(1, layerSizes[0]);
    for (byte i = 1; i < layerCount; i++) {
        sByte* newWeights = new sByte[layerSizes[i-1]*layerSizes[i]];
        sByte* newBiases = new sByte[layerSizes[i]];
        for (byte j = 0; j < layerSizes[i-1]*layerSizes[i]; j++) {
            newWeights[j] = signed_rand_within(127);
        }
        for (byte j = 0; j < layerSizes[i]; j++) {
            newBiases[j] = signed_rand_within(127);
        }
        weights[i] = new Matrix(layerSizes[i-1], layerSizes[i], newWeights);
        biases[i] = new Matrix(1, layerSizes[i], newBiases);
    }
}

Network::Network(const Network& other) : inputs(other.inputs), layerCount(other.layerCount) {
    layerSizes = new byte[layerCount];
    weights = new Matrix*[layerCount];
    biases = new Matrix*[layerCount];
    for (byte i = 0; i < layerCount; i++) {
        layerSizes[i] = other.layerSizes[i];
        weights[i] = new Matrix(*other.weights[i]);
        biases[i] = new Matrix(*other.biases[i]);
    }
}

Network& Network::operator=(const Network& other) {
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
    return *this;
}

byte Network::activate(int sum) {
    if (sum <= 0) return 0;
    if (sum >= 2147483647) return 255;
    return (byte)((long long)sum * 255 / 2147483647);
}

void Network::forward(byte* initial_input, byte* output) {
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