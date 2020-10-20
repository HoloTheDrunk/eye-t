#ifndef BINARY_TREE_H
#define BINARY_TREE_H


#include <stdlib.h>
#include <stdio.h>
#include "tuple.h"
#include "matrix.h"
#include "../image_load.h"

typedef struct _BinTree
{
    matrix *key;
    int empty;
    int hor;
    int vert;
    char *txt;
    struct _BinTree *left;
    struct _BinTree *right;
}BinTree;

BinTree* NewBinTree(matrix * mat);
// Create a new bintree with a matrix as key, the matrix should
// contain the text matrix
void Free_MatBT(BinTree* MatBT);
// Deletes a BinTree
void MatBT_Print(BinTree* MatBT, size_t h);
// Print a bintree recursevly
#endif
