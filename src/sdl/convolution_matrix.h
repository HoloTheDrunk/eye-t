#ifndef CONVOLUTION_MATRIX
#define CONVOLUTION_MATRIX

#include <stdlib.h>
#include <SDL/SDL.h>
#include "pixel_operations.h"

SDL_Surface* convolute(SDL_Surface *surface, float matrix[], size_t maskLen);
int isqrt(int n);
//int matrix_sum(int matrix[][3]);
//Uint32* apply_kernel(Uint8 source[], Uint32 destination[], int kernel_value);

#endif
