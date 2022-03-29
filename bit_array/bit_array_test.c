#include <stdio.h> /*printf()*/
#include <string.h>

#include "../include/bit_array.h"


int main()
{
	
	
	
	/*set all bits*/
	bits_arr64_t bit_array = 0;
	
	/*to string*/
	char bit_array_print[65] = {0};
	
	int bit_val = 0;
	
	bit_array = BitArraySetAll(bit_array);
	BitArrayToString(bit_array,bit_array_print);
	printf("%s ", bit_array_print);
	printf("\n");
	
	/*reset all*/
	bit_array = BitArrayResetAll(bit_array);
	BitArrayToString(bit_array,bit_array_print);
	printf("%s ", bit_array_print);
	printf("\n");
	
	
	
	/*turn on specific bit*/
	bit_array = BitArraySetOn(bit_array, 1);
	bit_array = BitArraySetOn(bit_array, 2);
	bit_array = BitArraySetOn(bit_array, 3);
	bit_array = BitArraySetOn(bit_array, 4);
	bit_array = BitArraySetOn(bit_array, 5);
	bit_array = BitArraySetOn(bit_array, 6);
	BitArrayToString(bit_array,bit_array_print);
	printf("%s ", bit_array_print);
	printf("\n");
	
	/*turn off specific bit:*/
	bit_array = BitArraySetOn(bit_array, 32);
	bit_array = BitArraySetOff(bit_array, 10);
	bit_array = BitArraySetOff(bit_array, 11);
	bit_array = BitArraySetOff(bit_array, 12);
	bit_array = BitArraySetOff(bit_array, 13);
	bit_array = BitArraySetOff(bit_array, 32);
	BitArrayToString(bit_array,bit_array_print);
	printf("%s ", bit_array_print);
	printf("\n");
	
	
	/*get the specific bit value*/
	bit_val = BitArrayGetVal(bit_array, 0);
	printf("%d\n",bit_val);
	
	
	
	/*count bit on*/
	bit_array = BitArraySetOn(bit_array, 43);
	bit_array = BitArraySetOn(bit_array, 32);
	bit_array = BitArraySetOn(bit_array, 55);
	bit_array = BitArraySetOn(bit_array, 22);
	printf("---------------------------\n");
	BitArrayToString(bit_array,bit_array_print);
	printf("%s ", bit_array_print);
	printf("\n");
	
	printf("number of bits on: %ld\n",BitArrayCountOn(bit_array));
	
	
	/*count number of bits off*/
	 printf("number of bits off: %ld\n",BitArrayCountOff(bit_array));
	 
	printf("---------------------------\n");
	printf("\n");
	
	
	
	printf("------------rotate right---------------\n");
	bit_array = BitArrayResetAll(bit_array);
	bit_array = BitArraySetOn(bit_array, 0);
	bit_array = BitArraySetOn(bit_array, 1);
	bit_array = BitArraySetOn(bit_array, 2);
	BitArrayToString(bit_array,bit_array_print);
	printf("before rotate: %s ", bit_array_print);
	printf("\n");
	
	
	bit_array = BitArrayRotateRight(bit_array,3);
	BitArrayToString(bit_array,bit_array_print);
	printf("after rotate: %s ", bit_array_print);
	printf("\n");
	
	printf("------------flip---------------\n");
	printf("before flipping: \n");
	bit_array = BitArraySetAll(bit_array);
	bit_array = BitArraySetOff(bit_array, 1);
	BitArrayToString(bit_array,bit_array_print);
	printf("%s ", bit_array_print);
	printf("\n");
	printf("after flipping:\n");
	bit_array = BitArrayFlip(bit_array,1);
	BitArrayToString(bit_array,bit_array_print);
	printf("%s ", bit_array_print);
	printf("\n");
	
	
	printf("------------set bit---------------\n");
	printf("before setting: \n");
	bit_array = BitArraySetAll(bit_array);
	BitArrayToString(bit_array,bit_array_print);
	printf("%s ", bit_array_print);
	printf("\n");
	printf("after setting: \n");
	bit_array = BitArraySetBit(bit_array,30,0);
	BitArrayToString(bit_array,bit_array_print);
	printf("%s ", bit_array_print);
	printf("\n");
	
	printf("------------byte mirror---------------\n");
	bit_array = 4294967295;
	BitArrayToString(bit_array,bit_array_print);
	printf("%s ", bit_array_print);
	printf("\n");
	
	
	bit_array = BitArrayMirror(bit_array);
	BitArrayToString(bit_array,bit_array_print);
	printf("%s ", bit_array_print);
	printf("\n");
	
	
	
	
	return 0;
	
}


















