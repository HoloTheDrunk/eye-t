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


int rec[1000006];

void PrintTree(BinTree* curr,int depth)
{
    char* nothing ="";
    int i;
    if(curr==NULL)return;
    printf("\t");
    for(i=0;i<depth;i++)
        if(i==depth-1)
                printf("%s───",rec[depth-1]?"├":"└");
        else
                printf("%s   ",rec[i]?"│":"  ");
    if (*curr->txt == '\n')
        printf("%s\n","\\n");
    else if (curr->txt == nothing)
        printf("%s\n","*");
    else if (*curr->txt == ' ')
        printf("%s\n","space");
    else
        printf("%s\n",curr->txt);
    rec[depth]=1;
    PrintTree(curr->left,depth+1);
    rec[depth]=0;
    PrintTree(curr->right,depth+1);
}


