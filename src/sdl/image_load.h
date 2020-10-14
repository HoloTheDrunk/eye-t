#ifndef IMAGE_LOAD_H
#define IMAGE_LOAD_H


#include <stdlib.h>
#include <SDL/SDL.h>
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include <err.h>

void init_sdl();
SDL_Surface* load_image(char *path);
int save_image(SDL_Surface* img, char *path);
SDL_Surface* display_image(SDL_Surface *img);
void greyscale(SDL_Surface *img);
void wait_for_keypressed();
void SDL_FreeSurface(SDL_Surface *surface);


#endif
