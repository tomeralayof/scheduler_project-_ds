/*****************************************************************************
 *** Written by:    Tomer Alayof                                            ***
 *** Date:          01/02/22                                                ***
 *** Reviewer:      Shoshana 		                                        ***
 \*****************************************************************************
 *** Description:                                                           ***
 *** implementation for hash.	                                            ***
 ******************************************************************************
 \*****************************************************************************/

#include <stdlib.h> /*malloc()*/
#include <assert.h> /*assert()*/

#ifdef DEBUG	
	#include <stdio.h> /*printf()*/
#endif

#include "../include/hash.h"
#include "../include/dll.h"

struct hash
{
	hash_cmp_func_t cmp_func;
	hash_func_t hash_func;
	hash_get_key_func_t get_key;
	size_t size;
	dlist_t **table;
};

enum bool
{
	FALSE,
	TRUE
};

enum status
{
	SUCCESS = 0,
	FAILURE = 1
};

static hash_t *InitHash(size_t size, hash_get_key_func_t get_key, hash_cmp_func_t cmp_func, hash_func_t hash_func,hash_t *hash);
static dlist_iter_t PromoteIter(dlist_iter_t start, dlist_iter_t end,const void *key,const hash_t *hash);

#ifdef DEBUG
	static int PrintInt(void *data, void *param);
#endif

hash_t *HashCreate(size_t size, hash_get_key_func_t get_key, hash_cmp_func_t cmp_func, hash_func_t hash_func)
{
	hash_t *hash = NULL;

	assert(NULL != cmp_func);
	assert(NULL != hash_func);
	assert(NULL != get_key);
	assert(0 < size);

	hash = (hash_t *)malloc(sizeof(hash_t));
	if (NULL == hash)
	{
		return NULL;
	}

	hash = InitHash(size, get_key, cmp_func, hash_func,hash);

	return hash;
}

void HashDestroy(hash_t *hash)
{
	size_t i = 0;
	size_t size = 0;

	assert(NULL != hash);

	size = hash->size;

	for (i = 0; i < size; ++i)
	{
		DListDestroy(hash->table[i]);
		hash->table[i] = NULL;
	}

	free(hash->table);
	hash->table = NULL;

	free(hash);
	hash = NULL;
}

int HashIsEmpty(const hash_t *hash)
{
	int is_empty = TRUE;
	size_t i = 0;

	assert(NULL != hash);

	for (i = 0; i < hash->size && is_empty; ++i)
	{
		is_empty = DListIsEmpty(hash->table[i]);
	}

	return is_empty;
}

size_t HashSize(const hash_t *hash)
{
	size_t i = 0;
	size_t size = 0;
	size_t count = 0;

	assert(NULL != hash);

	size = hash->size;

	for (i = 0; i < size ; ++i)
	{
		count += DListSize(hash->table[i]);
	}

	return count;
}

int HashInsert(hash_t *hash, void *data)
{
	const void *key = NULL;
	size_t idx = 0;
	dlist_iter_t runner = NULL;
	int is_found = TRUE;

	assert(NULL != hash);
	assert(NULL != data);

	key = hash->get_key(data);
	idx = hash->hash_func(key);

	assert(idx < hash->size);

	runner = PromoteIter(DListBegin(hash->table[idx]),DListEnd(hash->table[idx]),key,hash);
	is_found = DListIsEqual(runner,DListEnd(hash->table[idx]));

	assert(TRUE == is_found);

	return  DListIsEqual(DListEnd(hash->table[idx]),DListPushFront(hash->table[idx],data)) ? FAILURE : SUCCESS;
}

void HashRemove(hash_t *hash, const void *key)
{
	size_t idx = 0;
	dlist_iter_t start = NULL;
	dlist_iter_t end =  NULL;

	assert(NULL != hash);
	assert(NULL != key);

	idx = hash->hash_func(key);
	start = DListBegin(hash->table[idx]);
	end =  DListEnd(hash->table[idx]);

	start = PromoteIter(start,end,key,hash);

	if (!DListIsEqual(start,end))
	{
		DListRemove(start);
	}
}

void *HashFind(const hash_t *hash, const void *key)
{
	int idx = hash->hash_func(key);
	dlist_iter_t start = DListBegin(hash->table[idx]);
	dlist_iter_t end =  DListEnd(hash->table[idx]);

	start = PromoteIter(start,end,key,hash);

	return DListIsEqual(start,end) ? NULL : DListGetData(start);
}

static dlist_iter_t PromoteIter(dlist_iter_t start, dlist_iter_t end,const void *key,const hash_t *hash)
{	
	while (!DListIsEqual(start,end) && 0 != hash->cmp_func(hash->get_key(DListGetData(start)), key))
	{
		start = DListNext(start);
	}

	return start;
}

int HashForEach(const hash_t *hash, hash_action_func_t action_func, void *param)
{
	size_t i = 0; 
	int status = SUCCESS;

	assert(NULL != hash);
	assert(NULL != action_func);

	for (i = 0; i < hash->size && status == SUCCESS; ++i)
	{
		status = DListForEach(DListBegin(hash->table[i]),DListEnd(hash->table[i]),action_func,param);
	}

	return status;
}

static hash_t *InitHash(size_t size, hash_get_key_func_t get_key, hash_cmp_func_t cmp_func, hash_func_t hash_func,hash_t *hash)
{
	size_t i = 0;

	hash->cmp_func = cmp_func;
	hash->hash_func = hash_func;
	hash->get_key = get_key;
	hash->size = size;

	hash->table = (dlist_t **)malloc(size * sizeof(dlist_t *));
	if (NULL == hash->table)
	{
		free(hash);
		hash = NULL;

		return NULL;
	}

	for (i = 0; i < size; ++i)
	{
		hash->table[i] = DListCreate();
		if (NULL == hash->table[i])
		{
			hash->size = i;
			HashDestroy(hash);

			return NULL;
		}
	}

	return hash;
}

#ifdef DEBUG
	void PrintIntHash(hash_t *hash)
	{
		size_t i = 0;

		for (i = 0; i < hash->size; ++i)
		{
			printf("list %ld: {", i + 1);
			DListForEach(DListBegin(hash->table[i]), DListEnd(hash->table[i]), &PrintInt, &i);
			printf("}\n");	
		}
	}

	static int PrintInt(void *data, void *param)
	{
		(void)param;
		printf("%d, ", *(int *)data);
		return 0;
	}
#endif