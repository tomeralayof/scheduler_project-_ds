#ifndef __HASH_H__
#define __HASH_H__

#include <stddef.h> /* size_t */

typedef struct hash hash_t;

typedef int (*hash_cmp_func_t)(const void *key1, const void *key2);

typedef const void *(*hash_get_key_func_t)(const void *data);

typedef size_t (*hash_func_t)(const void *key);

typedef int (*hash_action_func_t)(void *value, void *param);
/* hash_action_func_t cannot change the data! */


/* Description:
 * Creates hash table.
 *
 * Parameters:
 * size - the number of indexes the table consists of.
 * get_key - a function that generates a key to a value.
 * cmp_func - a function that compares two data items.
 * hash_func - a function that determine an index to a key.
 *
 * Return:
 * A pointer to the new hash table.
 * 
 *Complexity: time O(1) or O(m) (your choice), space O(m)*/
hash_t *HashCreate(size_t size, hash_get_key_func_t get_key, 
			hash_cmp_func_t cmp_func, hash_func_t hash_func);

/* Description:
 * Destroys existing hash table. 
 *
 * Parameters:
 * hash - the hash table to be destroyed.
 *
 * Return:
 * None.
 *
 * Complexity: time O(n) space O(1)*/
void HashDestroy(hash_t *hash);

/* Description:
 * Inserts data to hash table.
 *
 * Parameters:
 * hash - hash table.
 * data - data to be inserted.
 *
 * Return:
 * status - 0 for success, 1 for failure. 
 *
 * Complexity: time O(1) (amortized), space O(1)*/
int HashInsert(hash_t *hash, void *data);


/* Descrition:
 * Removes data from hash table.
 * 
 * Parameters:
 * hash - hash table.
 * key - to be removed data's key.
 *
 * Rerturn:
 * None.
 *
 * Complexity: time O(1) (amortized), space O(1)*/
void HashRemove(hash_t *hash, const void *key);

/* Description:
 * Finds data in hash table.
 * 
 * Parameters:
 * hash - hash table.
 * key - Looked up data's key.
 *
 * Return:
 * Looked up data.
 *
 * Complexity: time O(1) (amortized), space O(1)*/
void *HashFind(const hash_t *hash, const void *key);

/* Description:
 * Counts the data items in hash table.
 *
 * Parameters:
 * hash - hash table.
 *
 * Return:
 * Number of data items in size_t.
 *
 * Complexity: time O(1) space O(1)*/
size_t HashSize(const hash_t *hash);

/* Description:
 * Checks if hash table is empty.
 *
 * Parameters:
 * hash - hash table.
 *
 * Return:
 * boolean - 1 in case empty, 0 in case not empty.
 *
 * Complexity: time O(m) space O(1)*/
int HashIsEmpty(const hash_t *hash);

/* Description:
 * Performs an action on all data items in the table.
 *
 * Parameters:
 * hash - hash table.
 * action_func - a function that performs an action on data.
 * param - a parameter required by action_func.
 *
 * Complexity: time O(n) space O(1)*/ /* it cannot change the data! */
int HashForEach(const hash_t *hash, hash_action_func_t action_func, void *param);


#ifdef DEBUG
void PrintIntHash(hash_t *hash);
#endif

#endif /* __HASH_H__*/