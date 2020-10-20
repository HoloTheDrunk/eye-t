#include "image_load.h"
#include "convolution_matrix.h"
#include "otsu.h"
#include "types/matrix.h"
#include "types/tuple.h"
#include "hough_transform.h"
#include "autorotate.h"
#include "types/binary_tree.h"

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

<<<<<<< HEAD
    update_surface(screen_surface, image_preproc);*/
    /////////// NOW LOOK AT FUNCTION TYPES ON THE LEFT THEN AT CLI

    image_surface = load_image(argv[1]);
    image_preproc = Otsu_method(image_surface);
    //image_preproc = image_surface;
    //matrix * test = image_to_matrix(image_preproc, image_preproc->w, image_preproc->h);
    //Bounds_Detector(image_preproc, image_preproc->h, image_preproc->w);
    //auto_rotate(image_preproc);
    //Uint8 value = HoughTransform(test);

    //printf("WIDTH : %i  HEIGHT : %i \n", image_preproc->w, image_preproc->h);
    //printf("THE CORRECT VALUE : %i", value);
    //printMatrix(test);

    //screen_surface = display_image(image_preproc);
=======
    image_surface = 
        convolute(
            convolute(load_image(argv[1]), gaussian_blur),
            edge_detection);

    image_preproc = image_surface;//Otsu_method(image_surface);
>>>>>>> 15e77b6f0dc377b9b731a7a88e62c4097ce8997c

    screen_surface = display_image(auto_rotate(image_preproc));

    save_image(image_preproc, "eye_t.bmp");

    wait_for_keypressed();

    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);
    SDL_FreeSurface(image_preproc);

    return 0;
}
