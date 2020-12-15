#ifndef NN_H_
#define NN_H_

#include <stdio.h>
#include "Network.h"
#include<stdlib.h>
#include "../sdl/types/matrix.h"
#include "surface_binlist.h"

void InitNN(Network *network);
void TrainNN(Network *net);
char* GetCharNN(Network *net, Matrix* matrix);

#endif
