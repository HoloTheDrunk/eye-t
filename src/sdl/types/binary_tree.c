#include "binary_tree.h"

BinTree* NewBinTree(matrix * mat)
{
    BinTree *MatBT = malloc(sizeof(BinTree));
    MatBT->key = mat;
    MatBT->hor = 0;
    MatBT->vert = 0;
    MatBT->txt = NULL;
    MatBT->right = NULL;
    MatBT->left = NULL;
    return MatBT;
}


void Free_MatBT(BinTree* MatBT)
{
    if (MatBT)
    {
        deleteMatrix(MatBT->key);
        if (MatBT->txt)
            free(MatBT->txt);
        Free_MatBT(MatBT->right);
        Free_MatBT(MatBT->left);
    }
    else
        free(MatBT);
}



void MatBT_Print(BinTree* MatBT, size_t h)
{
    if (!MatBT)
        return;
    display_image(matrix_to_image(MatBT->key,1));
    MatBT_Print(MatBT->right,h + 1);
    MatBT_Print(MatBT->left,h + 1);
}



