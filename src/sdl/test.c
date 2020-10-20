#include "types/tuple.h"
//#include "types/matrix.h"

void Put_Tuple(Tuple* parr, int x, int y, size_t len ) ;


int main()
{
    Tuple tuple_list[3];
    for(int i = 0; i != 3; i++)
    {
        tuple_list[i] = NewTuple();
        PrintTuple(tuple_list[i]);
    }
    tuple_list[0].x = 1;
    tuple_list[0].y = 2;
    Put_Tuple(tuple_list, 4, 5, 3);
    for(int i = 0; i != 3; i++)
    {
        PrintTuple(tuple_list[i]);
    }
}


void Put_Tuple(Tuple parr[], int x, int y, size_t len)  // FONCTIONNE BIEN A PRIORIS A REVOIR QUAND MEME !
{
    printf("It begins there : \n");
    for(unsigned int i = 0; i != len ; i++)
    {
        if (IsTupleEmpty(parr[i]))
        {
            parr[i].x = x;
            parr[i].y = y;
            break;
        }
    }
}
