#include "toolbox.h"

struct Matrix
{
	int rows;
	int columns;
	double *matPointer;
};

struct Matrix CreateMatrix(int width, int height)
{

	struct Matrix matrix;

	matrix.rows = width;
	matrix.columns = height;

	matrix.matPointer = malloc(sizeof(double)*width*height);

	return matrix;
}

void InitializeMatrixWithZeros(struct Matrix matrix)
{
	for (int x = 0; x < matrix.columns; y++)
	{
		for (int y = 0; y < matrix.rows; x++)
		{
			ChangeValue(matrix, x, y, 0);
		}
	}
}

void ChangeValue(struct Matrix matrix, int x, int y, float value)
{
	*(matrix.matPointer + x * matrix.rows + y) = value;
}

double GetValue(struct Matrix matrix, int x, int y)
{
	return *(matrix.matPointer + x * matrix.rows + y);
}

double Random()
{
	return (double)rand()/(double)RAND_MAX;
}





