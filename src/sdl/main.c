#include "main.h"

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

    SDL_Surface* image_surface = NULL;
    SDL_Surface* screen_surface = NULL;

    init_sdl();

    for(int i = 1; i < argc; i++)
    {
        if(argv[i][0] == '-' && argv[i][1] != '-')
        {
            switch(argv[i][1])
            {
                case 'i':
                    if(i < argc-1)
                    {
                        image_surface = load_image(argv[i+1]);
                        i++;
                    }
                    else
                        errx(0, "-%c: Incorrect usage, check man.", argv[i][1]);
                    break;
                case 'o':
                    if(i < argc-1)
                    {
                        save_image(image_surface, argv[i+1]);
                        i++;
                    }
                    else
                        errx(0, "-%c: Incorrect usage, check man.", argv[i][1]);
                    break;
                case 'g':
                    if(image_surface != NULL)
                        greyscale(image_surface);
                    else
                        errx(0, "-%c: Incorrect usage, check man.", argv[i][1]);
                    break;
                case 'v':
                    if(image_surface != NULL)
                    {
                        greyscale(image_surface);
                        image_surface = Otsu_method(image_surface, 0);
                    }
                    else
                        errx(0, "-%c: Incorrect usage, check man.", argv[i][1]);
                    break;
                case 'r':
                    if(image_surface != NULL)
                        image_surface = auto_rotate(image_surface);
                    else
                        errx(0, "-%c: Incorrect usage, check man.", argv[i][1]);
                    break;
                case 'b':
                    if(image_surface != NULL)
                        image_surface = convolute(image_surface, gaussian_blur,
                                ARRAYLEN(gaussian_blur));
                    else
                        errx(0, "-%c: Incorrect usage, check man.", argv[i][1]);
                    break;
                case 'e':
                    if(image_surface != NULL)
                        image_surface = convolute(image_surface, edge_detection,
                                ARRAYLEN(edge_detection));
                    else
                        errx(0, "-%c: Incorrect usage, check man.", argv[i][1]);
                    break;
                case 'd':
                    if(image_surface != NULL)
                        screen_surface = display_image(image_surface);
                    else
                        errx(0, "-%c: Incorrect usage, check man.", argv[i][1]);
                    break;
                case 's':
                    if(image_surface != NULL)
                        SegmentationTest(image_surface);
                    else
                        errx(0, "-%c: Incorrect usage, check man.", argv[i][1]);
                    break;
                case 'c':
                    if(image_surface != NULL)
                        fill_edges(image_surface, 0, 255);
                    else
                        errx(0, "-%c: Incorrect usage, check man.", argv[i][1]);
                    break;
                default:
                    errx(1, "-%c: Invalid command, check man.", argv[i][1]);
            }
        }

    }
    image_surface = load_image(argv[1]);

    image_surface = Otsu_method(image_surface,0);
    //image_surface = auto_rotate(image_surface);

    //matrix * test = image_to_matrix(image_surface, image_surface->w, image_surface->h);
    //Bounds_Detector(image_surface, image_surface->h, image_surface->w);
    //auto_rotate(image_surface);
    //Uint8 value = HoughTransform(test);

    //printf("WIDTH : %i  HEIGHT : %i \n", image_surface->w, image_surface->h);
    //printf("THE CORRECT VALUE : %i", value);
    //printMatrix(test);
    //
    screen_surface = display_image(image_surface);
    //screen_surface = display_image(auto_rotate(image_surface));

    /*image_surface = convolute(image_surface, gaussian_blur,
                ARRAYLEN(gaussian_blur));
    *image_surface = convolute(image_surface, edge_detection,
                ARRAYLEN(edge_detection));*/

    SegmentationTest(image_surface);

    //screen_surface = display_image(image_surface);

    save_image(image_surface, "eye_t.bmp");

    wait_for_keypressed();

    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);

    return 0;
}
