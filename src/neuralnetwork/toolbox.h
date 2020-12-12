#ifndef TOOLBOX_H
#define TOOLBOX_H

/*
 * Matrix structure and basic operations.
*/

// Matrix struct declaration.
struct MatrixNN
{
        // Size of the matrix.
        int rows;
        int columns;

        // Pointer to the start of the matrix.
        double *pointerStart;
};

void ChangeValue(struct MatrixNN matrix, int x, int y, float value);

double NavMatrix(struct MatrixNN matrix, int x, int y);

void InitMatrix(struct MatrixNN matrix);

void PrintMatrixNN(struct MatrixNN matrix); // Print the fucking matrix

void InitMatrixZero(struct MatrixNN matrix);

struct MatrixNN CreateMatrix(int rows, int colums);

/*
 * Miscellaneous
*/

double Random();

double Sigmoid(double eyet);

#endif
