#ifndef NEURAL_H_
#define NEURAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include "layer.h"
#include "Network.h"
//#include "sdl_func.h"
#include "surface_binlist.h"
#include "../sdl/pixel_operations.h"


void InitNN(Network *network);

void TrainNN(Network *net);

char GetCharNN(Network *net, Matrix* matrix);

#endif
