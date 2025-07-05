#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

typedef unsigned char uint8_t;
typedef signed char int8_t;
using byte = uint8_t;

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