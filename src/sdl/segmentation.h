#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_

#include "stdlib.h"
#include "SDL/SDL.h"
#include "SDl/SDL_image.h"
#include "types/matrix.h"
#include "types/binary_tree.h"


int WhiteLine(matrix* matrix, int y); //1
int WhiteColumn(matrix* matrix, int x);//2
matrix* CopyMatrix(matrix* matrix, int upperbound, int lowerbound,
		int leftbound,	int rightbound);//3
matrix* ClearHorBounds(matrix* matrix);//4
matrix* ClearVerBounds(matrix* matrix);//5
int FindHorPic(matrix* matrix);//6
int SpaceValue(matrix* matrix);//7
int IsWords(matrix* matrix, int space_value);//8
int FindVerPic(matrix* matrix, int is_words);//9
matrix* CutHorUpper(matrix* matrix, int y);//10
matrix* CutHorLower(matrix* matrix, int y);//11
matrix* CutVerLeft(matrix* matrix, int x);//12
matrix* CutVerRight(matrix* matrix, int y);//13
int IsLine(matrix* matrix);//14
int IsLetter(matrix* matrix);//15
BinTree* Segmentation(SDL_Surface image);//16
BinTree* SegmentationRec(matrix* matrix);//17
#endif
