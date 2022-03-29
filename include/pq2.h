#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include <stddef.h> /* size_t */

#include "heap.h"

typedef int (*pq_cmp_func_t)(const void *left, const void *right);
typedef int (*pq_match_func_t)(const void *data, const void *param);


typedef struct pqueue pq_t;

/**
 * DESCRIPTION:
 * Initialize a Priority Queue.
 * At end of use, QueueDestroy() must be called.
 * Complexity: O(1) time, O(1) space.
 * 
 * PARAMS:
 * None.
 * 
 * RETURN:
 * Pointer to the Queue.
 * NULL in case of memory allocation failure.
 */
pq_t *PQCreate(heap_cmp_func_t cmp_func);

/**
 * DESCRIPTION:
 * Frees resources used by a Queue.
 * Must be called at end of use of the Queue.
 * Complexity: O(n) time, O(1) space.
 * 
 * PARAMS:
 * Pointer to the Queue to destroy
 * 
 * RETURN:
 * None.
 */
void PQDestroy(pq_t *pq);

/**
 * DESCRIPTION:
 * Checks if the Queue is empty.
 * Complexity: O(1) time, O(1) space.
 * 
 * PARAMS:
 * A pointer to the Queue to check emptiness.
 * 
 * RETURN:
 * 1 if empty, else 0.
 */
int PQIsEmpty(const pq_t *pq);

/**
 * DESCRIPTION:
 * Counts the number of elements in a Queue.
 * Complexity: O(n) time, O(1) space.
 * 
 * PARAMS:
 * Pointer to the Queue to get size of.
 * 
 * RETURN:
 * Number of total elements in the Queue.
 */
size_t PQSize(const pq_t *pq);

/**
 * DESCRIPTION:
 * Inserts an element into the Queue.
 * Complexity: O(n) time, O(1) space.
 * 
 * PARAMS:
 * Pointer to Queue in which to insert.
 * Data to be inserted.
 * 
 * RETURN:
 * 0 if enqueued data successfully.
 * else -1 
 */
int PQEnqueue(pq_t *pq, void *data);

/**
 * DESCRIPTION:
 * Removes the top element in the Queue
 * Complexity: O(1) time, O(1) space.
 * 
 * PARAMS:
 * Pointer to Queue from which we wish to remove.
 * 
 * RETURN:
 * Data contained at the top of the Queue.
 */
void *PQDequeue(pq_t *pq);

/**
 * DESCRIPTION:
 * Returns the data contained at the top of the Queue
 * Complexity: O(1) time, O(1) space.
 * 
 * PARAMS:
 * Pointer to the Queue from which we wish to peek.
 * 
 * RETURN:
 * Data contained at the top of the Queue.
 */
void *PQPeek(const pq_t *pq);

/**
 * DESCRIPTION:
 * clear the queue
 * Complexity: O(n) time, O(1) space.
 * 
 * PARAMS:
 * Pointer to the Queue.
 * 
 * RETURN:
 * None
 */
void PQClear(pq_t *pq);

/**
 * DESCRIPTION:
 * clear the queue
 * Complexity: O(n) time, O(1) space.
 * 
 * PARAMS:
 * Pointer to the Queue.
 * match function 
 * param to check if is match to data
 * 
 * RETURN:
 * 0 if enqueued data successfully.
 * else -1 
 */
void *PQErase(pq_t *pq, heap_is_match_func_t match_func, void *param);

#endif /* __PRIORITY_QUEUE_H__ */