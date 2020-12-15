#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_

#include <stdlib.h>
#include <SDL/SDL.h>
#include  <SDL/SDL_image.h>
#include "types/matrix.h"
#include "types/binary_tree.h"


int WhiteLine(Matrix* matrix, int y); //1
void SegmentationTest(SDL_Surface* image);//16
BinTree* Segmentation(SDL_Surface* image);
#endif
