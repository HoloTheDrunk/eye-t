#ifndef LAYER_H
#define LAYER_H

typedef struct Layer
{
    int size;           //Number of neurons.
    int input_size;     //number of input (the prededente Layer result)
    
    //Lists of biases and weights.
    double *bias;
    double *weight;
    //Stocks deltas and outputs for the BackPropagation.
    double *deltas;
    double *out;
}Layer;

//Basic functions for matrix operations.
void Copy(double *tab, double *copy, int size);
void Mult(double res[], double A[], double B[], int inputSize, int size);
void Add(double res[], double B[], int size);

//Useful for activating.
double Sigmoid(double x);
double Sigmoid_prime(double x);

void Forward(Layer *layer, double *input, double *output);

//fonction agregation and activation
void Aggregation(Layer *layer, double *input, int input_size, int size,\
        double *output);
void Activation(double *output, int len);

//Initialises the layer.
void Init(Layer *layer, unsigned int size, int newSize);

//Computes the weights during BackPropagation.
void ComputeWeight(Layer *layer,double *input);

#endif
