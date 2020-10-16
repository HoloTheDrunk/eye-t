#include "image_load.h"
#include "convolution_matrix.h"
#include "otsu.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        errx(0, "A file has to be specified.");
    }

    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;
    SDL_Surface* image_preproc;
    init_sdl();

    //int width = image_surface->w;
    //int height = image_surface->h;

    //IMAGE TREATMENT

    int gaussian_blur[3][3] = {
        { 1, 2, 1 },
        { 2, 4, 2 },
        { 1, 2, 1 }
    };

    int edge_detection[3][3] = {
        { 1, 1, 0 },
        { 1, 0, 0 },
        { 0, 0,-2 }
    };

    image_surface = 
        convolute(
            convolute(load_image(argv[1]), gaussian_blur),
            edge_detection);

    image_preproc = image_surface;//Otsu_method(image_surface);

    screen_surface = display_image(image_preproc);

    save_image(image_preproc, "eye_t.bmp");

    wait_for_keypressed();

    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);
    SDL_FreeSurface(image_preproc);

    return 0;
}
