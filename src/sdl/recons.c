#include "recons.h"

char *mystrcat(char *a, char *b) {
    char *p, *q, *rtn;
    rtn = q = malloc(strlen(a) + strlen(b) + 1);
    for (p = a; (*q = *p) != '\0'; ++p, ++q) {}
    for (p = b; (*q = *p) != '\0'; ++p, ++q) {}
    return rtn;
}


char test[5];
void LeavesBound(BinTree* bin, Network* net)
{
    if (bin->left == NULL)
    {

        test[0] = *GetCharNN(net,bin->key);
        *(bin->txt) = test[0];
        test[0] = test[1];
    }
    else
    {

        LeavesBound(bin->left, net);
        LeavesBound(bin->right, net);
    }
}

void check(BinTree* bin)
{
    if (bin == NULL)
        return;
    //printf("%s\n",bin->txt);
    check(bin->right);
    check(bin->right);
}

char *buffer;


char* Reconstruction(BinTree* bin, Network* net) // Pas ouf :(
{
    if (bin->left != NULL)
    {
        asprintf(&buffer, "%s%s%s", Reconstruction(bin->left,net), bin->txt, Reconstruction(bin->right,net));
        return buffer;
    }
    return bin->txt;
}


int rec_bis[4096];

void printTree(BinTree* curr, int depth)
{
    char* nothing ="";
    int i;
    if(curr==NULL)return;
    printf("\t");
    for(i=0;i<depth;i++)
        if(i==depth-1)
            printf("%s───",rec_bis[depth-1]?"├":"└");
        else
            printf("%s   ",rec_bis[i]?"│":"  ");
    if (*curr->txt == '\n')
        printf("%s\n","\\n");
    else if (curr->txt == nothing)
        printf("%s\n","*");
    else if (*curr->txt == ' ')
        printf("%s\n","space");
    else
        printf("%s\n",curr->txt);
    rec_bis[depth]=1;
    printTree(curr->left,depth+1);
    rec_bis[depth]=0;
    printTree(curr->right,depth+1);
}

void outputTree(BinTree* curr, int depth, FILE *fptr)
{
    char* nothing ="";
    int i;
    if(curr==NULL)return;
    //fprintf(fptr, "\t");
    for(i=0;i<depth;i++)
        if(i==depth-1)
            fprintf(fptr, "%s___", rec_bis[depth-1] ? "L" : "\\");
        else
            fprintf(fptr, "%s   ", rec_bis[i] ? "|" : "  ");
    if (*curr->txt == '\n')
        fprintf(fptr, "\\n\n");
    else if (curr->txt == nothing)
        fprintf(fptr, "*\n");
    else if (*curr->txt == ' ')
        fprintf(fptr, "space\n");
    else
        fprintf(fptr, "%s\n",curr->txt);
    rec_bis[depth]=1;
    outputTree(curr->left, depth+1, fptr);
    rec_bis[depth]=0;
    outputTree(curr->right, depth+1, fptr);

}
