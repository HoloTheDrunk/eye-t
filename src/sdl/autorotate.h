#ifndef AUTO_ROTATE_H_
#define AUTO_ROTATE_H_

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "rotation.h"
#include "pixel_operations.h"
#include "types/tuple.h"

Tuple Bounds_Detector(SDL_Surface* image, unsigned height, unsigned width);

SDL_Surface* auto_rotate(SDL_Surface* image);

#endif
