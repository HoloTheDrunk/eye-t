#ifndef NETWORK_H
#define NETWORK_H
#include "layer.h"

typedef struct Network
{
    int input_dim;			//Dimention of the inputs. (Here, an image)
    int layers_dim;			//Number of layers wanted.
	Layer *layers;			//A list of all the layers for accessibility.
} Network;

//Initialises the Network with the number of inputs.
void InitNetwork(Network *network, int input_dim);

//Adds a new layer by specifying the number of neurons wanted.
void AddLayer(Network *network, int size);

//Computes the matching outputs to a specific set of inputs.
void ForwardPass(Network *network ,double *input, double *out);

//Returns the character matching to the inputs, according to the NN.
int Predict(Network *network, double *input, double *out);

//Computes how efficient the network currently is.
double Evaluate(Network *network, double **inputlist, int *result,\
		int sizeoflist);

//Trains the network according to the images given.
void Train(Network *network, double **inputlist, int *result, int nbImages);

//Free all the RAM used by the network.
void freeall(Network *network);

#endif
