#ifndef MATRIX_H
#define MATRIX_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL/SDL.h>
#include "SDL/SDL_image.h"
#include <err.h>
#include "../toolbox.h"
struct Matrix {
    int width; // number of rows
    int height; // number of columns
    int** data; // a pointer to an array
    //of n_rows pointers to rows; a row is an array of n_cols doubles
};


typedef struct Matrix Matrix;


Matrix* NewMatrix(int n_cols, int n_rows);

void PrintMatrix(Matrix* m);

int GetElement(Matrix* matrix, int x, int y);

void SetElement(Matrix* matrix, int x, int y, int val);

Matrix* ResizeMatrix(Matrix* matrix, int newHt, int newWid);

struct MatrixNN ConvertToNN(Matrix* matrix);
#endif
