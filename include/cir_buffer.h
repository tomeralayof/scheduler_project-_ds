#ifndef __CBUFFER_H__
#define __CBUFFER_H__

#include <unistd.h> /* size_t ssize_t*/

typedef struct cbuffer cbuffer_t;

/* Time complexity O(1), Space complexity O(n)*/
/* DESCRIPTION: 
 * create a new circular buffer  
 *
 * PARAMS: 
 * the capacity of the new buffer
 *
 * RETURN:
 * Pointer to a circular buffer organizational structure
 */
cbuffer_t *CBuffCreate(size_t capacity);

/* Time complexity O(1), Space complexity O(1) */
/* DESCRIPTION: 
 * destroy circular buffer  
 *
 * PARAMS: 
 * cbuffer_t *buffer - circular buffer organizational structure
 *
 * RETURN:
 * none
 */
void CBuffDestroy(cbuffer_t *buffer);

/* Time complexity O(1), Space complexity O(1) */
/* DESCRIPTION: 
 * return the capacity of the buffer  
 *
 * PARAMS: 
 * cbuffer_t *buffer- circular buffer organizational structure
 *
 * RETURN:
 * capacity of a circular buffer
 */
size_t CBuffCapacity(const cbuffer_t *buffer);

/* Time complexity O(n), Space complexity O(1) */
/* DESCRIPTION: 
 * writing to the buffer count bytes from src
 *
 * PARAMS: 
 * cbuffer_t *buffer- circular buffer organizational structure
 * void *src - source to copy from 
 * size_t count - number of bytes to copy
 *
 * RETURN:
 * number of bytes wrote 
 * in case of writing to a fuul buffer -1 will returned
 */
ssize_t CBuffWrite(cbuffer_t *buffer,const void *src, size_t count);

/* Time complexity O(n), Space complexity O(1) */
/* DESCRIPTION: 
 * reading from the buffer count bytes to dest  
 *
 * PARAMS: 
 * cbuffer_t *buffer- circular buffer organizational structure
 * void *dest - destrntion to copy to 
 * size_t count - number of bytes to copy
 *
 * RETURN:
 * number of bytes read
 * in case of reading from empty buffer -1 will returned
 */
ssize_t CBuffRead(cbuffer_t *buffer, void *dest, size_t count);

/* Time complexity O(1), Space complexity O(1) */
/* DESCRIPTION: 
 * cheak if buffer is empty   
 *
 * PARAMS: 
 * cbuffer_t *buffer- circular buffer organizational structure
 *
 * RETURN:
 * 1 if empty 0 is not
 */
int CBuffIsEmpty(const cbuffer_t *buffer);

/* Time complexity O(1), Space complexity O(1) */
/* DESCRIPTION: 
 * cheak how much much free is avlible    
 *
 * PARAMS: 
 * cbuffer_t *buffer- circular buffer organizational structure
 *
 * RETURN:
 * 1 if empty 0 is not
 */
size_t CBuffFreeSpace(const cbuffer_t *buffer);

#endif /* __CBUFFER_H__ */

