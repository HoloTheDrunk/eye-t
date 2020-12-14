#ifndef LAYER_H
#define LAYER_H

/*
    description of the functionalality of the layer 
    its a matric implementation they are no structure of neuronne
    thank you 
    --ziane
*/

// structure of the layer (enjoy typdef befor inge1)
typedef struct layer
{
    //number of neurone
	int size;
    //number of input (the prededente layer result)
	int input_size;
    // liste of bias and weight
	double *bias;
	double *weight;
    //stock of the delta and output for the backpropagation
	double *deltas;
	double *out;
}layer;

// symple manipulation of matric and array
void copietab(double *tab,double *copie,int size);
void multmatric(double newtab[],double A[],double B[],int input_size,int size);
void addition(double newtab[],double B[],int size);

//for the activation
double sigmoid(double x);
double sigmoid_prime(double x);

//passage of layer i to i + 1
void forward(layer *self,double *input,double *output);

//fonction agregation and activation
void agreg(layer *self,double *input,int input_size,int size,double *output);
void activation(double *output,int len);

//init the layer at the begin of script
void init(layer *self,int newsize, int newinput_size);

//calcule weigth in the backpropagation with delta (the error)
void calculweigth(layer *self,double *input);

//print layer for debug att the begin becaus i dont now gdb befor 
void printlayer(layer *self);

#endif
