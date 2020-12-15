#include "main.h"
#include <gtk/gtk.h>

//#include "../neuralnetwork/NeuralNetwork.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        errx(0, "A file has to be specified.");
    }

    SDL_Surface* image_surface;
    //SDL_Surface* screen_surface;

    init_sdl();

    image_surface = load_image(argv[1]); // Load

    //image_surface = Otsu_method(image_surface, 0); // Otsu

    BinTree* bintree = Segmentation(image_surface); // Segmentation bintree

    MatBT_Print(bintree); // Print BinTree


    //=======================================//
    //                  IA
    //=======================================//


    Network net;

    InitNetwork(&net,784);
    AddLayer(&net,100);
    AddLayer(&net,127);

    TrainNN(&net);


    int* matrix_letter = surface_binlist(image_surface); // Directement l'image

    // ----------------------------------------------
    double *imgMatrix = malloc(784*sizeof(double));

    for(int j = 0; j < 784; j++)
        imgMatrix[j] = matrix_letter[j];

    double *output = calloc(net.input_dim, sizeof(double));
    char letter = (char)Predict(&net, imgMatrix, output);
    // ----------------------------------------------




    printf("The prediction is : %c\n", letter);

    LeavesToChar(bintree, &net);

    //printf("%s \n", Reconstruction(bintree));

    wait_for_keypressed();

    freeall(&net);
    SDL_FreeSurface(image_surface);
    //SDL_FreeSurface(screen_surface);
    return 0;
}

