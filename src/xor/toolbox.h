#ifndef TOOLBOX_H_
#define TOOLBOX_H_

#include <stdio.h>
#include <stdlib.h>


struct Matrix CreateMatrix(int width, int height);

void InitializeMatrixWithZeros(struct Matrix matrix);

double GetValue(struct Matrix Matrix, int x, int y);

void ChangeValue(struct Matrix matrix, int x, int y, float value);

double Random();

#endif
