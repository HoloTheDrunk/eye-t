#include "otsu.h"

SDL_Surface* Otsu_method(SDL_Surface* image)
{
    int width = image->w;
    int height= image->h;
    Uint8 threshold = Threshold_value(image, width, height);
    return Applying_Threshold(image, threshold, width, height);
}



Uint8 Threshold_value(SDL_Surface* image, int width, int height)
{
    Uint8 threshold =  0;
    //Uint8 threshold2 = 0;
    double nbrPixel = width * height;
    unsigned long histo[256];

    unsigned long sum = 0;
    unsigned long w1 = 0,w2 = 0;
    unsigned long m1 = 0,m2 = 0;
    float valence = 0.0f;
    unsigned long sumB = 0;
    unsigned long var_max = 0;


    Set_Histo_0(histo);
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
        if (w1 > nbrPixel)
            break;
        w2 = nbrPixel - w1;


        sumB += t*histo[t];
        m1 = sumB/w1;
        m2 = (sum-sumB)/w2;

        valence = w1*w2*(m1-m2)*(m1-m2);

        if (valence >= var_max)
        {
            threshold = t;
            if(valence > var_max)
                //threshold2 = t;
            var_max = valence;
        }
    }
    return threshold;
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

void Set_Histo_0(unsigned long histo[256])
{
    histo[0] = 1;
    for(int i = 1; i < 256; i++)
    {
        histo[i] = 0;
    }
}



void Get_Histo(SDL_Surface* image, unsigned long histo[256], int width,
        int height)
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
