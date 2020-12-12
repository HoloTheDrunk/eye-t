#include "matrix.h"
#define min(a,b) (a<=b?a:b)

Matrix* NewMatrix(int n_rows, int n_cols) {
    struct Matrix* matrix = malloc(sizeof(Matrix));
    matrix->width = n_rows;
    matrix->height = n_cols;
    int** data = malloc(sizeof(double*) * n_rows);
    for(int x = 0; x < n_rows; x++){
        data[x] = calloc(n_cols, sizeof(double));
    }
    matrix->data = data;
    return matrix;
}

void PrintMatrix(Matrix* m) {
    for(int x = 0; x < m->height; x++) {
        printf("%s", "\n");
        for(int y = 0; y < m->width; y++) {
            printf("%i", m->data[y][x]);
        }
    }
    printf("\n");
}

int GetElement(Matrix* matrix, int x, int y)
{
    return matrix->data[x][y];
}

void SetElement(Matrix* matrix, int x, int y, int val)
{
    matrix->data[x][y] = val;
}

Matrix* ResizeMatrix(Matrix* matrix, int newHt, int newWid)
{
    Matrix* target = NewMatrix(newHt, newWid);
    int width = matrix->width;
    int height = matrix->height;
    int srcY = 0;
    int srcX = 0;
    for(int x = 0; x < newWid; x++)
    {
        for(int y = 0; y < newHt; y++)
        {
            srcX = (int)(roundf((float)x/(float)newWid * (float)width));
            srcY = (int)(roundf((float)y / (float)newHt * (float)height));
            srcX = min(srcX, width-1);
            srcY = min(srcY, height-1);
            int val = GetElement(matrix, srcX, srcY);
            SetElement(target, x, y, val);
        }
    }
    return target;
}
