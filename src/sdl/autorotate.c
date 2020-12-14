#include "autorotate.h"
#include "image_load.h"

SDL_Surface* auto_rotate(SDL_Surface* image)
{
    SDL_Surface* neuf = image;

    unsigned int first = 0;
    neuf = SDL_RotationCentralN(image, 20);
    first =  Bounds_Detector(neuf, neuf->h, neuf->w).y -
        Bounds_Detector(neuf, neuf->h, neuf->w).x;


    unsigned int second = 0;
    neuf = SDL_RotationCentral(image, 20);
    second =  Bounds_Detector(neuf, neuf->h, neuf->w).y -
        Bounds_Detector(neuf, neuf->h, neuf->w).x;


    Uint8 clockwise = first < second;
    clockwise = 1;
    neuf = image;

    int Current_Length = image->w;
    int Previous_Length = image->w+1;
    int angle = 0;
    while(Current_Length <  Previous_Length)
    {
        Previous_Length = Current_Length;
        if (clockwise)
        {
            angle ++;
            neuf = SDL_RotationCentralN(image,angle);
            Tuple tuple =  Bounds_Detector(neuf, neuf->h, neuf->w);
            Current_Length =  tuple.y -  tuple.x;
        }
        else
        {
            angle--;
            neuf = SDL_RotationCentral(image,angle);
            Tuple tuple =  Bounds_Detector(neuf, neuf->h, neuf->w);
            Current_Length =  tuple.y -  tuple.x;
        }
    }

    if (!clockwise)
        return SDL_RotationCentralN(image,angle);
    return SDL_RotationCentral(image,angle-1);
}



Tuple Bounds_Detector(SDL_Surface* image, unsigned height, unsigned width)
{
    unsigned int left = 0;
    unsigned int right = 0;

    Uint8 r,g,b;
    Uint32 pixel;

    for (unsigned int x = 0; x < width; x++)
    {
        if (left != 0)
            break;
        for(unsigned int y = 0; y < height; y++)
        {
            pixel = get_pixel(image, x, y);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);

            if(r  == 255 && g == 0 && b == 0 )
            {
                left = x;
                break;
            }
        }
    }

    for (int x = width-1; x > 0; x--)
    {
        if (right != 0)
            break;
        for(int y = height-1; y > 0; y--)
        {
            pixel = get_pixel(image, x, y);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);

            if(r  == 255 && g == 0 && b == 0 )
            {
                right = x;
                break;
            }
        }
    }

    for (unsigned int y = 0; y < height; y++)
    {
        Uint32 leftPixel = get_pixel(image, left, y);
        Uint32 rightPixel = get_pixel(image, right, y);
        leftPixel = SDL_MapRGB(image->format, 0, 255, 0);
        rightPixel = SDL_MapRGB(image->format, 0, 255, 0);
        put_pixel(image, left, y, leftPixel);
        put_pixel(image, right, y, rightPixel);
    }

    Tuple tuple;
    tuple.x = left;
    tuple.y = right;
    return tuple;
}
