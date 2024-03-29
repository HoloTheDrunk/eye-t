#ifndef PIXEL_OPERATIONS_H_
#define PIXEL_OPERATIONS_H_

#include <stdlib.h>
#include <SDL/SDL.h>

Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y);
Uint8 get_v(SDL_Surface *surface, unsigned x, unsigned y);
Uint8* get_rgb(SDL_Surface *surface, unsigned x, unsigned y);

void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);

void update_surface(SDL_Surface* screen, SDL_Surface* image);

SDL_Surface* new_rgb_surface(int width, int height);

#endif
