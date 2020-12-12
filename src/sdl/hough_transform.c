/*#include "hough_transform.h"
#define DEG2RAD (3.14159/180.0f)

Uint8 HoughTransform(Matrix * mtx)
{ CORRECT
    int width ;
    int height ;
    if (!(nRows(mtx, &width) && nCols(mtx, &height)))
        errx(1, "Error determination of the matrix size has failed");
    double hough_h = ((sqrt(2.0) * (double)(height>width?height:width)) / 2.0);
    unsigned int Accumulator_rho_size = hough_h * 2;
    unsigned int Accumulator_theta_size = 180;
    double center_x = width / 2;
    double center_y = height / 2;
    Matrix * Accumulator =
        newMatrix(Accumulator_rho_size, Accumulator_theta_size);

<<<<<<< HEAD
=======
    //Tuple* black_pixels = BlackPixel_to_List(mtx); // A REVOIR D URGENCE CA NE FORME PAS UN ARRAY MAISS BIEN QU UN SEUL TUPLE
    // CEST POUR CA QUE RIEN NE FONCTIONNE
    //PrintTuple(*black_pixels); // LA FONCTION PRINTTUPLE LE PROUVE BIEN
    //printf("SIZE OF BLACK PIXELS : %lu ", sizeof(black_pixels)/sizeof(black_pixels[0]));
>>>>>>> origin/reconstruction
    for(int x = 1; x != mtx->width ; x++)
    {
        for(int y = 1; y != mtx->height ; y++)
        {
            unsigned val = -1;
            getElement(mtx,x,y, &val);
            if (val == 0)
            {
                //printf("x : %i y : %i \n",x,y );
                for (int theta = -60; theta != 60; theta++)
                {
                    double rho = ((double)x-center_x) *
                        cos((double)theta * DEG2RAD) + (((double)y -center_y) *
                                sin((double)theta * DEG2RAD));

                    unsigned val = 0;
                    getElement(Accumulator, round(rho+hough_h), theta, &val);
                    val++;
                    SetElement(Accumulator, round(rho+hough_h),theta,val);

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

                if (!getElement(Accumulator,i,j, &val))
                {
                    errx(1, "Error");
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
                }
            }
        }

        printf("%i\n", thetaa);
        return sum/div;
    }
<<<<<<< HEAD
=======

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
