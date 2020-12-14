#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include "layer.h"
#include "Network.h"
#include "sdl_func.h"
#include "surface_binlist.h"
#include "pixel_operations.h"


#define nbimage 62

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


void InitNN(Network *self)
{
    initnet(self,784);
    add_layer(self,100);
    add_layer(self,127);
}


void TrainNN(Network *net)
{
    double **inputliste = malloc(62 * sizeof(double));
    init_sdl();
    for(int i = 0; i < 62; i++)
    {
        char name[50]="set/";
        char ch[10];
        sprintf(ch, "%d", res[i]);
        strcat(name, ch);
        strcat(name,"/0.jpg");
        puts(name);
        SDL_Surface* image_surface = load_image(name);
        int *image1 = surface_binlist(image_surface);
        double *image2 = malloc(784*sizeof(double));
        printf("\n");
        for(int j = 0; j < 784; j++)
        {
            image2[j]=image1[j];
        }
        inputliste[i]=image2;
    }

    train(net,inputliste,res,200,nbimage);
}


char GetCharNN(Network *net, Matrix* matrix)
{
    int* matrix_letter = matrix_binlist(matrix);
    double *image2 = malloc(784*sizeof(double));
    printf("\n");
    for(int j = 0; j < 784; j++)
    {
        image2[j]=matrix_letter[j];
    }

    double *out3 = calloc(net->input_dim, sizeof(double));
    char letter = (char)predict(net, image2, out3);

    printf("The prediction is : %c", letter);
    return letter;
}


int main()
{
    Network net;
    initnet(&net,784);
    add_layer(&net,100);
    add_layer(&net,127);

    SDL_Surface* image_surface;

    init_sdl();

    image_surface = load_image("set/108/0.jpg");


    TrainNN(&net);

    savestruct(&net, "struct");
    savenet(&net, "net");

    Matrix* matrix = Image_To_Matrix(image_surface, 28, 28);

    PrintMatrix(matrix);

    GetCharNN(&net, matrix);

    freeall(&net);
    return 0;
}
