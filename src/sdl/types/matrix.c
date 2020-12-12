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


Matrix* Image_To_Matrix(SDL_Surface* image, int width, int height)
{
    Matrix* matrix = NewMatrix(image->w, image->h);
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            Uint8 r,g,b;
            Uint32 pixel = get_pixel(image, i , j);

            SDL_GetRGB(pixel, image->format, &r, &g, &b);

            if (r == 0 && g == 0 && b == 0)
                SetElement(matrix, i, j, 0);
            else
                SetElement(matrix, i, j, 1);
        }
    }
    return matrix;
}

SDL_Surface* Matrix_To_Image(Matrix* mtx, int coef)
{
    Uint32 white = 0x00000000;
    Uint32 black = 0xffffffff;
    Uint32 color = 0xffffffff / coef;
    SDL_Surface *New_Image = SDL_CreateRGBSurface(0,mtx->width,mtx->height,32,0,0,0,0);
    for (int  i = 0; i < mtx->width; i++)
    {

    for (int j = 0; j < mtx->height; j++)
    {
        if (GetElement(mtx,i,j)== 1)
            put_pixel(New_Image, i,j,white);
        else
        {
            if (GetElement(mtx,i,j) == 0)
                put_pixel(New_Image,i,j,black);
            else
                put_pixel(New_Image,i,j,color*GetElement(mtx,i,j));
        }
    }
    }
    return New_Image;
}
/*
def nearestNeighborScaling(matrix , newWid, newHt ):
    target = makeEmptyMatrixf(newWid, newHt)
    width = len(matrix[0])
    height = len(matrix)
    print("Width : " + str(width) + " Height : " + str(height))
    for x in range(newWid):
        for y in range(newHt):
            srcX = int( round( float(x) / float(newWid) * float(width) ) )
            srcY = int( round( float(y) / float(newHt) * float(height) ) )
            srcX = min( srcX, width-1)
            srcY = min( srcY, height-1)
            target[x][y] = matrix[srcX][srcY]
    return target
*/


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
