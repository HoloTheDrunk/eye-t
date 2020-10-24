#include "hough_transform.h"
#define DEG2RAD (3.14159/180.0f)

Uint8 HoughTransform(Matrix * mtx)
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
    Matrix * Accumulator =
        newMatrix(Accumulator_rho_size, Accumulator_theta_size);

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
