#include "matrix.h"

/* Creates a ``rows by cols'' matrix with all values 0.
 * Returns NULL if rows <= 0 or cols <= 0 and otherwise a
 * pointer to the new matrix.
 */

matrix * image_to_matrix(SDL_Surface* image, int width, int height)
{
    matrix* imgMatrix = newMatrix(width, height);
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            Uint8 r, g, b;
            Uint32 pixel = get_pixel(image, i, j);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            int val = (r == 0 && g == 0 && b == 0) ? 0 : 1;
            if (!setElement(imgMatrix,i,j,val))
                errx(1,"Error matrix initization value matrix.c/image_to_matrix : 20");
        }
    }
    return imgMatrix;
}

matrix * newMatrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) return NULL;

    // allocate a matrix structure
    matrix * m = (matrix *) malloc(sizeof(matrix));

    // set dimensions
    m->rows = rows;
    m->cols = cols;

    // allocate a double array of length rows * cols
    m->data = (unsigned *) malloc(rows*cols*sizeof(double));
    // set all data to 0
    int i;
    for (i = 0; i < rows*cols; i++)
        m->data[i] = 0.0;

    return m;
}

/* Deletes a matrix.  Returns 0 if successful and -1 if mtx
 * is NULL.
 */
int deleteMatrix(matrix * mtx) {
    if (!mtx) return -1;
    // free mtx's data
    assert (mtx->data);
    // if the expression is false then err is shown
    free(mtx->data);
    // free mtx itself
    free(mtx);
    return 0;
}

#define ELEM(mtx, row, col) \
    mtx->data[(col-1) * mtx->rows + (row-1)]

/* Copies a matrix.  Returns NULL if mtx is NULL.
*/
matrix * copyMatrix(matrix * mtx) {
    if (!mtx) return NULL;

    // create a new matrix to hold the copy
    matrix * cp = newMatrix(mtx->rows, mtx->cols);

    // copy mtx's data to cp's data
    memcpy(cp->data, mtx->data,
            mtx->rows * mtx->cols * sizeof(double));

    return cp;
}

/* Sets the (row, col) element of mtx to val.  Returns 0 if
 * successful, -1 if mtx is NULL, and -2 if row or col are
 * outside of the dimensions of mtx.
 */
int setElement(matrix * mtx, int row, int col, unsigned val)
{
    if (!mtx) return 0;
    assert (mtx->data);
    if (row <= 0 || row > mtx->rows ||
            col <= 0 || col > mtx->cols)
        return -2;

    ELEM(mtx, row, col) = val;
    return 1;
}

void IncreamentElement(matrix * mtx, int row, int col)
{

    ELEM(mtx, row, col)++;
    printf("%i", ELEM(mtx,row,col));
}



/* Sets the reference val to the value of the (row, col)
 * element of mtx.  Returns 0 if successful, -1 if either
 * mtx or val is NULL, and -2 if row or col are outside of
 * the dimensions of mtx.
 */
int getElement(matrix * mtx, int row, int col,
        unsigned * val) {
    if (!mtx || !val) return 0;
    assert (mtx->data);
    if (row <= 0 || row > mtx->rows ||
            col <= 0 || col > mtx->cols)
    {
        //printf("ROW : %i , COL : %i, MTX->ROWS : %u , MTX->COLS : %u ",row,col,mtx->rows,mtx->cols);
        return 0;
    }

    *val = ELEM(mtx, row, col);
    return 1;
}

/* Sets the reference n to the number of rows of mtx.
 * Returns 0 if successful and -1 if mtx or n is NULL.
 */
int nRows(matrix * mtx, int * n) {
    if (!mtx || !n) return 0;
    *n = mtx->rows;
    return 1;
}

/* Sets the reference n to the number of columns of mtx.
 * Returns 0 if successful and -1 if mtx is NULL.
 */
int nCols(matrix * mtx, int * n) {
    if (!mtx || !n) return 0;
    *n = mtx->rows;
    return 1;
}

/* Prints the matrix to stdout.  Returns 0 if successful
 * and -1 if mtx is NULL.
 */
int printMatrix(matrix * mtx) {
    if (!mtx) return -1;

    int row, col;
    for (row = 1; row <= mtx->rows; row++) {
        for (col = 1; col <= mtx->cols; col++) {
            // Print the floating-point element with
            //  - either a - if negative or a space if positive
            //  - at least 3 spaces before the .
            //  - precision to the hundredths place
            printf("%u      ", ELEM(mtx, row, col));
        }
        // separate rows by newlines
        printf("\n");
    }
    return 0;
}

/* Writes the transpose of matrix in into matrix out.
 * Returns 0 if successful, -1 if either in or out is NULL,
 * and -2 if the dimensions of in and out are incompatible.
 */
int transpose(matrix * in, matrix * out) {
    if (!in || !out) return -1;
    if (in->rows != out->cols || in->cols != out->rows)
        return -2;

    int row, col;
    for (row = 1; row <= in->rows; row++)
        for (col = 1; col <= in->cols; col++)
            ELEM(out, col, row) = ELEM(in, row, col);
    return 0;
}

/* Writes the sum of matrices mtx1 and mtx2 into matrix
 * sum. Returns 0 if successful, -1 if any of the matrices
 * are NULL, and -2 if the dimensions of the matrices are
 * incompatible.
 */
int sum(matrix * mtx1, matrix * mtx2, matrix * sum) {
    if (!mtx1 || !mtx2 || !sum) return -1;
    if (mtx1->rows != mtx2->rows ||
            mtx1->rows != sum->rows ||
            mtx1->cols != mtx2->cols ||
            mtx1->cols != sum->cols)
        return -2;

    int row, col;
    for (col = 1; col <= mtx1->cols; col++)
        for (row = 1; row <= mtx1->rows; row++)
            ELEM(sum, row, col) =
                ELEM(mtx1, row, col) + ELEM(mtx2, row, col);
    return 0;
}

/* Writes the product of matrices mtx1 and mtx2 into matrix
 * prod.  Returns 0 if successful, -1 if any of the
 * matrices are NULL, and -2 if the dimensions of the
 * matrices are incompatible.
 */
int product(matrix * mtx1, matrix * mtx2, matrix * prod) {
    if (!mtx1 || !mtx2 || !prod) return -1;
    if (mtx1->cols != mtx2->rows ||
            mtx1->rows != prod->rows ||
            mtx2->cols != prod->cols)
        return -2;

    int row, col, k;
    for (col = 1; col <= mtx2->cols; col++)
        for (row = 1; row <= mtx1->rows; row++) {
            double val = 0.0;
            for (k = 1; k <= mtx1->cols; k++)
                val += ELEM(mtx1, row, k) * ELEM(mtx2, k, col);
            ELEM(prod, row, col) = val;
        }
    return 0;
}

/* Writes the dot product of vectors v1 and v2 into
 * reference prod.  Returns 0 if successful, -1 if any of
 * v1, v2, or prod are NULL, -2 if either matrix is not a
 * vector, and -3 if the vectors are of incompatible
 * dimensions.
 */
int dotProduct(matrix * v1, matrix * v2, double * prod) {
    if (!v1 || !v2 || !prod) return -1;
    if (v1->cols != 1 || v2->cols != 1) return -2;
    if (v1->rows != v2->rows) return -3;

    *prod = 0;
    int i;
    for (i = 1; i <= v1->rows; i++)
        *prod += ELEM(v1, i, 1) * ELEM(v2, i, 1);
    return 0;
}

int identity(matrix * m) {
    if (!m || m->rows != m->cols) return -1;
    int row, col;
    for (col = 1; col <= m->cols; col++)
        for (row = 1; row <= m->rows; row++)
            if (row == col)
                ELEM(m, row, col) = 1.0;
            else
                ELEM(m, row, col) = 0.0;
    return 0;
}

int isSquare(matrix * mtx) {
    return mtx && mtx->rows == mtx->cols;
}

int isDiagonal(matrix * mtx) {
    if (!isSquare(mtx)) return 0;
    int row, col;
    for (col = 1; col <= mtx->cols; col++)
        for (row = 1; row <= mtx->rows; row++)
            // if the element is not on the diagonal and not 0
            if (row != col && ELEM(mtx, row, col) != 0.0)
                // then the matrix is not diagonal
                return 0;
    return 1;
}

int isUpperTriangular(matrix * mtx) {
    if (!isSquare(mtx)) return 0;
    int row, col;
    // looks at positions below the diagonal
    for (col = 1; col <= mtx->cols; col++)
        for (row = col+1; row <= mtx->rows; row++)
            if (ELEM(mtx, row, col) != 0.0)
                return 0;
    return 1;
}

int diagonal(matrix * v, matrix * mtx) {
    if (!v || !mtx ||
            v->cols > 1 || v->rows != mtx->rows ||
            mtx->cols != mtx->rows)
        return -1;
    int row, col;
    for (col = 1; col <= mtx->cols; col++)
        for (row = 1; row <= mtx->rows; row++)
            if (row == col)
                ELEM(mtx, row, col) = ELEM(v, col, 1);
            else
                ELEM(mtx, row, col) = 0.0;
    return 0;
}

/* EXAMPLE
 *
 * int main() {
 matrix * A;

 A = newMatrix(10, 10);

 setElement(A, 1, 1, 1);
 setElement(A, 1, 2, 2);
 setElement(A, 1, 3, 1);
 setElement(A, 2, 2, 4);
 setElement(A, 2, 3, 3);
 setElement(A, 3, 2, 1);
 setElement(A, 3, 3, 3);


 printMatrix(A);

 unsigned val;
 getElement(A,1,1,&val);
 printf("%u", val);
 deleteMatrix(A);
 return 0;
 }*/
