#include "hough_transform.h"
#define DEG2RAD (3.14159/180.0f)

Uint8 HoughTransform(matrix * mtx)
{ /*CORRECT */
    int width ;
    int height ;
    if (!(nRows(mtx, &width) && nCols(mtx, &height)))
        errx(1, "Error determination of the matrix size has failed");
    double hough_h = ((sqrt(2.0) * (double)(height>width?height:width)) / 2.0);
    unsigned int Accumulator_rho_size = hough_h * 2;
    unsigned int Accumulator_theta_size = 180;
    double center_x = width / 2;
    double center_y = height / 2;
    matrix * Accumulator =
        newMatrix(Accumulator_rho_size, Accumulator_theta_size);
    /*****************************************************************************/
    //Tuple* black_pixels = BlackPixel_to_List(mtx); // A REVOIR D URGENCE CA NE FORME PAS UN ARRAY MAISS BIEN QU UN SEUL TUPLE
    // CEST POUR CA QUE RIEN NE FONCTIONNE
    //PrintTuple(*black_pixels); // LA FONCTION PRINTTUPLE LE PROUVE BIEN
    //printf("SIZE OF BLACK PIXELS : %lu ", sizeof(black_pixels)/sizeof(black_pixels[0]));
    for(int x = 1; x != mtx->rows ; x++)
    {
        for(int y = 1; y != mtx->cols ; y++)
        {
            unsigned val = -1;
            getElement(mtx,x,y, &val);
            if (val == 0)
            {
                //printf("x : %i y : %i \n",x,y );
                for (int theta = -60; theta != 60; theta++)
                {
                    double rho = ((double)x-center_x) * cos((double)theta * DEG2RAD) + (((double)y -center_y) * sin((double)theta * DEG2RAD));
                    // LE CALCUL EST BON ET COHERENT IL NE FAUT PAS TOUCHER A CETTE LIGNE
                    // CEPENDNANT IL NE FAUT PAS OUBLIER D'INCREMENTÉ LA VALEUR ACCUMULATOR[RHO, THETA] POUR QUE
                    // CA PRENNENT EN COMPTE TOUT CA
                    //printf("THETA : %i  X : %i  Y : %i  RHO : %f \n",theta,x,y ,rho);
                    unsigned val = 0;
                    //printf("%f , %i \n", rho, theta);
                    getElement(Accumulator, round(rho+hough_h), theta, &val);
                    //printf("%f", round(rho+hough_h)*180);
                    val++;
                    setElement(Accumulator, round(rho+hough_h),theta,val);
                    //IncreamentElement(Accumulator, rho, theta); CETTE FONCTION CAUSE UN SEGFAULT ERROR
                    //JE SUPPOSE QUE L ERREUR VIENT DE LA MATRIX ACCUMULATOR, TOUT DOIT ETRE REVU CONCENRNAT LES MATRIX
                    //LA MATRIX EST BIEN CONSTRUIRE AVEC LE BON NOMBRES DE DIMENSIONS, LES FONCTIONS SONT MERDIQUES
                    //IL FAUT TOUT RECODER !!!!
                }
            }
        }

    }
        Uint8 max = 0;
        Uint8 thetaa = 0;
        Uint8 sum = 0;
        Uint8 div = 1;
        //Uint8 rhoo = 0;
        for(unsigned int i = 1; i != Accumulator_rho_size; i++)
        {
            for(unsigned int j = 1; j != Accumulator_theta_size; j++)
            {
                unsigned val = 0;

                if (!getElement(Accumulator,i,j, &val)) // PROBLEME DE DIMENSIONS ?
                {
                    //printf("i : %i , j : %i \n", i, j);
                    errx(1, "Error impossible to get the value Accumulator hough_transform.c/Hough_Transform : 36");
                }
                if (max < val)
                {
                    max = val;
                    printf("%i \n", i);
                    if (div != 21)
                    {
                        sum += i;
                        div += 1;
                    }
                    thetaa = i;
                    //rhoo = j;
                }
            }
        }

        printf("%i\n", thetaa);
        return sum/div;
    }
/*
   void Put_Tuple(Tuple parr[], int x, int y, size_t len)  // FONCTIONNE BIEN A PRIORIS A REVOIR QUAND MEME !
   {
   printf("It begins there : \n");
   for(unsigned int i = 0; i != len ; i++)
   {
   if (IsTupleEmpty(parr[i]))
   {
   parr[i].x = x;
   parr[i].y = y;
   break;
   }
   }
   }




   void BlackPixel_to_List(matrix * mtx) // GROS PROBLEME !!!! SURREENT LA STRUCTURE TUPLE MAL GERE
   {
   Tuple *parr = malloc(mtx->rows * mtx->cols * sizeof(Uint8));

   for (int i = 0; i != sizeof(parr)/sizeof(parr[0]); i++)
   {
   parr[i] = NewTuple();
   } // Initializing the array of empyt tuples avoiding trash memory


//for(int i = 0; i!= sizeof(parr)/sizeof(parr[0]) ; i++)
//{
//    PrintTuple(parr[i]);
//}

// INSERER CHAQUE COORD DE PIXELS NOIR
for(int i = 1; i != mtx->rows ; i++)
{
for(int j = 1; j != mtx->cols ; j++)
{
unsigned val = -1;
getElement(mtx,i,j, &val);
if (val == 0)
Put_Tuple(parr, i,j, mtx->rows * mtx->cols * sizeof(Uint8));
}
}
return parr;
}
*/
