#include "binary_tree.h"

BinTree* NewBinTree(Matrix * mat)
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
        if (MatBT->txt)
            free(MatBT->txt);
        Free_MatBT(MatBT->right);
        Free_MatBT(MatBT->left);
    }
    else
        free(MatBT);
}



void MatBT_Print(BinTree* MatBT)
{
    if (!MatBT)
        return;
    PrintMatrix(MatBT->key);
    MatBT_Print(MatBT->right);
    MatBT_Print(MatBT->left);
}

void Resize_Leaves(BinTree* bin, int width, int height)
{
    if (bin->right == NULL && bin->left == NULL)
    {
        bin->key = ResizeMatrix(bin->key, width, height);
        printf("Test \n");
    }
    else if (bin->right == NULL)
        Resize_Leaves(bin->left, width, height);
    else if (bin->left == NULL)
        Resize_Leaves(bin->right, width, height);
    else
    {
        Resize_Leaves(bin->left, width, height);
        Resize_Leaves(bin->right, width, height);
    }
}


