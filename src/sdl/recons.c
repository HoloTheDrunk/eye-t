#include "recons.h"

char *mystrcat(char *a, char *b) {
  char *p, *q, *rtn;
  rtn = q = malloc(strlen(a) + strlen(b) + 1);
  for (p = a; (*q = *p) != '\0'; ++p, ++q) {}
  for (p = b; (*q = *p) != '\0'; ++p, ++q) {}
  return rtn;
}

void LeavesToChar(BinTree* bin, Network *net)
{
    if (bin->left == NULL && bin->right == NULL)
    {
        char test = GetCharNN(net, bin->key);
        bin->txt = &test;
        return;

    }
    else
    {
        LeavesToChar(bin->right, net);
        LeavesToChar(bin->left, net);
    }
}

char* Reconstruction(BinTree* bin) // Pas ouf :(
{
    if (bin->left != NULL)
    {
        return mystrcat(mystrcat(Reconstruction(bin->left), bin->txt)
                ,Reconstruction(bin->right));
    }

    printf("In then node : %s\n", bin->txt);
    return bin->txt;
}

