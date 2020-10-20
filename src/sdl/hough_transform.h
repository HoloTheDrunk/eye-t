#ifndef HOUGH_TRANSFORM_H
#define HOUGH_TRANSFORM_H

#include "types/matrix.h"
#include <stdio.h>
#include <math.h>
#include "types/tuple.h"

Tuple* BlackPixel_to_List(matrix * mtx);
Uint8 HoughTransform(matrix * mtx);
void Put_Tuple(Tuple* parr, int x, int y);
#endif
