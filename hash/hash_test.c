/*****************************************************************************
 *** Written by:    Tomer Alayof                                            ***
 *** Date:          01/02/22                                                ***
 *** Reviewer:      Shoshana 		                                        ***
 \*****************************************************************************
 *** Description:                                                           ***
 *** implementation for hash.	                                            ***
 ******************************************************************************
 \*****************************************************************************/

#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE (70000)

#include "../include/hash.h"

#define DICTIONARY_PATH "/usr/share/dict/words"

void TestCreateDestroy(void);
void TestInsert();
void TestLinuxDict();

static size_t HashFunction(const void *key);
static const void *GetKey(const void *data);
static int HashCmp(const void *key1, const void *key2);
static int ActionFunc(void *value, void *param);
static size_t HashDjb2(const void *key);
static int CompareTwoStrings(const void *key1, const void *key2);
int ActionFuncPrint(void *value, void *param);

int main()
{
	TestLinuxDict();
	/*
	TestCreateDestroy();
	
	*/

	/**/

	/*TestInsert();*/
	return 0;
}

void TestLinuxDict()
{
	FILE *ptr;
	int i = 0;
	int is_continue = 1;

	char **str1 = (char **)malloc(200000 * sizeof(char *));
	hash_t *hash = HashCreate(TABLE_SIZE, &GetKey, &CompareTwoStrings, &HashDjb2);

	for (i = 0; i < 200000; ++i)
	{
		str1[i] = (char *)malloc(sizeof(char) * 100);
	}

    ptr = fopen(DICTIONARY_PATH,"r");

	i = 0;

   	while (fgets(str1[i], 1024, ptr) != NULL && i < 200000)
   	{
		HashInsert(hash,str1[i]);
		++i;
   	}
	
    fclose(ptr);

	/*HashForEach(hash,&ActionFuncPrint,NULL);*/
	/*printf(" size: %ld\n",HashSize(hash));*/

	printf("welcome to gaza, to quit please press hamas\n");

	while(is_continue)
	{
		char word[1024] = {0};

		fgets (word,1024,stdin);

		if (HashFind(hash,GetKey(word)) != NULL)
		{
			printf("the word was found ...\n");
		}
		else
		{
			printf("the word was not found\n");
		}

		if( 0 == strcmp(word,"hamas\n"))
		{
			is_continue = 0;
		}
	}

	for (i = 0; i < 200000; i++)
	{
		
		free(str1[i]);
		str1[i] = NULL;
	}

	free(str1);
	str1 = NULL;

	HashDestroy(hash);
}

void TestCreateDestroy(void)
{
    hash_t *hash = HashCreate(8, &GetKey, &HashCmp, &HashFunction);

    assert(1 == HashIsEmpty(hash));
    assert(0 == HashSize(hash));

    HashDestroy(hash);
}

void TestInsert()
{
	hash_t *hash = HashCreate(8, &GetKey, &HashCmp, &HashFunction);

	int x1 = 6;
	int x2 = 8;
	int x3 = 12;
	int x4 = 1;

	int x5 = 2;
	int x6 = 7;
	int x7 = 52;
	int x8 = 7;

	int x9 = 667;
	int x10 = 89;
	int x11 = 3;
	int x12 = 10;

	int x13 = 1000;

	size_t size = 0;

	size = HashSize(hash);

	assert(1 == HashIsEmpty(hash));
	assert(0 == size);

	HashInsert(hash, &x1);
	HashInsert(hash, &x2);
	HashInsert(hash, &x3);
	HashInsert(hash, &x4);
	HashInsert(hash, &x5);
	HashInsert(hash, &x6);
	HashInsert(hash, &x7);
	HashInsert(hash, &x8);
	HashInsert(hash, &x9);
	HashInsert(hash, &x10);
	HashInsert(hash, &x11);
	HashInsert(hash, &x12);

	size = HashSize(hash);

	assert(12 == size);
	assert(0 == HashIsEmpty(hash));

	printf("before remove 6,81,1 \n");
	PrintIntHash(hash);

	HashRemove(hash,GetKey(&x1));
	HashRemove(hash,GetKey(&x10));
	HashRemove(hash,GetKey(&x4));

	printf("after remove 6,81,1 \n");
	PrintIntHash(hash);	

	printf("data that found(667): %d\n",*(int *)HashFind(hash,GetKey(&x9)));

	printf("test for each: \n");

	HashForEach(hash,&ActionFunc,NULL);

	printf("\n");

	assert(NULL == HashFind(hash,&x1));

	HashDestroy(hash);
}

static size_t HashFunction(const void *key)
{
	return (*(int *)key) % 8;
}

static int HashCmp(const void *key1, const void *key2)
{
	return *(int *)key1 - *(int *)key2;
}

static const void *GetKey(const void *data)
{
	return data;
}

static int ActionFunc(void *value, void *param)
{
	(void)param;

	printf("%d\n ",*(int *)value);

	return 0;
}

static size_t HashDjb2(const void *key)
{
    size_t hash = 5381;
    int c = 1;
    unsigned char *str = (unsigned char *)key;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % TABLE_SIZE;
}

static int CompareTwoStrings(const void *key1, const void *key2)
{
	return strcmp((char*)key1,(char*)key2);
}

int ActionFuncPrint(void *value, void *param)
{
	(void)param;
	printf("%s\n",(char *)value);
	return 0;
}