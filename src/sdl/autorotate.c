#include "autorotate.h"


SDL_Surface* auto_rotate(SDL_Surface* image)
{
    SDL_Surface* neuf = image;

    unsigned int first = 0;
    neuf = SDL_RotationCentralN(image, 1);
    Tuple tuple = Bounds_Detector(image,image->h,image->w);
    first = tuple.y - tuple.x;

    unsigned int second = 0;
    neuf = SDL_RotationCentral(image, 1);
    tuple = Bounds_Detector(image,image->h,image->w);
    second = tuple.y - tuple.x;

    Uint8 clockwise = first >= second;

    neuf = image;

    int Current_Length = 0;
    int Max_Length = 0;
    int angle = 0;

    while(Current_Length >= Max_Length && angle != 41)
    {
        printf("Current_Length : %i , Max_Length : %i", Current_Length, Max_Length);
        Max_Length = Current_Length;
        if (clockwise)
        {
            angle ++;
            neuf = SDL_RotationCentralN(neuf,1);
            Current_Length =  Bounds_Detector(neuf, neuf->h, neuf->w).y -  Bounds_Detector(neuf, neuf->h, neuf->w).x;
            printf("Current_Length 2 : %i \n", Current_Length);
        }
        else
        {

            angle--;
            neuf = SDL_RotationCentral(neuf,1);
            Current_Length =  Bounds_Detector(neuf, neuf->h, neuf->w).y -  Bounds_Detector(neuf, neuf->h, neuf->w).x;
        }
        printf("LEFT : %i RIGHT : %i \n", tuple.x, tuple.y); // LE CHAR LE PLUS A GAUCHE ET LE PLUS A DROITE
    }

    printf("\n %i",angle);
    //if (!clockwise)
    //    return SDL_RotationCentralN(image,angle+30);
    //return SDL_RotationCentral(image,angle);
   return neuf;
}


Tuple Bounds_Detector(SDL_Surface* image, unsigned height, unsigned width)
{
    unsigned int left = width;
    unsigned int right = width-1;

    Uint8 r,g,b;
    Uint32 pixel;

    for (unsigned int x = 0; x < width; x++)
    {
        for(unsigned int y = 0; y < height; y++)
        {
            pixel = get_pixel(image, x, y);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);

            if(r == 255 && g == 0 && b == 0) // A CHANGER
            {
                if(left == width)
                {
                    left = x;
                    right = x;
                }
                else
                {
                    right = x;
                }
            }
        }
    }
    Tuple tuple;
    tuple.x = left;
    tuple.y = right;
    return tuple;
}
