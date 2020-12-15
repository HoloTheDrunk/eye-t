#include "segmentation.h"
#include "image_load.h"
#include "types/tuple.h"
#include "types/matrix.h"
#include "types/binary_tree.h"




int WhiteLine(Matrix* matrix, int y) // TETED
{
    for(int x = 0; x < matrix->width; x++)
    {
        if (GetElement(matrix,x,y) == 0)
        {
            return 0;
        }
    }
    return 1;
}


int WhiteColumn(Matrix* matrix, int x) // TESTED
{
    for(int y = 0; y < matrix->height; y++)
    {
        if (GetElement(matrix,x,y) == 0)
        {
            return 0;
        }
    }
    return 1;

}


Matrix* CopyMatrix(Matrix* matrix, int x1 , int x2, int y1, int y2) // TESTED
{
    Matrix* newOne = NewMatrix(x2-x1+1, y2-y1+1);

    for(int x = x1; x < x2 + 1; x++)
    {
        for(int y = y1; y < y2 + 1; y++)
        {
            SetElement(newOne, x-x1, y-y1,  GetElement(matrix,x,y) );
        }
    }
    return newOne;
}



Matrix* ClearBounds(Matrix* matrix) // TESTED
{
    int LowerBound_y = 0;
    int UpperBound_y = 0;
    int LeftBound_x  = 0;
    int RightBound_x = 0;
    for(int y = 0; y != matrix->height; y++)
    {
        if (!WhiteLine(matrix,y))
        {
            UpperBound_y = y;
            break;
        }
    }
    for (int y = matrix->height-1 ; y >= 0; y--)
    {
        if (!WhiteLine(matrix,y))
        {
            LowerBound_y = y;
            break;
        }
    }
    for(int x = 0; x != matrix->width; x++)
    {
        if (!WhiteColumn(matrix,x))
        {
            LeftBound_x = x;
            break;
        }
    }
    for (int x = matrix->width-1 ; x >= 0; x--)
    {
        if (!WhiteColumn(matrix,x))
        {
            RightBound_x = x;
            break;
        }
    }

    Matrix* clearedmatrix =
        CopyMatrix(matrix, LeftBound_x, RightBound_x,
                UpperBound_y, LowerBound_y);
    return clearedmatrix;
}


int FindHorPic(Matrix* matrix) // TESTED
{
    int y = 0;
    int res = 0;
    int y_index = 0;
    int height = matrix->height;
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


int SpaceValue(Matrix* matrix) // TESTED
{
    int white_pixel_count = 0;
    int space_count = 0;
    int before_was_black = 0;
    int width = matrix->width;
    for (int i = 0; i < width ; i++)
    {
        if (WhiteColumn(matrix, i) == 1 && before_was_black == 0)
        {
            before_was_black += 1;
            white_pixel_count += 1;
            space_count  += 1;
        }
        else
        {
            if (WhiteColumn(matrix,i) == 1)
                white_pixel_count += 1;
            else
                before_was_black = 0;
        }
    }
    if (space_count ==  0)
    {
        printf("SPACE VALUE\n");
        return 0;
    }
    return (white_pixel_count / space_count) + 1;
}


int IsWords(Matrix* matrix, int space_value) // TESTED
{
    int before = 0;
    int count = 0;
    for(int x = 0; x != matrix->width ;x++)
    {
        if (WhiteColumn(matrix,x))
        {
            count++;
            if (!before)
                before = 1;
        }
        else
        {
            if (before && count > space_value)
                return 0;
            else
            {
                count = 0;
                before = 0;
            }
        }
    }
    return 1;
}

int FindVerPic(Matrix* matrix, int is_words)  // TESTED
{
    int x = 0;
    int res = 0;
    int x_index = 0;
    int width = matrix->width;
    int whitecolumn_found = 1;
    if (is_words != 0)
    {
        for (int i = 0; i < width; i++)
        {
            if (WhiteColumn(matrix,i) == 1 && whitecolumn_found == 1)
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
                if (WhiteColumn(matrix,i) == 0 && whitecolumn_found == 0)
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
            if (WhiteColumn(matrix,i) == 1 && whitecolumn_found == 1)
            {
                whitecolumn_found = 0;
                white_pixel_count += 1;
            }
            else
            {
                if (WhiteColumn(matrix,i) == 1 && whitecolumn_found == 0)
                {
                    white_pixel_count += 1;
                }
                else
                {
                    if (WhiteColumn(matrix,i) == 0 && whitecolumn_found == 0)
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

Matrix* CutHorUpper(Matrix* matrix1, int y) // TESTED
{
    int width = matrix1->width;
    Matrix* uppermatrix = CopyMatrix(matrix1,0,width-1,0,y-1);
    return uppermatrix;
}


Matrix* CutHorLower(Matrix* matrix1, int y) // TESTED
{
    int width = matrix1->width;
    int height = matrix1->height;
    Matrix* lowermatrix = CopyMatrix(matrix1,0,width-1, y ,height-1);
    return lowermatrix;
}


Matrix* CutVerLeft(Matrix* matrix1, int x)  // TESTED
{
    int height = matrix1->height;
    Matrix* leftmatrix = CopyMatrix(matrix1,0,x,0,height-1);
    return leftmatrix;
}
//Returns the left side of the matrix with regards to x.

Matrix* CutVerRight(Matrix* matrix1, int x)  // TESTED
{
    int width = matrix1->width;
    int height = matrix1->height;
    Matrix* rightmatrix = CopyMatrix(matrix1,x,width-1,0,height-1);
    return rightmatrix;
}


int IsLine(Matrix* matrix) //14
{
    int height = matrix->height;
    for (int j = 0; j < height; j++)
    {
        if (WhiteLine(matrix,j))
        {
            return 0;
        }
    }
    return 1;
}


int IsLetter(Matrix* matrix) //15
{
    int width = matrix->width;
    int height = matrix->height;
    for (int i = 1; i < width; i++)
    {
        if (WhiteColumn(matrix,i))
        {
            return 0;
        }
        for (int j = 0; j < height ; j++)
        {
            if (WhiteLine(matrix,j))
                return 0;
        }
    }
    return 1;
}


BinTree* SegmentationRec(BinTree* bintree)//17
{
    Matrix* originalmatrix = bintree->key;
    Matrix* matrix = ClearBounds(originalmatrix);
    if (IsLetter(originalmatrix))
    {
        return bintree;
    }


    if (IsLine(matrix))
    {
        int space_value = SpaceValue(matrix);
        int is_words = IsWords(matrix, space_value);

        Matrix* leftmatrix = CutVerLeft(matrix,FindVerPic(matrix,is_words));

        Matrix* rightmatrix = CutVerRight(matrix,FindVerPic(matrix,is_words));

        if (is_words)
        {
            bintree->txt = ' ';
        }
        else
        {
            bintree->txt = '.';
        }
        bintree->left = NewBinTree(ClearBounds(leftmatrix));
        bintree->right = NewBinTree(ClearBounds(rightmatrix));
        //MatBT_Print(bintree->right);
        //MatBT_Print(bintree->left);
        SegmentationRec(bintree->left);
        SegmentationRec(bintree->right);

    }
    else
    {
        bintree->txt = '\n';
        Matrix* uppermatrix = CutHorUpper(matrix,FindHorPic(matrix));
        Matrix* lowermatrix = CutHorLower(matrix,FindHorPic(matrix));
        bintree->left = NewBinTree(ClearBounds(uppermatrix));
        bintree->right = NewBinTree(ClearBounds(lowermatrix));
        SegmentationRec(bintree->left);
        SegmentationRec(bintree->right);
    }
    return bintree;
}


BinTree* Segmentation(SDL_Surface* image) //16
{
    Matrix* matrix = Image_To_Matrix(image, image->w, image->h);
    BinTree* bintree = NewBinTree(matrix);

    return SegmentationRec(bintree);

}

void  SegmentationTest(SDL_Surface* image)
{

    BinTree* bintree = Segmentation(image);
    Resize_Leaves(bintree,28,28);
    MatBT_Print(bintree);
    //Matrix* Test = NewMatrix(10,10);
    //PrintMatrix(ResizeMatrix(Test, 5 ,5));
}
