#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Network.h"


void InitNetwork(Network *network, int input_dim)
{
    network->input_dim = input_dim;
    network->layers_dim = 0;
    network->layers = calloc(network->layers_dim,sizeof(Layer));
}

void AddLayer(Network *network, int size)
{
    int input_dim = 0;
    if(network->layers_dim > 0)
        input_dim = network->layers[(network->layers_dim)-1].size;
	else
        input_dim = network->input_dim;

    network->layers_dim +=1;
    network->layers = realloc(network->layers,\
			(network->layers_dim) * sizeof(Layer));
    Layer newLayer;
    Init(&newLayer, size, input_dim);
    network->layers[(network->layers_dim) - 1] = newLayer;
}

void ForwardPass(Network *network, double *input, double *out)
{

    for(int i = 0; i < network->input_dim; i++)
    {
        out[i] = input[i];
    }

    for(int i = 0; i < network->layers_dim;i++)
    {

        int size = network->layers[i].size;
        double *output = calloc(size, sizeof(double));

        Forward(&(network->layers[i]), out, output);

        out = realloc(out, size * sizeof(double));
        for(int j = 0; j < size; j++)
        {
            out[j] = output[j];
            network->layers[i].out[j] = output[j];
        }
        free(output);
    }
    free(out);
}

int Predict(Network *network,double *input,double *out)
{
    ForwardPass(network,input,out);

    Layer finalLayer = network->layers[network->layers_dim-1];
    int size = finalLayer.size;

    int maxIndex = 0;
    double max = finalLayer.out[0];

    for(int i = 0; i < size; i++)
    {
        if(max < finalLayer.out[i])
        {
            maxIndex = i;
            max = finalLayer.out[i];
        }
    }

   return maxIndex;
}

double Evaluate(Network *network,double **inputlist,int *result,int sizeoflist)
{
    double sum = 0;
    for(int i = 0; i < sizeoflist; i++)
    {
        double *out = calloc(network->input_dim, sizeof(double));
        if(Predict(network, inputlist[i], out) == result[i])
        {
            sum += 1;
        }
    }
    return sum / (double)sizeoflist;
}


void Train(Network *network, double **inputlist, int *result, int nbImages)
{
    double max = 0;
    double currAccuracy;
    do
    {
        double resEval = Evaluate(network, inputlist, result, nbImages);
        if(resEval > max)
            max = resEval;

        currAccuracy = resEval * 100;

        for(int j = 0; j < nbImages; j++)
        {
            int trainingIsSufficient = 0;
            int maxIndex;
            Layer *layersList = network->layers;
            Layer finalLayer = layersList[network->layers_dim-1];
            double inputDim = network->input_dim;

            do
            {
                //Computes the error of every output.
                double *currOutputValue = calloc(inputDim,sizeof(double));
                maxIndex = Predict(network, inputlist[j], currOutputValue);

                //Computing errors.
                double* finalLayerOutput = finalLayer.out;
                int sizeOutputLayer = layersList[network->layers_dim-1].size;
                double *error = calloc(sizeOutputLayer, sizeof(double));
                error[result[j]] = 1;

                for(int k = 0; k < sizeOutputLayer; k++)
                {
                    error[k] -= finalLayerOutput[k];
                    finalLayer.deltas[k]= error[k];
                }
                free(error);

                //BackPropagation.
                for(int currLayer = network->layers_dim-2; currLayer >= 0;\
						currLayer--)
                {
                    Layer l = layersList[currLayer];
                    Layer b = layersList[currLayer+1];
                    int size = layersList[currLayer].size;
                    for(int index = 0; index < size; index++)
                    {
                        //Computes delta values.
                        double sumWeightsDeltas = 0;
                        double currOutput = l.out[index];
                        for(int all=0;all<size;all++)
                        {
                             double currWeight = b.weight[all * size + index];
                             double delta = b.deltas[index];
                             sumWeightsDeltas += currWeight * delta;
                        }
                        l.deltas[index] = currOutput * (1-currOutput) *\
										  sumWeightsDeltas;
                    }
                }
                double *out2 = calloc(inputDim, sizeof(double));
                maxIndex = Predict(network, inputlist[j], out2);
                trainingIsSufficient =! (result[j] == maxIndex);
            } while(trainingIsSufficient);
        }
    } while (currAccuracy < 97);
}


void freeall(Network *network)
{
    for(int i=0; i < (network->layers_dim); i++)
    {
        free(network->layers[i].bias);
        free(network->layers[i].weight);
        free(network->layers[i].deltas);
        free(network->layers[i].out);
    }
    free(network->layers);
}
