#include "recons.h"

char *mystrcat(char *a, char *b) {
  char *p, *q, *rtn;
  rtn = q = malloc(strlen(a) + strlen(b) + 1);
  for (p = a; (*q = *p) != '\0'; ++p, ++q) {}
  for (p = b; (*q = *p) != '\0'; ++p, ++q) {}
  return rtn;
}


char* Reconstruction(BinTree* bin) // Pas ouf :(
{
    if (bin->left != NULL)
    {
        return mystrcat(mystrcat(Reconstruction(bin->left), bin->txt)
                ,Reconstruction(bin->right));
    }
    return bin->txt;
}


int rec[1000006];

void printTree(BinTree* curr,int depth)
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
    printTree(curr->left,depth+1);
    rec[depth]=0;
    printTree(curr->right,depth+1);
}
