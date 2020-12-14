#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "layer.h"
#include <time.h>

/*
   the description of the global utilisation of the function is on the .h
   thank you
   --ziane
 */
void copietab(double *tab, double *copie,int row)
{
    for(int i=0; i<row; i++)
    {
        copie[i]=tab[i];
    }
}
void multmatric(double *newtab,double A[], double B[],int input_size,int size)
{
    for(int i=0; i < size;i++)
    {
        for(int k=0;k<input_size;k++)
        {
            newtab[i]+= A[input_size*i+k]*B[k];
        }
    }
}
void addition(double *newtab,double B[],int size)
{
    for(int j=0;j<size;j++)
    {
        newtab[j]+=B[j]; 
    }
}

double sigmoid(double x)
{
    return 1/(1+exp(-x));
}

double sigmoid_prime(double x)
{
    return sigmoid(x)*(1-sigmoid(x)); 
}

void calculweigth(layer *self,double *input)
{
    int  colone = self -> input_size;
    int  ligne = self -> size; 
    for(int i=0; i<ligne;i++)
    {
        double delta = self->deltas[i]; 
        for(int j=0; j<colone;j++)
        {
            self->weight[i*colone+j] += input[j]*delta*0.1;
        }
        self->bias[i]+=delta;
        self->deltas[i]=0;
    }
}

void agreg(layer *self,double *input,int input_size,int size,double *output)
{
    multmatric(output,self->weight,input,input_size,size);
    addition(output,self->bias,size);
}

void acticationprime(double *output,int len)
{
    for(int i = 0; i<len; i++)
    {
        output[i] = sigmoid_prime(output[i]);
    }
}

void activation(double *output,int len)
{
    for(int i = 0; i<len; i++)
    {
        output[i] = sigmoid(output[i]);
    }
}

void forward(layer *self,double *input,double *output)
{
    calculweigth(self,input);
    agreg(self,input,self->input_size,self->size,output);
    activation(output,self->size);
}

void init(layer *self,int newsize,int newinput_size)
{

    srand(time(NULL));
    self -> weight = calloc((newsize * newinput_size),sizeof(double));
    for(int i=0; i < newinput_size;i++)
    {
        for(int j=0;j<newsize;j++)
        {
            self -> weight[newsize*i+j] =(rand()/(double)RAND_MAX)*(-2)+1;
        }
    }
    self -> size = newsize;
    self -> input_size = newinput_size;
    self -> bias = calloc(newsize,sizeof(double));
    self -> deltas =  calloc(newsize,sizeof(double));
    self -> out = calloc(newsize,sizeof(double));
    for(int i=0; i< newsize;i++)
        self -> bias[i]=(rand()/(double)RAND_MAX)*(-2)+1;
}


void printlayer(layer *self)
{
    int x = self -> input_size;
    int y = self -> size;
    double* tab = self -> weight; 
    for(int i=0; i < x;i++)
    {
        for(int j=0;j< y;j++)
        {
            printf("%f    ",tab[y*i+j]);
        }
        printf("\n");
    }
}

