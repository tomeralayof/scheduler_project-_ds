#include <stdlib.h> /*malloc*/
#include <stddef.h> /*offset*/
#include <string.h> /*memcpy*/
#include <assert.h> /*assert*/

#include "../include/cir_buffer.h"

/*reviewed by shaked*/

#define FAILURE (-1)
#define	MIN(a, b) ((a) > (b) ? (b) : (a))

struct cbuffer
{
    size_t capacity;
    size_t front;
    size_t size;
    char buffer[1];
};

cbuffer_t *CBuffCreate(size_t capacity)
{

	cbuffer_t *circular_buffer = (cbuffer_t *)malloc(capacity * sizeof(char) + offsetof(struct cbuffer,buffer));
	if(NULL == circular_buffer)
	{
		return NULL;
	}
	
	circular_buffer -> capacity = capacity;
	circular_buffer -> front = 0;
	circular_buffer -> size = 0;	
	
	return circular_buffer;
}

void CBuffDestroy(cbuffer_t *buffer)
{
	assert(NULL != buffer);
	
	free(buffer);
	buffer = NULL;
}


size_t CBuffCapacity(const cbuffer_t *buffer)
{
	assert(NULL != buffer);
	
	return buffer -> capacity;
}

int CBuffIsEmpty(const cbuffer_t *buffer)
{
	assert(NULL != buffer);
	
	return buffer -> size == 0;
}


ssize_t CBuffWrite(cbuffer_t *buffer,const void *src, size_t count)
{

	size_t free_space_to_end = 0;

	assert(NULL != buffer);
	assert(NULL != src);
	
	free_space_to_end =  buffer->capacity - buffer->front;
	
	count = MIN(count,CBuffFreeSpace(buffer));
	
	if (!CBuffFreeSpace(buffer))
	{
		return FAILURE;
	}
	
	if(count > free_space_to_end)
	{				
		memcpy(buffer->buffer + ((buffer->size + buffer->front) % buffer->capacity) , (char *)src ,free_space_to_end);
		memcpy(buffer->buffer, (char *)src + free_space_to_end, count - free_space_to_end);
		buffer->size+=count;
	}	
	else 
	{
		memcpy(buffer->buffer + buffer->size + buffer->front, (char *)src ,count);	
		buffer->size+=count;
	}

	return count;
}

ssize_t CBuffRead(cbuffer_t *buffer, void *dest, size_t count)
{

	size_t free_space_to_end = 0;
	
	assert(NULL != buffer);
	assert(NULL != dest);
	
	count = MIN(count,buffer->size);
	
	free_space_to_end = buffer->capacity - buffer->front;
	
	if (CBuffIsEmpty(buffer))
	{
		return FAILURE;
	}
	
	if (count > free_space_to_end)	
	{	
		memcpy((char *) dest, buffer->buffer + buffer->front,free_space_to_end);
		memcpy((char *) dest + free_space_to_end , buffer->buffer , count - free_space_to_end);
		buffer->front=(buffer->front + count) % buffer->capacity;
		buffer->size-=count;
	}	
	else 
	{
		memcpy((char *) dest, buffer->buffer + buffer->front ,count);	
		buffer->front+=count;
		buffer->size-=count;
	}
		
	return count;
}

size_t CBuffFreeSpace(const cbuffer_t *buffer)
{
	assert(NULL != buffer);
	
	return buffer->capacity - buffer->size;
}







