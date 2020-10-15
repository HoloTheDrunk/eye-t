#include "image_load.h"
#include "./types/matrix.h"




int main(int argc, char *argv[])
{
    if (argc < 2)
        errx(0, "A file has to be specified.");

	  SDL_Surface* image_surface;
    SDL_Surface* screen_surface;

    init_sdl();

    image_surface = load_image(argv[1]);
    screen_surface = display_image(image_surface);


    matrix * A;
    A = newMatrix(10,10);
    setElement(A, 1, 1, 1);
    setElement(A, 1, 2, 1);
    setElement(A, 1, 3, 1);

    printMatrix(A);
    //int width = image_surface->w;
    //int height = image_surface->h;

    /*IMAGE TREATMENT*/

    update_surface(screen_surface, image_surface);

    //save_image(image_surface, "eye_t.bmp");

    wait_for_keypressed();

    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);


    return 0;
}




