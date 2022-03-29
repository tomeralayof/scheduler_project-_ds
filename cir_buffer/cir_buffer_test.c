#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../include/cir_buffer.h"

#define OUTPUT_SIZE (100)
#define BUFFER_SIZE (10)
#define ERR ((ssize_t) -1)


void EphraimTest();
void TestTomer();
void AdrianTest();
void testDor();
void Test1();
void TestWriteLock();
void TestReadAcrossBuffer();


int main()
{


    const size_t cap = (1 << 4);
    const char input[] = "Hello World! ";
    char output[sizeof(input) << 1];

    cbuffer_t *buffer = CBuffCreate(cap);
    assert(NULL != buffer);
    assert(cap == CBuffCapacity(buffer));
    assert(1 == CBuffIsEmpty(buffer));
    assert(cap == CBuffFreeSpace(buffer));

    assert(strlen(input) == (size_t)CBuffWrite(buffer, input, strlen(input)));
    assert(0 == CBuffIsEmpty(buffer));
    assert(cap != CBuffFreeSpace(buffer));
    assert(0 != CBuffFreeSpace(buffer));

    assert(cap != (size_t)CBuffWrite(buffer, input, strlen(input)));
    assert(0 == CBuffIsEmpty(buffer));
    assert(0 == CBuffFreeSpace(buffer));
    assert(-1 == CBuffWrite(buffer, input, strlen(input)));
    
    assert(cap == (size_t)CBuffRead(buffer, output, sizeof(output)));
    assert(1 == CBuffIsEmpty(buffer));
    assert(cap == CBuffFreeSpace(buffer));
    assert(0 == strncmp("Hello World! Hello World! ", output, cap));
    assert(-1 == CBuffRead(buffer, output, sizeof(output)));

    assert((cap >> 2) == (size_t)CBuffWrite(buffer, input, cap >> 2));
    assert((cap >> 2) == (size_t)CBuffRead(buffer, output, cap >> 2));
    assert(sizeof(input) == CBuffWrite(buffer, input, sizeof(input)));
    assert(sizeof(input) == CBuffRead(buffer, output, sizeof(output)));
    assert(0 == strncmp(input, output, sizeof(input)));

    CBuffDestroy(buffer);
    buffer = NULL;

    printf("SUCCESS\n");

	
	
	
	
	/*passed*/
	/*AdrianTest();*/
	
	 /*
	 passed
	 EphraimTest();
	 */

	/*testDor();*/
	
	/*Test1();*/
	
	
	/*TestWriteLock();*/
	
	/*TestReadAcrossBuffer();*/
	
	/*TestReadAcrossBuffer();*/
	
	
	return 0;
}

/*if the condition is not true it breaks the program*/
void TestReadAcrossBuffer()
{
	cbuffer_t *buffer = CBuffCreate(BUFFER_SIZE);
	char *src = "abcdefghijklmnop";
	char output[OUTPUT_SIZE] ={'\0'};
	ssize_t write_idx = 0;
	ssize_t tmp = 0;

	CBuffWrite(buffer, src, 10);
	write_idx = CBuffRead(buffer, output, 6);
	assert(!strncmp(output, src, 6));

	CBuffWrite(buffer, (src + 10), 10);
	assert(ERR != (tmp = CBuffRead(buffer, output + write_idx, 7)));
	write_idx += tmp;
	
	/*abcdefghijklm*/
	printf("output: %s\n",output);

	assert(13 == write_idx);
	assert(!strncmp(output, src, 13));


	CBuffDestroy(buffer);
}
































void testcase1()
{

	size_t capacity = 10;	
	size_t space_free = 0;
	
	ssize_t is_write_success = 0;
	size_t count = 2;
	size_t count_2 = 200;
	char * src = "this is the sentence i want to copy";
	
	int is_empty = 0;
	
	void * src_ptr = src;
	
	
	cbuffer_t *buffer = CBuffCreate(capacity);
	
	
	space_free = CBuffFreeSpace(buffer);
	printf("free space: %ld\n",space_free);
	
	is_empty = CBuffIsEmpty(buffer);
	printf("is empty: %d\n",is_empty);
	
	is_write_success = CBuffWrite(buffer,src_ptr,count);
	printf("%ld\n",is_write_success);
	
	space_free = CBuffFreeSpace(buffer);
	printf("free space: %ld\n",space_free);
	
	/*
	is_write_success = CBuffWrite(buffer,src_ptr,count);
	printf("%ld\n",is_write_success);
	
	is_write_success = CBuffWrite(buffer,src_ptr,count);
	printf("%ld\n",is_write_success);
	
	is_write_success = CBuffWrite(buffer,src_ptr,count);
	printf("%ld\n",is_write_success);
	
	is_write_success = CBuffWrite(buffer,src_ptr,count);
	printf("%ld\n",is_write_success);
	
	is_write_success = CBuffWrite(buffer,src_ptr,count);
	printf("%ld\n",is_write_success);
	*/
	is_empty = CBuffIsEmpty(buffer);
	printf("is empty: %d\n",is_empty);
	
	space_free = CBuffFreeSpace(buffer);
	printf("free space: %ld\n",space_free);
	
	is_write_success = CBuffWrite(buffer,src_ptr,count_2);
	printf("is write success: %ld\n",is_write_success);
	
	
	/*CBuffRead(buffer,src,count_2);*/
		
	CBuffDestroy(buffer);
}



void EphraimTest()
{
    const size_t cap = (1 << 4);
    const char input[] = "Hello World! ";
    char output[sizeof(input) << 1];

    cbuffer_t *buffer = CBuffCreate(cap);
    assert(NULL != buffer);
    assert(cap == CBuffCapacity(buffer));
    assert(CBuffIsEmpty(buffer));
    assert(cap == CBuffFreeSpace(buffer));

    assert(strlen(input) == (size_t)CBuffWrite(buffer, input, strlen(input)));
    assert(!CBuffIsEmpty(buffer));
    
    assert(cap != CBuffFreeSpace(buffer));
    
    assert(0 != CBuffFreeSpace(buffer));

    assert(cap != (size_t)CBuffWrite(buffer, input, strlen(input)));
    assert(!CBuffIsEmpty(buffer));
    assert(0 == CBuffFreeSpace(buffer));
    assert(-1 == CBuffWrite(buffer, input, strlen(input)));
    
    
   
    printf("capacity: %ld\n",cap);
    
    
    assert(cap == (size_t)CBuffRead(buffer, output, sizeof(output)));
    /*condition is true*/
    
    
    
    assert(CBuffIsEmpty(buffer));
    assert(cap == CBuffFreeSpace(buffer));
    assert(!strncmp("Hello World! Hello World! ", output, cap));
    assert(-1 == CBuffRead(buffer, output, sizeof(output)));

    assert(8 == CBuffWrite(buffer, input, 8));
    assert(8 == CBuffRead(buffer, output, 8));
    assert(sizeof(input) == CBuffWrite(buffer, input, sizeof(input)));
    assert(sizeof(input) == CBuffRead(buffer, output, sizeof(output)));
    assert(!strncmp(input, output, sizeof(input)));

    CBuffDestroy(buffer);
    buffer = NULL;

    printf("SUCCESS\n");
}




void AdrianTest()
{
	
	cbuffer_t *buffer = NULL;
	size_t capacity = 50;
	char str_1[] = "hola que tal "; 
	char str_2[] = "todo en orden "; 
	char str_3[] = "me estoy por pasar aaaaaggghhh";

	
	buffer = CBuffCreate(capacity);
	assert(NULL != buffer);
	assert(capacity == CBuffCapacity(buffer));
	assert(CBuffIsEmpty(buffer));
	assert(13 == CBuffWrite(buffer, str_1, 13));
	assert(37 == CBuffFreeSpace(buffer));
	assert(!CBuffIsEmpty(buffer));
	assert(14 == CBuffWrite(buffer, str_2, 14));
	assert(23 == CBuffWrite(buffer, str_3, 30));
	assert(-1 == CBuffWrite(buffer, str_3, 30));
	assert(0 == CBuffFreeSpace(buffer));
	assert(26 == CBuffRead(buffer, str_3, 26));
	assert(26 == CBuffFreeSpace(buffer));
	assert(24 == CBuffRead(buffer, str_3, 26));
	assert(-1 == CBuffRead(buffer, str_3, 24));
	assert(14 == CBuffWrite(buffer, str_2, 14));
	assert(14 == CBuffWrite(buffer, str_2, 14));
	assert(4 == CBuffRead(buffer, str_3, 4));
	assert(14 == CBuffWrite(buffer, str_2, 14));
	assert(12 == CBuffWrite(buffer, str_2, 14));
	CBuffDestroy(buffer);
	buffer = NULL;

}



void testDor()
{

	cbuffer_t *buffer = CBuffCreate(10);
	char dest[] = {1,2,3,4,5,6,7,8,9,0};
	char dest2[] = {1,2,3,4,5,6,7,8,9,0};
	char dest3[] = {1,2,3,4,5,6,7,8,9,0};
	char dest4[] = {1,2,3,4,5,6,7,8,9,0};
	int status = 0;

	printf("the buffer need to be empty : %d \n", CBuffIsEmpty(buffer));
	status = CBuffWrite(buffer, "dor", 3);
	assert(status != -1);
	printf("status exit buffer write : %d \nshould be : 3 \n", status);
	printf("the buffer need to be not empty : %d \n", CBuffIsEmpty(buffer));
	printf("free space need to be 7\nit is: %ld \n", CBuffFreeSpace(buffer));
	printf("the capacity need to be: 10\nit is: %ld \n", CBuffCapacity(buffer));
	status = CBuffRead(buffer, dest, 11);
	printf("the string that copied is : %s \ncopied %d bytes\n", dest, status);
	printf("free space need to be 10\nit is: %ld \n", CBuffFreeSpace(buffer));
	printf("the buffer need to be empty : %d \n", CBuffIsEmpty(buffer));
	printf("the num of bytes is writen needs to be 10\nit is: %ld", CBuffWrite(buffer, "shaileviinfi", 12));
	CBuffRead(buffer, dest2, 10);
	printf("it copied %s \n", dest2);
	printf("free space need to be 10\nit is: %ld \n", CBuffFreeSpace(buffer));
	printf("the num of bytes is writen needs to be 8\nit is: %ld \n", CBuffWrite(buffer, "dorigler", 8));
	printf("free space need to be 2\nit is: %ld \n", CBuffFreeSpace(buffer));
	status = CBuffRead(buffer, dest3, 3);
	printf("the string that copied is : %s \ncopied %d bytes\n", dest3, status);
	printf("the buffer need to be not empty : %d \n", CBuffIsEmpty(buffer));
	printf("free space need to be 5\nit is: %ld \n", CBuffFreeSpace(buffer));
	status = CBuffRead(buffer, dest4, 5);
	printf("the string that copied is : %s\ncopied %d bytes\n",dest4, status);
	printf("free space need to be 10\nit is: %ld \n", CBuffFreeSpace(buffer));
	status = CBuffRead(buffer, dest4, 5);
	printf("copied %d bytes\n", status);


	CBuffDestroy(buffer);
}




void Test1()
{
    const size_t cap = (1 << 4);
    const char input[] = "Hello World! ";
    char output[sizeof(input) << 1];

    cbuffer_t *buffer = CBuffCreate(cap);
    assert(NULL != buffer);
    assert(cap == CBuffCapacity(buffer));
    assert(1 == CBuffIsEmpty(buffer));
    assert(cap == CBuffFreeSpace(buffer));

    assert(strlen(input) == (size_t)CBuffWrite(buffer, input, strlen(input)));
    assert(0 == CBuffIsEmpty(buffer));
    assert(cap != CBuffFreeSpace(buffer));
    assert(0 != CBuffFreeSpace(buffer));

    assert(cap != (size_t)CBuffWrite(buffer, input, strlen(input)));
    assert(0 == CBuffIsEmpty(buffer));
    assert(0 == CBuffFreeSpace(buffer));
    assert(-1 == CBuffWrite(buffer, input, strlen(input)));
    
    assert(cap == (size_t)CBuffRead(buffer, output, sizeof(output)));
    assert(1 == CBuffIsEmpty(buffer));
    assert(cap == CBuffFreeSpace(buffer));
    assert(0 == strncmp("Hello World! Hello World! ", output, cap));
    assert(-1 == CBuffRead(buffer, output, sizeof(output)));

    assert((cap >> 2) == (size_t)CBuffWrite(buffer, input, cap >> 2));
    assert((cap >> 2) == (size_t)CBuffRead(buffer, output, cap >> 2));
    assert(sizeof(input) == CBuffWrite(buffer, input, sizeof(input)));
    assert(sizeof(input) == CBuffRead(buffer, output, sizeof(output)));
    assert(0 == strncmp(input, output, sizeof(input)));

    CBuffDestroy(buffer);
    buffer = NULL;

    printf("SUCCESS\n");
}



void TestWriteAcrossBuffer()
{
	cbuffer_t *buffer = CBuffCreate(BUFFER_SIZE);
	char *src = "abcdefghijklmnop";
	char output[OUTPUT_SIZE] ={'\0'};
	ssize_t write_idx = 0;
	ssize_t tmp = 0;

	CBuffWrite(buffer, src, 6);
	assert(ERR != (write_idx = CBuffRead(buffer, output, 3)));
	assert(3 == write_idx);
	assert(BUFFER_SIZE - 3 == CBuffFreeSpace(buffer));
	assert(!strncmp(output, src, 3));

	assert(ERR != CBuffWrite(buffer, (src + 6), 10));
	assert(ERR != (tmp = CBuffRead(buffer, output + write_idx, 7)));
	write_idx += tmp;

	assert(10 == write_idx);
	assert(!strncmp(output, src, 10));

	CBuffDestroy(buffer);
}



void TestWriteLock()
{
	cbuffer_t *buffer = CBuffCreate(BUFFER_SIZE);
	char *src = "Salmon Labrak Hamburder Sushi Coockies";
	char output[OUTPUT_SIZE] ={'\0'};
	ssize_t write_idx = 0;

	write_idx = CBuffWrite(buffer, src, 20);
	assert(10 == write_idx);
	assert(0 == CBuffFreeSpace(buffer));
	assert(ERR == CBuffWrite(buffer, src, 30));

	write_idx = CBuffRead(buffer, output, 30);
	assert(write_idx = 10);
	assert(CBuffIsEmpty(buffer));
	assert(!strncmp(output, src, 10));
	assert(ERR == CBuffRead(buffer, output, 30));

	CBuffDestroy(buffer);
}








