#ifndef SURFACE_BINLIST_H
#define SURFACE_BINLIST_H

#include <stdio.h>
#include "../sdl/image_load.h"
#include "../sdl/pixel_operations.h"
#include "../sdl/types/matrix.h"


int* surface_binlist(SDL_Surface* picture);
int* matrix_binlist(Matrix* matrix);


#endif
