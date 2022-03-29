#include <assert.h>         /* assert() */
#include <string.h>         /* memcpy() */
#include <stdlib.h>         /* malloc(), free(), size_t, NULL */

#include "../include/vector.h"

#define TO_BYTES(elem_size, index) ((index) * (elem_size))


typedef enum error
{
	MEM_ERR = -1,
	SUCCESS
} error_t;


struct vector
{
	size_t capacity;
	size_t elem_size;
	size_t size;
	char *start;
};


vector_t *VectorCreate(size_t element_size, size_t capacity)
{
	vector_t *vptr = malloc(sizeof(vector_t));
	if (NULL == vptr)
	{
		return NULL;
	}

	vptr->start = malloc(capacity * element_size);
	if (NULL == vptr->start)
	{
		free(vptr);
		vptr = NULL;
		return NULL;
	}

	vptr->capacity = capacity;
	vptr->elem_size = element_size;
	vptr->size = 0;

	return vptr;
}

void VectorDestroy(vector_t *vptr)
{
	assert(NULL != vptr);

	free(vptr->start);
	vptr->start = NULL;
	
	free(vptr);
	vptr = NULL;
}

void *VectorGetAccessToElement(vector_t *vptr, size_t index)
{
	assert(NULL != vptr);

	return (vptr->start + TO_BYTES(index, vptr->elem_size));
}

error_t VectorPushBack(vector_t *vptr, const void *element)
{
	assert(NULL != vptr);

    memcpy(vptr->start + TO_BYTES(vptr->size, vptr->elem_size), 
           element, vptr->elem_size);

    if (++vptr->size == vptr->capacity)
    {
    	vector_t *realloc_check = VectorReserve(vptr, vptr->capacity << 1);
    	if (NULL == realloc_check)
		{
			return MEM_ERR;
		}
    }

    return SUCCESS;
}

void VectorPopBack(vector_t *vptr)
{
	assert(NULL != vptr);

	if (0 == vptr->size)
	{
		return;
	}

	if (--vptr->size < vptr->capacity >> 2)
	{
		vector_t *new_vector = VectorReserve(vptr, vptr->capacity >> 1);
		if (NULL == new_vector)
		{
			return;
		}
	}
}

size_t VectorSize(const vector_t *vptr)
{
	assert(NULL != vptr);

	return vptr->size;
}

size_t VectorCapacity(const vector_t *vptr)
{
	assert(NULL != vptr);

	return vptr->capacity;
}

vector_t *VectorReserve(vector_t *vptr, size_t new_size)
{
	char *new_start = NULL;
	assert(NULL != vptr);

	new_start = realloc(vptr->start, TO_BYTES(new_size, vptr->elem_size));
	if (NULL == new_start)
	{
		return NULL;
	}

	vptr->start = new_start;
	vptr->capacity = new_size;

	return vptr;
}



/*
#include <string.h> 
#include <assert.h> 

#include "../include/vector.h"

#define EMPTY (0)
#define GROWTH_RATE (2)
#define RESIZE_FACTOR (4)

enum
{
	FAILURE = -1,
	SUCCESS = 0
};

struct vector  
{
	size_t num_of_element;
	size_t size_of_each_element;
	size_t num_of_occupied_element;
	void ** vector_start;
};

vector_t *VectorCreate(size_t element_size, size_t capacity)
{
	vector_t *vector = (vector_t *)malloc(sizeof(vector_t));	
	if(NULL == vector )
	{
		return NULL;
	}
	
	vector -> num_of_element = capacity;
	vector -> size_of_each_element = element_size;
	vector -> num_of_occupied_element = EMPTY;
	
	vector -> vector_start = (void *)malloc(sizeof(element_size) * sizeof(capacity));
	
	if(NULL == vector -> vector_start)
	{
		free(vector);
		vector = NULL;
		
		return NULL;
	}
	
	return vector;
}

int VectorPushBack(vector_t *vptr,const void *element)
{
	
	assert(NULL != vptr);
	
	if (vptr -> num_of_element == vptr -> num_of_occupied_element)
	{	
		VectorReserve(vptr, vptr -> num_of_element * GROWTH_RATE);
		
		if (NULL == vptr -> vector_start)
		{
			return FAILURE;
		}
	}

	memcpy(vptr -> vector_start + vptr -> num_of_occupied_element, element ,vptr -> size_of_each_element);	
	++(vptr -> num_of_occupied_element);

	return SUCCESS;

}

void *VectorGetAccessToElement(vector_t *vprt, size_t index)
{
	assert(NULL != vprt);
	
	return vprt -> vector_start + index;
}

size_t VectorCapacity(const vector_t *vptr)
{
	assert(NULL != vptr);

	return vptr -> num_of_element;
}


size_t VectorSize(const vector_t *vptr)
{
	
	assert(NULL != vptr);

	return vptr -> num_of_occupied_element;
}
 

void VectorDestroy(vector_t *vptr)
{

	assert(NULL != vptr);

	free(vptr -> vector_start);
	vptr -> vector_start = NULL;
	
	free(vptr);
	vptr = NULL;
}

void VectorPopBack(vector_t *vptr)
{
	
	assert(NULL != vptr);	
	
	--(vptr -> num_of_occupied_element);
	
	if ( vptr -> num_of_occupied_element <= (( vptr -> num_of_element) / RESIZE_FACTOR))
	{
		VectorReserve(vptr, vptr -> num_of_element / GROWTH_RATE);
	}
	
}


vector_t *VectorReserve(vector_t *vptr, size_t new_size)
{
	
	assert(NULL != vptr);
	
	vptr -> vector_start = realloc(vptr -> vector_start ,sizeof(void *) * (new_size) * (vptr -> size_of_each_element));
	
	if( NULL == vptr -> vector_start)	
	{
		return NULL;
	}
	
	vptr -> num_of_element = new_size;
	
	
	return vptr;
}
*/



