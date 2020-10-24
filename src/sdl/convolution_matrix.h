#ifndef CONVOLUTION_MATRIX
#define CONVOLUTION_MATRIX

#include <stdlib.h>
#include <SDL/SDL.h>
#include "pixel_operations.h"

SDL_Surface* convolute(SDL_Surface *surface, float matrix[], size_t maskLen);
int isqrt(int n);

#endif
