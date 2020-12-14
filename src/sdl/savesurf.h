#ifndef SAVESURF_H_
#define SAVESURF_H_

#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <png.h>


int png_colortype_from_surface(SDL_Surface *surface);

void png_user_warn(png_structp ctx, png_const_charp str);

void png_user_error(png_structp ctx, png_const_charp str);

int png_save_surface(char *filename, SDL_Surface *surf);
#endif
