#include "image_load.h"
#include "convolution_matrix.h"
#include "otsu.h"
#include "types/matrix.h"
#include "types/tuple.h"
#include "autorotate.h"
#include "types/binary_tree.h"
#include "segmentation.h"

#define ARRAYLEN(x) sizeof(x)/sizeof(x[0])

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        errx(0, "A file has to be specified.");
    }

    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;

    init_sdl();

    float gaussian_blur[] = {
        .0625, .125, .0625,
         .125,  .25,  .125,
        .0625, .125, .0625
    };

    /*float edge_detection[] = {
        -1,-1,-1,
        -1, 8,-1,
        -1,-1,-1
    };*/

    image_surface = load_image(argv[1]);

    image_surface = Otsu_method(image_surface);

    image_surface = convolute(image_surface, gaussian_blur,
                ARRAYLEN(gaussian_blur));

    screen_surface = display_image(image_surface);

    SegmentationTest(image_surface);

    save_image(image_surface, "eye_t.bmp");

    wait_for_keypressed();

    SDL_FreeSurface(image_surface);

    SDL_FreeSurface(screen_surface);

    return 0;
}
