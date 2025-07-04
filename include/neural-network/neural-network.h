#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

typedef unsigned char uint8_t;
typedef signed char int8_t;

using byte = uint8_t;

struct Neuron {
    byte* weights;
    byte bias;
    short output;
    byte input_count;

    byte activate(byte sum) {
        
    }
};

struct Layer {
    Neuron* neurons;
    byte neuron_count;

};


struct Network {
    public:
        Network();
        ~Network();
        byte infer();
    private:
};

struct Population {

};

#endif