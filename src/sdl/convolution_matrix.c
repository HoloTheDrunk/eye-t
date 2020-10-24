#include "convolution_matrix.h"



SDL_Surface* convolute(SDL_Surface *source, float mask[], size_t maskLen)
{
    size_t width = source->w;
    size_t height = source->h;
    size_t maskSize = isqrt(maskLen);

    SDL_Surface* output = new_rgb_surface(width, height);

    for(size_t j = 0; j < height; j++)
    {
        for(size_t i = 0; i < width; i++)
        {
            Uint8 r = 0;
            Uint8 g = 0;
            Uint8 b = 0;

            for(size_t l = 0; l < maskSize; l++)
            {
                for(size_t k = 0; k < maskSize; k++)
                {
                    if(i+k > 0 && i+k < width && j+l > 0 && j+l < height)
                    {
                        Uint8 *rgb = get_rgb(source, i+k, j+l);
                        r += rgb[0] * mask[k * maskSize + l];
                        g += rgb[1] * mask[k * maskSize + l];
                        b += rgb[2] * mask[k * maskSize + l];
                    }
                }
            }
            put_pixel(output, i, j, SDL_MapRGB(output->format, r, g, b));
        }
    }
    return output;
}


int isqrt(int n)
{
    int r = n;
    while(r*r > n)
    {
        r = (r + n/r)/2;
    }
    return r;
}

