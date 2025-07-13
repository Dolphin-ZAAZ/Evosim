#ifndef NETWORK_H
#define NETWORK_H

#include "helper/helper.h"
#include "neural-network/matrix.h"

struct NetworkConfig {
    byte inputs;
    byte count;
    byte* sizes;

    NetworkConfig ();
    NetworkConfig (byte in, byte count, byte size[]);
};

struct Network {
    byte layerCount;
    byte inputs;
    byte* layerSizes;
    Matrix** weights;
    Matrix** biases;
    
    ~Network();
    Network(byte in, byte count, byte* sizes);
    Network(const Network& other);
    Network& operator=(const Network& other);

    byte activate(int sum);
    void forward(byte* initial_input, byte* output);
};

#endif