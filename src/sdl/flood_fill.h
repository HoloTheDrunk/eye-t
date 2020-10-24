#ifndef FLOOD_FILL_H_
#define FLOOD_FILL_H_

#include "pixel_operations.h"

void flood_fill(SDL_Surface *surface, int x, int y, int oldcolor, int newcolor);
void fill_corners(SDL_Surface *surface, int oldcolor, int newcolor);
void fill_edges(SDL_Surface *surface, int oldcolor, int newcolor);

#endif
