#include "segmentation.h"
#include "image_load.h"
#include "types/tuple.h"
#include "types/matrix.h"
#include "types/binary_tree.h"

int WhiteLine(matrix* matrix, int y) //1
{
    int res = 0;
    int width = matrix->cols;
    for (int i = 0; i < width; i++)
    {
        unsigned * val = 0;
        getElement(matrix,i,y,val);
        if (*val == 1)
        {
            res += 1;
            break;
        }
    }
    return res;
}
//If y line in matrix is full of 0s return true else false

int WhiteColumn(matrix* matrix, int x) //2
{
    int res = 0;
    int height = matrix->rows;
    for (int j = 1; j < height; j++)
    {
        unsigned * val=0 ;
        unsigned val1 = 1;
        *val = val1;
        if (!getElement(matrix,x,j,val))
        {
            printf(" WIDTH : %x  HEIGHT : %u  J : %x  X : %i\n", matrix->rows, matrix->cols,j,x);
            errx(1, "Error line 32");
        }
        if (*val == 1)
        {
            res += 1;
            break;
        }
    }
    return res;
}
//If x column is full of 0s return true else false

matrix* CopyMatrix(matrix* matrix1,int upperbound, int lowerbound,  //3
        int leftbound, int rightbound)
{
    matrix* newmatrix ;
    newmatrix = newMatrix(lowerbound- upperbound,
            rightbound - leftbound);
    int height = lowerbound;
    int width = rightbound;
    for (int i = leftbound; i <= width; i++)
    {
        for (int j = upperbound; i <= height; j++)
        {
            unsigned *val_matrix = 0;
            getElement(matrix1, i, j, val_matrix);

            unsigned *val_newmatrix = 0;
            getElement(newmatrix, i-leftbound, j-upperbound, val_newmatrix);

            *val_newmatrix += *val_matrix;

            setElement(newmatrix, i-leftbound, j-upperbound, *val_newmatrix);

            // CODE ORIGINE :
            //  newmatrix[i-leftbound][j-upperbound] += matrix1[i][j];
        }
    }
    return newmatrix;
}
//ATTENTION newmatrix(y,x)
//Copy the matrix but only within the boundaries.

matrix* ClearHorBounds(matrix* matrix1) //4
{
    int upperbound = 0;
    int lowerbound = matrix1->rows - 1;
    int lastrow = matrix1->rows;
    int j = 0;
    int hightfound = 1;
    int lowfound = 1;
    while((hightfound == 1 || lowfound == 1) && j < lastrow)
    {
        if (WhiteLine(matrix1, upperbound+j) == 0 && hightfound == 1)
        {
            hightfound -= 1;
            upperbound += j;
        }
        if (WhiteLine(matrix1,lowerbound-j) == 0 && lowfound == 1)
        {
            lowfound -= 1;
            lowerbound -= j;
        }
        j += 1;
    }
    matrix* clearedmatrix =
        CopyMatrix(matrix1, upperbound, lowerbound, 0, matrix1->cols - 1);
    return clearedmatrix;
}
//Duplicates matrix but removes the white stripes belpw and above.


matrix* ClearVerBounds(matrix* matrix1) //5
{
    int leftbound = 0;
    int rightbound = matrix1->cols -1;
    int lastcol = matrix1->cols;
    int i = 0;
    int leftfound = 1;
    int rightfound = 1;
    while ((leftfound == 1 || rightfound == 1) && i < lastcol)
    {
        if (WhiteColumn(matrix1,leftbound+i) == 0 && leftfound == 1)
        {
            leftfound -= 1;
            leftbound += i;
        }
        if (WhiteColumn(matrix1,rightbound-i) == 0 && rightfound == 1)
        {
            rightfound -= 1;
            rightbound -= i;
        }
        i += 1;
    }
    matrix* clearedmatrix = CopyMatrix(matrix1,0,matrix1->rows-1,
            leftbound, rightbound);
    return clearedmatrix;
}
//Duplicates matrix but removes the white stripes left and right

int FindHorPic(matrix* matrix) //6
{
    int y = 0;
    int res = 0;
    int y_index = 0;
    int height = matrix->rows;
    int whiteline_found = 1;
    for (int j = 0; j < height; j++)
    {
        if (WhiteLine(matrix,j) == 0 && whiteline_found == 1)
        {
            whiteline_found = 0;
            y_index += 1;
            if (y_index/2 >= res)
            {
                res += 1;
                y = j;
            }
        }
        else
        {
            if (WhiteLine(matrix,j) == 1 && whiteline_found == 0)
            {
                whiteline_found = 1;
            }
        }
    }
    return y;
}
//Returns the position where to cut horizontally.
//Finds one white line between two non-white lines for each non-white lines.
//We then select the white line the most in the middle and return it's y
//coordinate.

int SpaceValue(matrix* matrix) //7
{
    int white_pixel_count = 0;
    int space_count = 0;
    int before_was_black = 0;
    int width = matrix->cols;
    for (int i = 0; i < width ; i++)
    {
        if (WhiteColumn(matrix, i) == 0 && before_was_black == 0)
        {
            before_was_black += 1;
            white_pixel_count += 1;
            space_count  += 1;
        }
        else
        {
            if (WhiteColumn(matrix,i) == 0)
            {
                white_pixel_count += 1;
            }
            else
            {
                before_was_black = 0;
            }
        }
    }
    return (white_pixel_count / space_count) + 1;
}
//Estimates the number of white pixels corresponding to a gap between words.
//If the gap between words is striclty  greater than the return value then
//the gap is a word space (and not a letter space).

int IsWords(matrix* matrix, int space_value)  //8
{
    int white_pixel_count = 0;
    int before_was_black = 0;
    int width = matrix->cols;
    for (int i = 0; i < width; i++)
    {
        if (WhiteColumn(matrix,i) == 0 && before_was_black == 0)
        {
            before_was_black += 1;
            white_pixel_count += 1;
            if (white_pixel_count > space_value)
            {
                return 0;
            }
        }
        else
        {
            if (WhiteColumn(matrix,i) == 0)
            {
                white_pixel_count += 1;
            }
            else
            {
                before_was_black = 0;
                white_pixel_count = 0;
            }

        }
    }
    return 1;
}
//Checks if the matrix (which is established to be a line) contains more than
//one word. If yes then it returns 0 else 1. If it returns 1 it implies that
//the matrix contains only one word or subword.

int FindVerPic(matrix* matrix, int is_words)  //9
{
    int x = 0;
    int res = 0;
    int x_index = 0;
    int width = matrix->cols;
    int whitecolumn_found = 1;
    if (is_words != 0)
    {
        for (int i = 0; i < width; i++)
        {
            if (WhiteColumn(matrix,i) == 0 && whitecolumn_found == 1)
            {
                whitecolumn_found = 0;
                x_index += 1;
                if (x_index/2 >= res)
                {
                    res += 1;
                    x = i;
                }
            }
            else
            {
                if (WhiteColumn(matrix,i) == 1 && whitecolumn_found == 0)
                {
                    whitecolumn_found = 1;
                }
            }
        }
    }
    else
    {
        int white_pixel_count = 0;
        int space_value = SpaceValue(matrix);
        for (int i = 0; i < width; i++)
        {
            if (WhiteColumn(matrix,i) == 0 && whitecolumn_found == 1)
            {
                whitecolumn_found = 0;
                white_pixel_count += 1;
            }
            else
            {
                if (WhiteColumn(matrix,i) == 0 && whitecolumn_found == 0)
                {
                    white_pixel_count += 1;
                }
                else
                {
                    if (WhiteColumn(matrix,i) == 1 && whitecolumn_found == 0)
                    {
                        whitecolumn_found = 1;
                        if (white_pixel_count > space_value)
                        {
                            x_index += 1;
                            if (x_index/2 >= res)
                            {
                                res += 1;
                                x = i-1;
                            }
                        }
                        white_pixel_count = 0;
                    }
                }
            }
        }
    }
    return x;
}
//Returns the position where to cut vertically.
//If the matrix represents a single word or a sub word then the function will
//check the spaces between characters. Else it will only check the spaces
//between words.
//We then select the space which has the x coordinate the most on the middle.


matrix* CutHorUpper(matrix* matrix1, int y) //10
{
    int width = matrix1->cols;
    matrix* uppermatrix = CopyMatrix(matrix1,0,y,0,width);
    return uppermatrix;
}
//Returns the upper half of the matrix with regards to y.

matrix* CutHorLower(matrix* matrix1, int y) //11
{
    int width = matrix1->cols;
    int height = matrix1->rows;
    matrix* lowermatrix = CopyMatrix(matrix1,y,height,0,width);
    return lowermatrix;
}
//Returns the lower half of the matrix with regards to y.

matrix* CutVerLeft(matrix* matrix1, int x)  //12
{
    int height = matrix1->rows;
    matrix* leftmatrix = CopyMatrix(matrix1,0,height,0,x);
    return leftmatrix;
}
//Returns the left side of the matrix with regards to x.

matrix* CutVerRight(matrix* matrix1, int x)  //13
{
    int width = matrix1->cols;
    int height = matrix1->rows;
    matrix* rightmatrix = CopyMatrix(matrix1,0,height,x,width);
    return rightmatrix;
}
//Returns the right side of the matrix with regards to x.

int IsLine(matrix* matrix) //14
{
    int height = matrix->rows;
    for (int j = 0; j < height; j++)
    {
        if (WhiteLine(matrix,j) == 1)
        {
            return 1;
        }
    }
    return 0;
}

int IsLetter(matrix* matrix) //15
{
    int width = matrix->cols;
    int height = matrix->rows;
    for (int i = 1; i < width; i++)
    {
        if (WhiteColumn(matrix,i) == 1)
        {
            return 1;
        }
        for (int j = 0; j < height ; j++)
        {
            if (WhiteLine(matrix,j) == 1)
            {
                return 1;
            }
        }
    }
    return 0;
}


BinTree* Segmentation(SDL_Surface* image) //16
{
    int width = image->w;
    int height = image->h;
    matrix* matrix = image_to_matrix(image, width, height);
    return SegmentationRec(matrix);

}

BinTree* SegmentationRec(matrix* originalmatrix) //17
{
    BinTree* bintree = NewBinTree(originalmatrix);
        if (IsLetter(originalmatrix) == 0)
        {
            return bintree;
        }

    matrix* intermatrix = ClearHorBounds(originalmatrix);
    matrix* matrix1 = ClearVerBounds(intermatrix);

    if (IsLine(matrix1) == 0)
    {
        int space_value = SpaceValue(matrix1);
        int is_words = IsWords(matrix1, space_value);
        matrix* leftmatrix = CutVerLeft(matrix1,FindVerPic(matrix1,is_words));
        matrix* rightmatrix = CutVerRight(matrix1,FindVerPic(matrix1,is_words));
        if (is_words)
        {
            bintree->txt = " ";
        }
        else
        {
            bintree->txt = "";
        }
        bintree->left = SegmentationRec(leftmatrix);
        bintree->right = SegmentationRec(rightmatrix);
    }
    else
    {
        bintree->txt = "\n";
        matrix* uppermatrix = CutHorUpper(matrix1,FindHorPic(matrix1));
        matrix* lowermatrix = CutHorLower(matrix1,FindHorPic(matrix1));
        bintree->left = SegmentationRec(uppermatrix);
        bintree->right = SegmentationRec(lowermatrix);
    }
    return bintree;
}
//Main function that represents the image with a binary tree where each node
//is the result of a text division.
