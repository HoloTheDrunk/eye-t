#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "layer.h"
#include <time.h>

void Copy(double *tab, double *copy, int size)
{
    for(int i = 0; i < size; i++)
    {
        copy[i] = tab[i];
    }
}
void Mult(double *res, double A[], double B[], int inputSize, int size)
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < inputSize; j++)
        {
            res[i] += A[inputSize * i + j] * B[j];
        }
    }
}
void Add(double *res, double B[], int size)
{
    for(int j = 0; j < size; j++)
    {
        res[j] += B[j]; 
    }
}

double Sigmoid(double x)
{
    return 1/(1+exp(-x));
}

double Sigmoid_prime(double x)
{
    return Sigmoid(x) * (1 - Sigmoid(x)); 
}

void ComputeWeight(Layer *layer, double *input)
{
    int cols = layer->input_size;
    int rows = layer->size; 
    for(int i = 0; i < rows; i++)
    {
        double delta = layer->deltas[i]; 
        for(int j = 0; j < cols ; j++)
        {
            layer->weight[i * cols + j] += input[j]* delta * 0.1;
        }
        layer->bias[i] += delta;
        layer->deltas[i] = 0;
    }
}

void Aggregation(Layer *layer, double *input, int input_size, int size,\
        double *output)
{
    Mult(output, layer->weight, input, input_size, size);
    Add(output, layer->bias, size);
}

void ActivationPrime(double *output,int len)
{
    for(int i = 0; i < len; i++)
    {
        output[i] = Sigmoid_prime(output[i]);
    }
}

void Activation(double *output,int len)
{
    for(int i = 0; i < len; i++)
    {
        output[i] = Sigmoid(output[i]);
    }
}

void Forward(Layer *layer, double *input, double *output)
{
    ComputeWeight(layer, input);
    Aggregation(layer, input, layer->input_size, layer->size, output);
    Activation(output, layer->size);
}

void Init(Layer *layer, unsigned int size,int newSize)
{

    srand(time(NULL));
    layer->weight = calloc((size * newSize), sizeof(double));
    for(int i = 0; i < newSize;i++)
    {
        for(unsigned int j = 0; j < size; j++)
        {
            layer->weight[size * i + j] =(rand() / (double)RAND_MAX) * (-2) + 1;
        }
    }
    layer->size = size;
    layer->input_size = newSize;
    layer->bias = calloc(size,sizeof(double));
    layer->deltas = calloc(size,sizeof(double));
    layer->out = calloc(size,sizeof(double));
    for(unsigned int i = 0; i < size; i++)
        layer->bias[i] = (rand() / (double)RAND_MAX) * (-2) + 1;
}
