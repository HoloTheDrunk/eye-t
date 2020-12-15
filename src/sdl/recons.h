#ifndef RECONS_H_
#define RECONS_H_

#include <stdio.h>
#include <stdlib.h>
#include "types/binary_tree.h"
#include "../neuralnetwork/NeuralNetwork.h"
#include <string.h>

char* Reconstruction(BinTree* bin, Network* net);
void LeavesBound(BinTree* bin, Network* net);


void check(BinTree* bin);

void outputTree(BinTree* curr, int depth, char *output);

#endif
