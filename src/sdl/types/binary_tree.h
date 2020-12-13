#ifndef BINARY_TREE_H
#define BINARY_TREE_H


#include <stdlib.h>
#include <stdio.h>
#include "tuple.h"
#include "matrix.h"
#include "../image_load.h"

typedef struct _BinTree
{
    Matrix *key;
    int empty;
    int hor;
    int vert;
    char *txt;
    struct _BinTree *left;
    struct _BinTree *right;
}BinTree;
// TreeB->left = NewBinTree(Left1);
BinTree* NewBinTree(Matrix * mat);
// Create a new bintree with a matrix as key, the matrix should
// contain the text matrix
void Free_MatBT(BinTree* MatBT);
// Deletes a BinTree
void MatBT_Print(BinTree* MatBT);
// Print a bintree recursevly
void Resize_Leaves(BinTree* bin, int width, int height);
// Resize in place all the leaves by width*height
void PrintTree(BinTree* curr,int depth);
// Print the BinTree
#endif
