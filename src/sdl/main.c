#include "image_load.h"
#include "convolution_matrix.h"
#include "otsu.h"
#include "types/matrix.h"
#include "types/tuple.h"
#include "autorotate.h"
#include "types/binary_tree.h"
#include "segmentation.h"
#include "recons.h"
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

    SDL_Surface* image_surface;
    //SDL_Surface* screen_surface;

    init_sdl();


    // IMAGE TREATMENT

    /*float gaussian_blur[] = {
        .0625, .125, .0625,
         .125,  .25,  .125,
        .0625, .125, .0625
    };
    *float edge_detection[] = {
        -1,-1,-1,
        -1, 8,-1,
        -1,-1,-1
    };*/

    image_surface = load_image(argv[1]);

    image_surface = Otsu_method(image_surface);
    //image_surface = auto_rotate(image_surface);
    BinTree* bin = NewBinTree(NULL);
    BinTree* bin_l = NewBinTree(NULL);
    BinTree* bin_r = NewBinTree(NULL);
    BinTree* bin_rr = NewBinTree(NULL);
    BinTree* bin_rl = NewBinTree(NULL);
    BinTree* bin_ll = NewBinTree(NULL);
    BinTree* bin_lr = NewBinTree(NULL);


    char* a = "";
    char* b = "";
    char* c = "l";
    char* d = ".";
    char* e = "e";
    char* f = "f";
    char* space = " ";

    bin->txt = space;

    bin_r->txt = b;
    bin_rl->txt = e;
    bin_rr->txt = f;

    bin_l->txt = a;
    bin_ll->txt = c;
    bin_lr->txt = d;


    bin_r->right = bin_rr;
    bin_r->left = bin_rl;
    bin_l->right = bin_lr;
    bin_l->left = bin_ll;


    bin->right = bin_r;
    bin->left = bin_l;

    printf("%s \n",Reconstruction(bin));
    //matrix * test = image_to_matrix(image_surface, image_surface->w, image_surface->h);
    //Bounds_Detector(image_surface, image_surface->h, image_surface->w);
    //auto_rotate(image_surface);
    //Uint8 value = HoughTransform(test);

    //printf("WIDTH : %i  HEIGHT : %i \n", image_surface->w, image_surface->h);
    //printf("THE CORRECT VALUE : %i", value);
    //printMatrix(test);
    //
    //screen_surface = display_image(image_surface);
    //screen_surface = display_image(auto_rotate(image_surface));

    /*image_surface = convolute(image_surface, gaussian_blur,
                ARRAYLEN(gaussian_blur));
    *image_surface = convolute(image_surface, edge_detection,
                ARRAYLEN(edge_detection));*/

    //SegmentationTest(image_surface);

    //screen_surface = display_image(image_surface);

    //save_image(image_surface, "eye_t.bmp");

    //wait_for_keypressed();

    //SDL_FreeSurface(image_surface);
    //SDL_FreeSurface(screen_surface);

    return 0;
}

