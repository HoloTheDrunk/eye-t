#include "image_load.h"
#include "convolution_matrix.h"
#include "otsu.h"
#include "types/matrix.h"
#include "types/tuple.h"
#include "hough_transform.h"
#include "autorotate.h"

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

    /*IMAGE TREATMENT


    /////////// LOOK HERE
    int gaussian_blur[3][3] = {
        { 1, 1, 0},
        { 1, 5, 0 },
        { 0, 1, 1 }
    };


    update_surface(screen_surface, image_preproc);*/
    /////////// NOW LOOK AT FUNCTION TYPES ON THE LEFT THEN AT CLI

    image_surface = load_image(argv[1]);
    SDL_SetColorKey(image_surface,SDL_SRCCOLORKEY,SDL_MapRGB(image_surface->format,255,255,255));
    //image_preproc = Otsu_method(image_surface);
    image_preproc = image_surface;
    //matrix * test = image_to_matrix(image_preproc, image_preproc->w, image_preproc->h);
    //
    auto_rotate(image_preproc);
    //Uint8 value = HoughTransform(test);

    //printf("WIDTH : %i  HEIGHT : %i \n", image_preproc->w, image_preproc->h);
    //printf("THE CORRECT VALUE : %i", value);
    //printMatrix(test);

    screen_surface = display_image(auto_rotate(image_preproc));

    save_image(image_preproc, "eye_t.bmp");

    wait_for_keypressed();

    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);


    return 0;
}
