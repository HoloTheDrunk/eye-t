#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include "layer.h"
#include "Network.h"
#include "../sdl/image_load.h"
#include "surface_binlist.h"
#include "../sdl/pixel_operations.h"


char GetCharNN(Network *net, Matrix* matrix);
void TrainNN(Network *net);
void InitNN(Network *network);

#endif
