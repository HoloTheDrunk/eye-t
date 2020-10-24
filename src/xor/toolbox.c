#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "toolbox.h"


int VerifyInbound(struct Matrix matrix, int x, int y);

/*
 * Matrix structure and basic operations.
*/
//========================================//

// Create a matrix; return the matrix
struct Matrix CreateMatrix(int rows, int columns)
{
	struct Matrix matrix;
       	
	matrix.rows = rows;
	matrix.columns = columns;

	matrix.mat = malloc(sizeof(double)*columns*rows);

	return matrix;
}

// Testing if given coordinates are correct
int VerifyInbound(struct Matrix matrix, int x, int y)
{
	return (x < matrix.rows &&  y < matrix.columns); 
}


// Function to navigate in the matrix; return matrix(x, y)
double NavMatrix(struct Matrix matrix, int x, int y)
{
	if (!VerifyInbound(matrix, x, y))
		printf("Out of bound: Wrong coordinates were given.\n");
	
	return *(matrix.mat + (x * matrix.columns + y));
}

// Function to change a value in a matrix
void ChangeMatrix(struct Matrix matrix, int x, int y, float val)
{
	if (!VerifyInbound(matrix, x, y))
	{
		printf("====================\n");
                printf("Error in coordinates\n");
                printf("====================\n");
	}
 
	*(matrix.mat + x * matrix.columns + y) = val;
}

// Initialize the matrix with zeros
void InitMatrix(struct Matrix matrix)
{
	for (int i = 0; i < matrix.rows; i++)
        {
                for(int j = 0; j < matrix.columns; j++)
                {
                        ChangeMatrix(matrix, i, j, Random());
                }
        }    
}

void InitMatrixZero(struct Matrix matrix)
{
	for (int i = 0; i < matrix.rows; i++)
        {
                for(int j = 0; j < matrix.columns; j++)
                {
                        ChangeMatrix(matrix, i, j, 0);
                }
        }

}


/*
 * Miscellaneous
*/

double Random()
{
        return (double)rand()/(double)RAND_MAX;
}

double Sigmoid(double eyet)
{
	return (1.0 / (1.0 + exp(-eyet)));
}
