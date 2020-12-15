#ifndef RECONS_H_
#define RECONS_H_

#include <stdio.h>
#include <stdlib.h>
#include "types/binary_tree.h"
#include <string.h>

char* Reconstruction(BinTree* bin, char* finale);
void LeavesToChar(BinTree* bintree, Network *net);

#endif
