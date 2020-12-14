#include "image_load.h"
#include "convolution_matrix.h"
#include "otsu.h"
#include "types/matrix.h"
#include "types/tuple.h"
#include "autorotate.h"
#include "types/binary_tree.h"
#include "segmentation.h"
#include "recons.h"
#include "../neuralnetwork/NeuralNetwork.h"
#define ARRAYLEN(x) sizeof(x)/sizeof(x[0])

#include <unistd.h>
#include <time.h>

time_t start, stop;
clock_t ticks;
double value;

SDL_Surface* Resize(SDL_Surface *img)
{
    SDL_Surface *dest = SDL_CreateRGBSurface(SDL_HWSURFACE,28,28,img->format->BitsPerPixel,0,0,0,0);
    SDL_SoftStretch(img, NULL, dest, NULL);
    return dest;
}


SDL_Surface* redImage(int w,int h,SDL_Surface* src)
{
    SDL_Surface* ret = SDL_CreateRGBSurface(src->flags,w,h,src->format->BitsPerPixel,
            src->format->Rmask,src->format->Gmask,src->format->Bmask,src->format->Amask);
    if (!ret)
        return src;
    SDL_BlitSurface(src,NULL,ret,NULL);
    SDL_FreeSurface(src);
    SDL_Surface* surface = SDL_DisplayFormatAlpha(ret);
    SDL_FreeSurface(ret);
    return surface;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        errx(0, "A file has to be specified.");
    }
    Network net;

    InitNetwork(&net,784);
    AddLayer(&net,100);
    AddLayer(&net,127);

    TrainNN(&net);


    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;

    init_sdl();

    image_surface = load_image(argv[1]);

    image_surface = Otsu_method(image_surface);

    screen_surface = display_image(image_surface);

    BinTree* bintree = Segmentation(image_surface);

    MatBT_Print(bintree);

    save_image(image_surface, "eye_t.bmp");



    int* matrix_letter = surface_binlist(image_surface);
    double *imgMatrix = malloc(784*sizeof(double));

    for(int j = 0; j < 784; j++)
        imgMatrix[j] = matrix_letter[j];

    double *output = calloc(net.input_dim, sizeof(double));
    char letter = (char)Predict(&net, imgMatrix, output);

    printf("The prediction is : %c\n", letter);
    return letter;

    //LeavesToChar(bintree, &net);

    printf("%s \n", Reconstruction(bintree));

    wait_for_keypressed();

    freeall(&net);
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);
    return 0;
}

