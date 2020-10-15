#include "otsu.h"
#include "pixel_operations.h"
#include <stdio.h>
#include <math.h>

void Get_Histo(SDL_Surface* image, int histo[256], int width, int height);
Uint8 Threshold_value(SDL_Surface* image, int width, int height);
SDL_Surface* Applying_Threshold(SDL_Surface* image, Uint8 threshold,
        int width, int height);

SDL_Surface* Otsu_method(SDL_Surface* image)
{
    int width = image->w;
    int height= image->h;
    Uint8 threshold = Threshold_value(image, width, height);
    printf("%i", threshold);
    return Applying_Threshold(image, 127, width, height);
    //return image;
}



Uint8 Threshold_value(SDL_Surface* image, int width, int height)
{
    Uint8 threshold =  0;
    Uint8 threshold2 = 0;
    double nbrPixel = width * height;
    int histo[256];
    unsigned long sum = 0;
    unsigned long w1 = 0,w2 = 0;
    unsigned long m1 = 0,m2 = 0;
    float valence = 0.0f;
    unsigned long sumB = 0;
    unsigned long var_max = 0;
    // Weight, Mean, Variance : for the two class

    Get_Histo(image, histo, width, height);
    for(int i = 0; i < 256; i++)
    {
        sum +=  i*histo[i];
    }

    for(int t = 0; t < 256; t++)
    {
        w1 += histo[t];
        if (w1 == 0)
            continue;
        w2 = nbrPixel - w1;
        if (w2 == 0)
            break;

        sumB += t*histo[t];
        m1 = sumB/w1;
        m2 = (sum-sumB)/w2;

        valence = w1*w2*pow((m1-m2),2);

        if (valence >= var_max)
        {
            threshold = t;
            if(valence > var_max)
                threshold2 = t;
            var_max = valence;
        }
    }
    Uint8 result = (threshold +threshold2 /2);
    return result;
}


SDL_Surface* Applying_Threshold(SDL_Surface* image, Uint8 threshold
        , int width, int height)
{
    SDL_Surface* output = new_rgb_surface(width, height);
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            Uint8 r, g, b;
            Uint32 pixel = get_pixel(image, i, j);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            int greyscale = (r+g+b)/3;
            if (greyscale > threshold)
            {
                Uint32 pixel1 = get_pixel(image, i, j);
                pixel1 = SDL_MapRGB(output->format, 255, 255, 255);
                put_pixel(output, i, j, pixel1);
            }
            else
            {
                 Uint32 pixel1 = get_pixel(image, i, j);
                 pixel1 = SDL_MapRGB(output->format, 0, 0, 0);
                 put_pixel(output, i, j, pixel1);
            }
        }
    }
    return output;
}


void Get_Histo(SDL_Surface* image, int histo[256], int width, int height)
    // Getting the histo for all the pixels
{

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            Uint8 r, g, b;
            Uint32 pixel = get_pixel(image, i, j);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            int greyscale = (r+g+b)/3;
            histo[greyscale] += 1;
        }
    }
}