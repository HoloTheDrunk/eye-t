#include "tuple.h"

Tuple NewTuple()
{
    Tuple new_tuple;
    new_tuple.x = -1;
    new_tuple.y = -1;

    return new_tuple;
}


Tuple SetTuple(Tuple tuple, int index, int val)
{
    Tuple new_tuple;
    if (index == 1)
    {
        new_tuple.x = tuple.x;
        new_tuple.y = val;
    }
    else
    {
    tuple.x = val;
    new_tuple.y = tuple.y;
    }
    return new_tuple;
}

int SetTuple_Coord(Tuple tuple, int x, int y)
{
    tuple.x = x;
    tuple.y = y;
    PrintTuple(tuple);
    return 1;

}

int GetTuple(Tuple tuple,int index)
{
    if (index >= 1)
        return tuple.y;
    return tuple.x;
}

int IsTupleEmpty(Tuple tuple)
{
    if (tuple.x == -1 || tuple.y == -1)
         return 1;
    return 0;
}

void PrintTuple(Tuple tuple)
{
    printf("(%i, %i)\n", tuple.x, tuple.y);
}
