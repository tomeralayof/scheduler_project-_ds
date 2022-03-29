/*****************************************************************************
 *** Written by:    Tomer Alayof                                            ***
 *** Date:          13/2/22                                                 ***
 *** Reviewer:      Eudi 		                                            ***
 \*****************************************************************************
 *** Description:                                                           ***
 *** implementation for knight tour.	                                    ***
 ******************************************************************************
 \*****************************************************************************/

#include <stdio.h> /*printf()*/
#include <limits.h> /*ULONG_MAX*/
#include <stdlib.h> /*qsort()*/
#include <assert.h> /*qsort()*/

#include "../include/knights_tour.h"
#include "../include/bit_array.h"

#define OUT_OF_LIMIT (98)
#define MAX_MOVES (8)

typedef struct Optional_idx idx_option_t;

 struct Optional_idx
{
        unsigned char key;
        size_t value;
};

enum status
{
    SUCCESS,
    FAILURE
};

/*move options*/
typedef unsigned char (*Knight_tour_move_t)(unsigned char idx);
static unsigned char DoubleUpLeft(unsigned char idx);
static unsigned char DoubleUpRight(unsigned char idx);
static unsigned char DoubleLeftUp(unsigned char idx);
static unsigned char DoubleRightUp(unsigned char idx);
static unsigned char DoubleLeftDown(unsigned char idx);
static unsigned char DoubleRightDown(unsigned char idx);
static unsigned char DoubleDownLeft(unsigned char idx);
static unsigned char DoubleDownRight(unsigned char idx);
static const Knight_tour_move_t lut_moves[MAX_MOVES] = {
    &DoubleUpLeft,
    &DoubleUpRight,
    &DoubleLeftUp,
    &DoubleRightUp,
    &DoubleLeftDown,
    &DoubleRightDown,
    &DoubleDownLeft,
    &DoubleDownRight
};

static void BacktrecingSolution(bits_arr64_t moves,unsigned char pos,unsigned char *tour, int index_tabls);

/*Wansdrof*/
int WansdrofSolution(bits_arr64_t moves,unsigned char pos,unsigned char *tour, int index_tabls);
static unsigned int SortMoves(unsigned char pos,struct Optional_idx *arr_min);
static int Compare(const void *struct1, const void *struct2);
static const size_t index_possibilities[64] =
{
    2, 3, 4, 4, 4, 4, 3, 2,
    3, 4, 6, 6, 6, 6, 4, 3,
    4, 6, 8, 8, 8, 8, 6, 4,
    4, 6, 8, 8, 8, 8, 6, 4,
    4, 6, 8, 8, 8, 8, 6, 4,
    4, 6, 8, 8, 8, 8, 6, 4,
    3, 4, 6, 6, 6, 6, 4, 4,
    2, 3, 4, 4, 4, 4, 3 ,2
};

void KnightsTour(unsigned char pos, unsigned char *tour)
{
    bits_arr64_t moves = 0;
    int index_tabls = 0;

    assert(pos >= 0 && pos < 64);
    assert(NULL != tour);

    WansdrofSolution(moves,pos,tour, index_tabls);
    /*BacktrecingSolution(moves,pos,tour,index_tabls);*/
}

static void BacktrecingSolution(bits_arr64_t moves,unsigned char pos,unsigned char *tour, int index_tabls)
{
    int i = 0;
    int result = 0;

    if (moves == ULONG_MAX)
    {
        return;
    }
    if (ON == BitArrayGetVal(moves,pos))
    {
        return;
    }

    moves = BitArraySetOn(moves,(unsigned int)pos);
    tour[index_tabls] = pos;

    for (i = 0; i < MAX_MOVES ; i++)
    {
        result = lut_moves[i](pos);

        if(result != OUT_OF_LIMIT)
        {
            BacktrecingSolution(moves,result,tour,index_tabls + 1);
        }
    }
}

int WansdrofSolution(bits_arr64_t moves,unsigned char pos,unsigned char *tour, int index_tabls)
{
    idx_option_t arr[MAX_MOVES];
    int size = 0;
    int i = 0;

    if (moves == ULONG_MAX)
    {
        return SUCCESS;
    }
    if (ON == BitArrayGetVal(moves,pos))
    {
        return FAILURE;
    }

    moves = BitArraySetOn(moves,(unsigned int)pos);
    tour[index_tabls] = pos;

    size = SortMoves(pos,arr);

    for (i = 0; i < size; i++)
    {
        if (SUCCESS == WansdrofSolution(moves,arr[i].key,tour,index_tabls +1))
        {
             return SUCCESS;
        }     
    }

    return FAILURE;
}

static unsigned int SortMoves(unsigned char pos,idx_option_t *arr_min)
{
    int i = 0; 
    int counter = 0;

    for (i = 0; i < MAX_MOVES; i++)
    {
       int result = lut_moves[i](pos);

        if (result != OUT_OF_LIMIT)
        {
            arr_min[counter].key = result;
            arr_min[counter].value = index_possibilities[result];
            ++counter;
        }       
    }

    qsort(arr_min,counter,sizeof(idx_option_t),&Compare);

    return counter;
}

static int Compare(const void *struct1, const void *struct2)
{
    return ((idx_option_t *)struct1)->value - ((idx_option_t *)struct2)->value;
}

static unsigned char DoubleUpLeft(unsigned char idx)
{
    if(idx % 8 == 0 || idx < 17)
    {
        return OUT_OF_LIMIT;
    }
    return idx - 17;
}

static unsigned char DoubleUpRight(unsigned char idx)
{
    if(idx % 8 == 7 || idx < 16)
    {
        return OUT_OF_LIMIT;
    }
    return idx - 15;
}

static unsigned char DoubleLeftUp(unsigned char idx)
{
    if((idx % 8 <= 1) || idx < 10)
    {
        return OUT_OF_LIMIT;
    }

    return idx - 10;
}

static unsigned char DoubleRightUp(unsigned char idx)
{
    if (idx < 8 || idx % 8 >= 6)
    {
        return OUT_OF_LIMIT;
    }   
    return idx - 6;
}

static unsigned char DoubleLeftDown(unsigned char idx)
{
    if (idx < 2 || (idx % 8 <= 1))
    {
        return OUT_OF_LIMIT;
    }
    return idx + 6;
}

static unsigned char DoubleRightDown(unsigned char idx)
{
    if (idx > 61 || idx % 8 >= 6)
    {
        return OUT_OF_LIMIT;
    }
    
    return idx + 10;
}

static unsigned char DoubleDownLeft(unsigned char idx)
{
    if ((idx < 1 || idx > 47) || (idx % 8 == 0))
    {
        return OUT_OF_LIMIT;
    }
    
    return idx + 15;
}

static unsigned char DoubleDownRight(unsigned char idx)
{
    if (idx > 46 || idx % 8 == 7)
    {
        return OUT_OF_LIMIT;
    }
    
    return idx + 17;
}