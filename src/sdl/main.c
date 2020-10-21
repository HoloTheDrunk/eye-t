#include "image_load.h"
#include "convolution_matrix.h"
#include "otsu.h"
#include "types/matrix.h"
#include "types/tuple.h"
#include "hough_transform.h"
#include "autorotate.h"
#include "types/binary_tree.h"

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


    // IMAGE TREATMENT

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
    image_surface = auto_rotate(image_surface); 

    //matrix * test = image_to_matrix(image_surface, image_surface->w, image_surface->h);
    //Bounds_Detector(image_surface, image_surface->h, image_surface->w);
    //auto_rotate(image_surface);
    //Uint8 value = HoughTransform(test);

    //printf("WIDTH : %i  HEIGHT : %i \n", image_surface->w, image_surface->h);
    //printf("THE CORRECT VALUE : %i", value);
    //printMatrix(test);

    //screen_surface = display_image(image_surface);
    //screen_surface = display_image(auto_rotate(image_surface));

    image_surface = convolute(image_surface, gaussian_blur,
                ARRAYLEN(gaussian_blur));
    /*image_surface = convolute(image_surface, edge_detection,
                ARRAYLEN(edge_detection));*/

    screen_surface = display_image(image_surface);

    save_image(image_surface, "eye_t.bmp");

    wait_for_keypressed();

    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);

    return 0;
}
