#ifndef NETWORK_H
#define NETWORK_H
#include "layer.h"

/*
    description of the functionality of the neural network 
    for more information contact me on git hub : Zorogo
    thank you 
    --Ziane
*/

//structure of the neuronal network
typedef struct Network
{
    //dimention of the image (juste the input exemple:2 for XOR)
	int input_dim;
    //number of layer
	int layers_dim;
    //liste of layer
	layer *layers; 
}Network;

//init the network
void initnet(Network *self,int input_dim);

//add layer with number of neurone
void add_layer(Network *self,int size);

//for load and save structure
void savestruct(Network *self,char *File);
void loadstruct(Network *self,char *File);
void savenet(Network *self,char *File);

//calcule the output liste of all the network
void feedforward(Network *self,double *input,double *out);

//BEST FUNCTION return the int of the char of the image in assci for the ocr
int predict(Network *self,double *input,double *out);

//evalue the efficacitie of the network with all the exemple
double evaluate(Network *self,double **inputlist,int *result,int sizeoflist);

//SECONDE BEST FUNCTION train the network with the exemple
void train(Network *self,double **inputlist,int *result,int step,int lenres);

//free all alloc on the network
void freeall(Network *self);

//print all the neurone (use for debug befor i discovers gdb)
void printnet(Network *self);
#endif
