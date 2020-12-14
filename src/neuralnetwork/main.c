#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include "layer.h"
#include "Network.h"
#include "sdl_func.h"
#include "surface_binlist.h"
#include "pixel_operations.h"


#define nbimage 62

int res[] = {(int)'0', (int)'1', (int)'2', (int)'3', (int)'4', (int)'5',\
   (int)'6', (int)'7', (int)'8', (int)'9',\
   (int)'A', (int)'B', (int)'C',\
   (int)'D', (int)'E', (int)'F', (int)'G', (int)'H', (int)'I', (int)'J',\
   (int)'K', (int)'L', (int)'M', (int)'N', (int)'O', (int)'P', (int)'Q',\
   (int)'R', (int)'S', (int)'T', (int)'U', (int)'V', (int)'W', (int)'X',\
   (int)'Y', (int)'Z',\
   (int)'a', (int)'b', (int)'c',\
   (int)'d', (int)'e', (int)'f', (int)'g', (int)'h', (int)'i', (int)'j',\
   (int)'k', (int)'l', (int)'m', (int)'n', (int)'o', (int)'p', (int)'q',\
   (int)'r', (int)'s', (int)'t', (int)'u', (int)'v', (int)'w', (int)'x',\
   (int)'y', (int)'z'};

int main()
{
    /*
       double **inputliste = malloc(nbimage * sizeof(double));
       int res[nbimage];
       init_sdl();
       for(int i=97;i<nbimage+97;i++)
       {
       char name[20]="data16x16/";
       char ch[10];
       ch[0]=(char)i;
       strcat(name,ch);
       strcat(name,".bmp");
       puts(name);
       SDL_Surface* image_surface = load_image(name);
       int *image1 = surface_binlist(image_surface);
       double *image2 = malloc(256*sizeof(double));
       printf("\n");
       for(int j = 0;j<256;j++)
       {
       image2[j]=image1[j];
       }
       inputliste[i-97]=image2;
       res[i-97]=i;
       }

     */

    Network net;
    initnet(&net,784);
    add_layer(&net,100);
    add_layer(&net,127);

    double **inputliste = malloc(62 * sizeof(double));
    init_sdl();
    for(int i = 0; i < 62; i++)
    {
        char name[50]="set/";
        char ch[10];
        sprintf(ch, "%d", res[i]);
        strcat(name, ch);
        strcat(name,"/0.jpg");
        puts(name);
        SDL_Surface* image_surface = load_image(name);
        int *image1 = surface_binlist(image_surface);
        double *image2 = malloc(784*sizeof(double));
        printf("\n");
        for(int j = 0; j < 784; j++)
        {
            image2[j]=image1[j];
        }
        inputliste[i]=image2;
    }

    train(&net,inputliste,res,100,nbimage);
	savestruct(&net, "struct");
	savenet(&net, "net");
	
    for(int i=0;i<nbimage;i++)
    {
        int p = (rand()/(double)RAND_MAX)*nbimage;
        double *out1 = calloc(net.input_dim,sizeof(double)); 
        printf("\n");
        printf("predict(%c)= %c \n",(char)res[p],\
				(char)predict(&net,inputliste[p],out1));
    }

    double *out3 = calloc(net.input_dim,sizeof(double));
    printf("predict(%c)= %c \n",(char)res[0],\
			(char)predict(&net,inputliste[0],out3)); 
    freeall(&net);
    free(inputliste);


    /*
    //  SDL_Surface *image1 = load_image("./imagename1");
    //  SDL_Surface *image2 = load_image("./imagename2");
    //double  inputliste1[16] = {1,0,1,1,0,0,1,0,1,0,0,1,1,1,1,1};
    //double  inputliste2[16] = {1,0,0,1,0,0,1,0,1,1,1,1,0,0,1,1};
    //double  inputliste3[16] = {1,1,1,1,0,0,1,1,0,1,0,0,0,1,0,0};
    //inputliste[0] = inputliste1;
    //inputliste[2] = inputliste2;
    //inputliste[1] = inputliste3;
    //int res[nbimage]={(int)'a',(int)'z',(int)'T'}; 

    Network net;
    initnet(&net,2);
    printf(" resulte j %d  ==?   indexmax %d  \n",result[j],indexmax);
    add_layer(&net,3);
    add_layer(&net,1);

    double input[4][2]={{0,0},{0,1},{1,0},{1,1}};
    double res[4]={0,1,1,0};
    double **resultliste = malloc(4*sizeof(double));
    for(int i =0;i<4;i++)
    {
    resultliste[i]=calloc(2,sizeof(double));
    resultliste[i][1] = input[i][1];
    resultliste[i][0] = input[i][0];
    }
    double result=evaluate(&net,resultliste,res,4);
    printf("performance initial = %f pourcent ",result*100);
    printf("\n");
    for(int i=0; i<(net.layers_dim);i++)
    {
    printlayer(&net.layers[i]);
    printf("\n\n");
    }


    train(&net,resultliste,res,1000,4);

    double resu2=evaluate(&net,resultliste,res,4);
    printf("performance finale = %f pourcent ",resu2*100);
    printf("\n");

    for(int i=0; i<(net.layers_dim);i++)
    {
    printlayer(&net.layers[i]);
    printf("\n\n");
    }
    free(resultliste);
    freeall(&net);

    layer layer1;
    init(&layer1,2,2);
    double input[]={1,1};
#include <stdlib.h>
double *outpout = calloc(2,sizeof(double));
forward(&layer1,input,outpout);
for(int i =0; i<2;i++)
printf("%f  \n", outpout[i]); 
free(outpout);
free(layer1.weight);
free(layer1.bias);
     */
    /*
       layer layer1;
       init(&layer1,3,2);
       for(int i = 0; i < 10;i++)
       printf("%f  ", layer1.weight[i]);
       printf("\n");
       printlayer(&layer1);
       free(layer1.weight);

       double A[] = {1,2,3,4,5,6};
       double B[] = {1,1,1,1,1,1}; 
       double *C = calloc(6,sizeof(double));
       addition(C,A,B,2,3);
       for(int i = 0; i<6;i++)
       {
       printf("%f   ",C[i]);
       }
       free(C);
       pr	for(int i = 0; i<6;i++)
       {
       printf("%f   ",C[i]);
       }intf("\n");
       double *D = calloc(2,sizeof(double));
       double input[]={1,1,1};
       multmatric(D,A,input,3,2);
       for(int i = 0; i<5;i++)
       {
       printf("%f   ",D[i]);
       }
       free(D);
       printf("\n");
     */
    return 0;
}
