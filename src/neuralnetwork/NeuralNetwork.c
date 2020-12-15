#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include "layer.h"
#include "Network.h"
#include "sdl_func.h"
#include "surface_binlist.h"
#include "../sdl/pixel_operations.h"


#define nbImages 62

int res[] = {(int)'0', (int)'1', (int)'2', (int)'3', (int)'4', (int)'5',\
    (int)'6', (int)'7', (int)'8', (int)'9',\
        (int)'A', (int)'B', (int)'C',\
        (int)'D', (int)'E', (int)'F', (int)'G', (int)'H', (int)'I', (int)'J',\
        (int)'K', (int)'L', (int)'M', (int)'N', (int)'O', (int)'P', (int)'Q',\
        (int)'R', (int)'S', (int)'T', (int)'U', (int)'V', (int)'W', (int)'X',\
        (int)'Y', (int)'Z',\
        (int)'a', (int)'b', (int)'c',\
        (int)'d', (int)'e', (int)'f', (int)'g', (int)'h', (int)'i', (int)'j',\
        (int)'k', (int)'l', (int)'m', (int)'n', (int)'o', (int)'p', (int)'q',\
        (int)'r', (int)'s', (int)'t', (int)'u', (int)'v', (int)'w', (int)'x',\
        (int)'y', (int)'z'};


void InitNN(Network *network)
{
    InitNetwork(network,784);
    AddLayer(network,100);
    AddLayer(network,127);
}


void TrainNN(Network *net)
{
    double **inputList = malloc(62 * sizeof(double));
    init_sdl();
    for(int i = 0; i < 62; i++)
    {
        char name[50]="../neuralnetwork/set/";
        char ch[10];
        sprintf(ch, "%d", res[i]);
        strcat(name, ch);
        strcat(name,"/0.jpg");

        SDL_Surface* image_surface = load_image(name);
        int *image1 = surface_binlist(image_surface);
        double *image2 = malloc(784*sizeof(double));

        for(int j = 0; j < 784; j++)
            image2[j] = image1[j];
        inputList[i] = image2;
    }

    Train(net,inputList, res, nbImages);
}

char* letter;

char* GetCharNN(Network *net, Matrix* matrix)
{
    int* matrix_letter = matrix_binlist(matrix);
    double *imgMatrix = malloc(784*sizeof(double));

    for(int j = 0; j < 784; j++)
        imgMatrix[j] = matrix_letter[j];

    double *output = calloc(net->input_dim, sizeof(double));
    char tets = (char)Predict(net, imgMatrix, output);

    letter = &tets;

    // Why the fuck does this dereference the pointer?
    printf(" ");

    return letter;
}
