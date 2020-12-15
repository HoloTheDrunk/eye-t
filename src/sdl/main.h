#ifndef MAIN_H_
#define MAIN_H_

#include "image_load.h"
#include "convolution_matrix.h"
#include "otsu.h"
#include "types/matrix.h"
#include "types/tuple.h"
#include "autorotate.h"
#include "types/binary_tree.h"
#include "segmentation.h"
#include "flood_fill.h"
#include "string_comparison.c"
#include "recons.h"

#include <unistd.h>
#include <time.h>
#include <libgen.h>

#define ARRAYLEN(x) sizeof(x)/sizeof(x[0])

float gaussian_blur[] = {
        .0625, .125, .0625,
         .125,  .25,  .125,
        .0625, .125, .0625
    };

float edge_detection[] = {
         0,-1, 0,
        -1, 5,-1,
         0,-1, 0
    };

#endif
