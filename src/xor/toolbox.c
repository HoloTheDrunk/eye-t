#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "toolbox.h"


int IsInbound(struct MatrixNN matrix, int x, int y);

/*
 * Matrix structure and basic operations on them.
*/

// Create a matrix and return it.
struct MatrixNN CreateMatrix(int rows, int columns)
{
	struct MatrixNN matrix;
       	
	matrix.columns = columns;
	matrix.rows = rows;

	matrix.pointerStart = malloc(sizeof(double)*columns*rows);

	return matrix;
}

// Testing if the given coordinates are not out of bounds.
int IsInbound(struct MatrixNN matrix, int x, int y)
{
	return (x < matrix.columns && y < matrix.rows); 
}


// Loop in the matrix to return the value at the index given.
double NavMatrix(struct MatrixNN matrix, int x, int y)
{
	if (!IsInbound(matrix, x, y))
		printf("Out of bound: Wrong coordinates were given.[%d, %d]\n", x, y);
	
	return *(matrix.pointerStart + (y * matrix.columns + x));
}

// Change the value at index by the value given.
void ChangeValue(struct MatrixNN matrix, int x, int y, float value)
{
	if (!IsInbound(matrix, x, y))
		printf("Out of bound: Wrong coordinates were given.[%d, %d]\n", x, y);
	
	*(matrix.pointerStart + y * matrix.columns + x) = value;
}

// Initialize the matrix with a random value.
void InitMatrix(struct MatrixNN matrix)
{
	for (int y = 0; y < matrix.rows; y++)
        {
                for(int x = 0; x < matrix.columns; x++)
                        ChangeValue(matrix, x, y, Random());
        }    
}

// Initialize the matrix with 0s.
void InitMatrixZero(struct MatrixNN matrix)
{
	for (int y = 0; y < matrix.rows; y++)
        {
                for(int x = 0; x < matrix.columns; x++)
                        ChangeValue(matrix, x, y, 0);
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
