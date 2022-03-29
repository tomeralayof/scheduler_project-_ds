#ifndef __DYNAMIC_VECTOR_H__
#define __DYNAMIC_VECTOR_H__

#include <stdlib.h> /* size_t */


/*reviewed by gal tsaig */

typedef struct vector vector_t; 


/*	in c file
typedef struct vector
{
	size_t capacity;
	size_t element_size;
	size_t size;	
	void *start;
} vector_t; 
*/
	

/* DESCRIPTION: 
 * initialize a vector based on given param
 * 
 *
 * !at the end of use, call for VectorDestroy() to destroy!
 *
 * PARAMS: 
 * size_t capacity - initialize size of the vector
 * size_t element_size - size of an element that can be passed by the user
 *	
 * RETURN:
 * address of the created vector,
 * NULL in case of failure
 *
 * Complexity - time O(n) - space O(n)
 *
 */
vector_t *VectorCreate(size_t element_size, size_t capacity);


/* DESCRIPTION: 
 * free used resources.
 * must be called at the end of the vector usage 
 * 
 * PARAMS:
 * vector_t *vptr - pointer to the vector to be destroyed
 *
 * 
 * RETURN:
 * no return value.
 *
 * Complexity - time O(1) - space O(1)
 *
 */
void VectorDestroy(vector_t *vptr);


/* DESCRIPTION: 
 * return address of the requested element
 * index of the desired element (starting from index 0)
 *
 * PARAMS: 
 * vptr *vprt to the vector
 * index of the element
 * 
 *
 * RETURN:
 * address of the desired element
 * if index is out of boundaries is undefined behavior
 *
 * Complexity - time O(1) - space O(1)
 *
 */
void *VectorGetAccessToElement(vector_t *vprt, size_t index);


/* DESCRIPTION: 
 * add value of element to the end of the vector
 * it's the user's responsibility to check if the vector has enough capacity to add an element
 * if not enough capacity - undefined behavior 
 *
 * PARAMS: 
 * vector_t *vptr - pointer to the vector 
 * const void *element - pointer to the element to be added to the end
 * 
 * RETURN:
 * status of 0 for success or -1 failure
 *
 * Complexity - time O(1) - space O(1)
 *
 */
int VectorPushBack(vector_t *vptr,const void *element);


/* DESCRIPTION: 
 * removes the element from the end of the vector
 * 
 *
 * PARAMS: 
 * vector_t *vptr - pointer to the vector 
 * 
 *
 * RETURN:
 * no return value.
 *
 * Complexity - time O(1) - space O(1)
 *
 */
void VectorPopBack(vector_t *vptr);

/* DESCRIPTION: 
 * return the current amount of the elements in the vector
 * 
 * 
 *
 * PARAMS: 
 * const vector_t *vptr - pointer to the constant vector 
 * 
 *
 * RETURN:
 * number of elements currently in the vector
 *
 * Complexity - time O(1) - space O(1)
 *
 */
size_t VectorSize(const vector_t *vptr);



/* DESCRIPTION: 
 * returns vector's current max capacity
 * 
 * 
 *
 * PARAMS: 
 * const vector_t *vptr - pointer to the constant vector
 * 
 *
 * RETURN:
 * current max elements available in the vector
 *
 * Complexity - time O(1) - space O(1)
 *
 */
size_t VectorCapacity(const vector_t *vptr);



/* DESCRIPTION: 
 * Changes the vector capacity to the required new capacity.
 * If larger than current size, add more capacity otherwise shrink vector size 
 *
 * PARAMS: 
 * vector_t *vptr - pointer to vector 
 * size_t new_size - the new size of vector in bytes
 *
 * RETURN:
 * pointer to the newly re-allocated (resized) vector
 * null in case of failure
 *
 * Complexity - time O(n) - space O(n)
 *
 */
vector_t *VectorReserve(vector_t *vptr, size_t new_size);



#endif /* __DYNAMIC_VECTOR_H__ */





