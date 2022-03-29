#include <stdio.h>

#include "../include/vector.h"

int main()
{


	size_t element_size = 4;
	size_t num_of_element = 1;
	
	int *get_val = NULL;	
		
	size_t capacity = 0;
	
	size_t occupied_elements = 0;
	
	const int first_elem_to_push = 1;
	const int second_elem_to_push = 2;
	const int third_elem_to_push = 3;
	const int fourth_elem_to_push = 4;
	const int fifth_elem_to_push = 5;
	const int sixth_elem_to_push = 6;
				
				
				
	vector_t * vector = VectorCreate(element_size,num_of_element);
	
	VectorPushBack(vector,&first_elem_to_push);	
	VectorPushBack(vector,&second_elem_to_push);	
	VectorPushBack(vector,&third_elem_to_push);	
	VectorPushBack(vector,&fourth_elem_to_push);	
	VectorPushBack(vector,&fifth_elem_to_push);	
	VectorPushBack(vector,&sixth_elem_to_push);	
	VectorPushBack(vector,&sixth_elem_to_push);	
	
	 get_val = (int *)VectorGetAccessToElement(vector,3);

	printf(" The value in index 5 is: %d\n",*get_val);
	
	
	/*vector capacity before resize*/
	capacity = VectorCapacity(vector);
	printf("current capacity: %ld\n",capacity);
	
	/*vector capacity after resize*/
	
	VectorReserve(vector, 100);
	capacity = VectorCapacity(vector);
	printf("after resize: %ld\n",capacity);
	
	occupied_elements = VectorSize(vector);
	printf("the num of occupied elements is: %ld\n",occupied_elements);
	
	
	/*test for VectorPopBack*/
	/*make capacity of 40 elements*/
	VectorReserve(vector, 40);
	capacity = VectorCapacity(vector);
	printf("capacity is: %ld\n",capacity);
	VectorPushBack(vector,&second_elem_to_push);	
	VectorPushBack(vector,&second_elem_to_push);	
	VectorPushBack(vector,&second_elem_to_push);	


	occupied_elements = VectorSize(vector);
	printf("occupied elements: %ld\n",occupied_elements);
	
	
	VectorPopBack(vector);
	capacity = VectorCapacity(vector);
	printf("new capacity is: %ld\n",capacity);
	
	
	VectorDestroy(vector);
		
	
	return 0;
}












