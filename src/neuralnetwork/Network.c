#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Network.h"
#include <err.h>

void initnet(Network *self,int input_dim)
{
    self -> input_dim = input_dim;
    self -> layers_dim = 0;
    self -> layers = calloc(self->layers_dim,sizeof(layer));
}

void add_layer(Network *self,int size)
{
    int input_dim=0;
    if(self->layers_dim > 0)
    {
        input_dim = self->layers[(self->layers_dim)-1].size;
    }
    else
    {
        input_dim = self->input_dim;
    }
    self ->layers_dim +=1;
    self ->layers = realloc(self->layers,(self->layers_dim)*sizeof(layer));
    layer newlayer;
    init(&newlayer,size,input_dim);
    self ->layers[(self->layers_dim)-1]=newlayer;
}

void savestruct(Network *self,char *File)
{
    FILE *file = fopen(File, "w");
    if(!file)
    {
        perror(File);
        errx(1, "The file wasn't able to be read/created");
    }
    else
    {
        printf("fichier ouvert\n");
        fwrite(self,sizeof(Network),1,file);
        fclose(file);
    }
}

void loadstruct(Network *self,char *File)
{
    FILE *file = fopen(File, "r");
    if(file)
    {
        printf("fichier ouvert\n");
        size_t res = fread(self,sizeof(Network),1,file);
        if(res==0)
            printf("erroor fread");
        fclose(file);
    }
    else
    {
        perror(File);
        errx(1, "The file wasn't able to be loaded");
    }
}


void savenet(Network *self,char *File)
{
    FILE* file = NULL;

    file = fopen(File, "w");
    if (file != NULL)
    {
        //printf("fail to open fail %s \n",File);
        layer *listelayer= self->layers;
        int nblayer = self->layers_dim;
        for (int i = 0; i<nblayer;i++)
        {
            double *matrix = listelayer[i].weight;
            int matrixsize = (listelayer[i].size)*(listelayer[i].input_size);
            fwrite(matrix,matrixsize,sizeof(double),file);
        }
        fclose(file);
    }
    else
    {
        printf("fopen fail\n");
    }
}

void feedforward(Network *self, double *input,double *out)
{

    for(int i=0; i<self->input_dim;i++)
    {
        out[i]=input[i];
    }

    for(int i=0; i<self->layers_dim;i++)
    {

        int size = self->layers[i].size;
        double *output=calloc(size,sizeof(double));

        forward(&(self->layers[i]),out,output);

        out = realloc(out,size*sizeof(double));
        for(int copie2=0; copie2<size;copie2++)
        {
            //printf("out befor = %f \n",out[copie2]);
            out[copie2]= output[copie2];
           // printf("out after = %f \n",out[copie2]);
            self->layers[i].out[copie2] = output[copie2];
        }
        //printf("size on layer %d \n",size);
        free(output);
    }
    free(out);
}

int predict(Network *self,double *input,double *out)
{
    feedforward(self,input,out);

    layer lastelayer = self->layers[self->layers_dim-1];
    int size = lastelayer.size;

    int index_max=0;
    double max=lastelayer.out[0];

    for(int i=0;i<size;i++)
    {
        if(max<lastelayer.out[i])
        {
            index_max=i;
            max = lastelayer.out[i];
        }
       // printf("out i = %f  %d \n",out[i],i);
    }

    //printf("max = %f\n", max);
    //printf("index_max = %d\n",index_max);
    return index_max;
}


double evaluate(Network *self,double **inputlist,int *result,int sizeoflist)
{
    //int size = self->layers[self->layers_dim -1].size;
    double sum =0;
    for(int i=0; i<sizeoflist; i++)
    {
        double *out = calloc(self->input_dim,sizeof(double));
        if(predict(self,inputlist[i],out)==result[i])
        {
            sum+=1;
        }
    }
    return sum/(double)sizeoflist;
}


void train(Network *self,double **inputlist,int *result,int step,int lenres)
{
    printf("step %d\n",step);
    double max = 0;
    double condieval;
    do
    {
        double eval = evaluate(self,inputlist,result,lenres);
        if(eval>max)
        {
            max = eval;
            printf("eval = %f pourcent \n",eval*100);
        }
        condieval = eval*100;
        for(int j=0; j<lenres;j++)
        {
            int condition = 0;
            int indexmax;
            layer *layerlist = self->layers;
            layer lastlayer = layerlist[self->layers_dim-1];
            double inputdim = self->input_dim;

            do
            {
                //calcule of the outpout for the error
                double *outi = calloc(inputdim,sizeof(double));
                indexmax= predict(self,inputlist[j],outi);

                //calcule of error
                double* outll = lastlayer.out;
                int outsize = layerlist[self->layers_dim-1].size;
                double *error=calloc(outsize,sizeof(double));
                error[result[j]]=1;

                for(int k = 0; k<outsize; k++)
                {
                    error[k] -= outll[k];
                    lastlayer.deltas[k]= error[k];//*outll[k]*(1-outll[k]);
                }


                free(error);

                //backpropagation
                for(int ilayer =self->layers_dim-2; ilayer>=0;ilayer--)
                {
                    layer l = layerlist[ilayer];
                    layer b = layerlist[ilayer+1];
                    int size = layerlist[ilayer].size;
                    for(int index = 0; index<size; index++)
                    {
                        //calcule of delta
                        double wiandt = 0;
                        double pout = l.out[index];
                        for(int all=0;all<size;all++)
                        {
                             double wi= b.weight[all*size+index];
                             double delta = b.deltas[index];
                             wiandt+=wi*delta;
                        }
                        l.deltas[index] = pout*(1-pout)*wiandt;
                    }
                }

                double *out2 = calloc(inputdim,sizeof(double));
                indexmax= predict(self,inputlist[j],out2);
                condition =!(result[j] == indexmax);
            }while(condition);
        }
    }while(condieval<97);

}


void freeall(Network *self)
{
    for(int i=0; i<(self->layers_dim);i++)
    {
        free(self->layers[i].bias);
        free(self->layers[i].weight);
        free(self->layers[i].deltas);
        free(self->layers[i].out);
    }
    free(self->layers);
}

void printnet(Network *self)
{
   for(int i=0;i<self->layers_dim;i++)
   {
       printlayer(&(self->layers[i]));
       printf("\n\n");
   }
}
