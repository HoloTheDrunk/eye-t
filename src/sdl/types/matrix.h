#ifndef MATRIX_H
#define MATRIX_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include "SDL/SDL_image.h"
#include "../pixel_operations.h"
#include <err.h>
typedef struct {
  int rows;
  int cols;
  unsigned * data;
} matrix;

// Watchout !!
// Keep in mind that the matrix begin with 1 and not 0 !!
matrix * newMatrix(int rows, int cols);
// Create a new matrix
int deleteMatrix(matrix * mtx);
// Free the space since we use malloc
matrix * copyMatrix(matrix * mtx);
// Copy the matrix
void IncreamentElement(matrix * mtx, int row, int col);
// IncreamentElement by one
int setElement(matrix * mtx, int row, int col, unsigned val);
// Set element val in the coord row and col
// return 1 if the element has been set else return 0
int getElement(matrix * mtx, int row, int col,unsigned * val);
// Getting the element in the coord row and col in val
// return 0 if the element exist, else return -1
int nRows(matrix * mtx, int * n);
// n become the number of Rows
int nCols(matrix * mtx, int * n);
// n become the number of Columns (Condem ;) )
int printMatrix(matrix * mtx);
// print the Matrix duh
int transpose(matrix * in, matrix * out);
// transpose the in matrix into the out one
int sum(matrix * mtx1, matrix * mtx2, matrix * sum);
// sum of the two matrix
int product(matrix * mtx1, matrix * mtx2, matrix * prod);
// product of the two matrix
int dotProduct(matrix * v1, matrix * v2, double * prod);
// dot product of the two matrix
int identity(matrix * m);
// transform the matrix to an identity matrix
int isSquare(matrix * mtx);
// 1 if th matrix is square 0 if not
int isDiagonal(matrix * mtx);
// 1 if the matrix is diagonal else 0
int isUpperTriangular(matrix * mtx);
// 1 if there's an Upper triangle 0 if not
int diagonal(matrix * v, matrix * mtx);
// same a upper bur for the diagonal :)
matrix * image_to_matrix(SDL_Surface* image, int width, int height);
// create new matrix from image

#endif
