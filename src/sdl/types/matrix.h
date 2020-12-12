#ifndef MATRIX_H
#define MATRIX_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL/SDL.h>
#include "SDL/SDL_image.h"
#include "../pixel_operations.h"
#include <err.h>

struct Matrix {
    int width; // number of rows
    int height; // number of columns
    int** data; // a pointer to an array
    //of n_rows pointers to rows; a row is an array of n_cols doubles
};


typedef struct Matrix Matrix;


Matrix* NewMatrix(int n_rows, int n_cols);

void PrintMatrix(Matrix* m);

int GetElement(Matrix* matrix, int x, int y);

void SetElement(Matrix* matrix, int x, int y, int val);

Matrix * Image_To_Matrix(SDL_Surface* image, int width, int height);
// create new matrix from image
SDL_Surface* Matrix_To_Image(Matrix* mtx, int coef);
// converting a matrix to image by returning a image
Matrix* ResizeMatrix(Matrix* matrix, int newHt, int newWid);

#endif
