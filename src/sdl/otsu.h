#ifndef OTSU_H
#define OTSU_H


#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "pixel_operations.h"
#include <math.h>


SDL_Surface* Otsu_method(SDL_Surface* image);

void Get_Histo(SDL_Surface* image,
        unsigned long histo[256], int width, int height);

Uint8 Threshold_value(SDL_Surface* image, int width, int height);
SDL_Surface* Applying_Threshold(SDL_Surface* image, Uint8 threshold,
        int width, int height);

void Set_Histo_0(unsigned long histo[256]);

#endif
