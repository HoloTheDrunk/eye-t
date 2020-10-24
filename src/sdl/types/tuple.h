#ifndef TUPLE_H
#define TUPLE_H

#include <stdio.h>

typedef struct {
    int x;
    int y;
} Tuple;


Tuple NewTuple();
Tuple SetTuple(Tuple tuple, int index, int val);
int GetTuple(Tuple tuple,int index);
void PrintTuple(Tuple tuple);
int IsTupleEmpty(Tuple tuple);
int SetTuple_Coord(Tuple tuple, int x, int y);

#endif
