#ifndef RECONS_H_
#define RECONS_H_

#include <stdio.h>
#include <stdlib.h>
#include "types/binary_tree.h"
#include <string.h>
#include "../neuralnetwork/NeuralNetwork.h"


char* Reconstruction(BinTree* bin);
void LeavesToChar(BinTree* bin, Network *net);


#endif
