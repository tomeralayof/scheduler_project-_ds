#include <limits.h> /*ULONG_MAX*/
#include <string.h>
#include <stdio.h>

#include "../include/bit_array.h"

/*REVIEWED BY GAL*/

#define LUT_MASK_LENGTH (sizeof(bits_arr64_t)) * (CHAR_BIT)
#define FOUR_BITS_ON_MASK 15
#define CHAR '0'

static unsigned long lut_table[LUT_MASK_LENGTH] = {
1 ,2 ,4 ,8 ,16 ,32 ,64 ,128 ,256 ,512 ,1024 ,2048 ,4096 ,8192 ,16384 ,32768 ,65536 ,131072 ,262144 ,524288 ,1048576 ,2097152 ,4194304 ,8388608 ,16777216 ,33554432 ,67108864 ,134217728 ,268435456 ,536870912 ,1073741824 ,2147483648 ,4294967296 ,8589934592 ,17179869184 ,34359738368 ,68719476736 ,137438953472 ,274877906944 ,549755813888 ,1099511627776 ,2199023255552 ,4398046511104 ,8796093022208 ,17592186044416 ,35184372088832 ,70368744177664 ,140737488355328 ,281474976710656 ,562949953421312 ,1125899906842624 ,2251799813685248 ,4503599627370496 ,9007199254740992 ,18014398509481984 ,36028797018963968 ,72057594037927936 ,144115188075855872 ,288230376151711744 ,576460752303423488 ,1152921504606846976 ,2305843009213693952 ,4611686018427387904,9223372036854775808ul
};

static int bit_on_lut[] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};
static const bits_arr64_t bit_mirror_lut[] = {0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};

bits_arr64_t BitArraySetAll(bits_arr64_t bit_array)
{

	(void)bit_array;
	return ULONG_MAX;
}

bits_arr64_t BitArrayResetAll(bits_arr64_t bit_array)
{
	(void)bit_array;
	return 0;
}

char *BitArrayToString(bits_arr64_t bit_array, char *str)
{

	long unsigned int i = 0;
	bits_arr64_t temp = 0;
	
	
	for (i = 0 ; i < LUT_MASK_LENGTH  ; ++i)
	{
		
		temp = bit_array & lut_table[i];
		str[i] = !!(temp) + CHAR; 
	}		

	return str;
}

bits_arr64_t BitArraySetOn(bits_arr64_t bit_array, unsigned int index)
{
	return bit_array |= lut_table[index]; 
}


bits_arr64_t BitArraySetOff(bits_arr64_t bit_array, unsigned int index)
{
	return 	bit_array &= ~(lut_table[index]);
}


bit_t BitArrayGetVal(bits_arr64_t bit_array, unsigned int index)
{	

	return (bit_array & lut_table[index]) > 0;
}


bits_arr64_t BitArrayFlip(bits_arr64_t bit_array, unsigned int index)
{

	return bit_array ^= lut_table[index]; 
}

size_t BitArrayCountOn(bits_arr64_t var)
{
	
	unsigned long nibble_1 = var & FOUR_BITS_ON_MASK;			
	unsigned long nibble_2 = (var >> 4) & FOUR_BITS_ON_MASK;
	unsigned long nibble_3 = (var >> 8) & FOUR_BITS_ON_MASK;
	unsigned long nibble_4 = (var >> 12) & FOUR_BITS_ON_MASK;
	unsigned long nibble_5 = (var >> 16) & FOUR_BITS_ON_MASK;
	unsigned long nibble_6 = (var >> 20) & FOUR_BITS_ON_MASK;
	unsigned long nibble_7 = (var >> 24) & FOUR_BITS_ON_MASK;
	unsigned long nibble_8 = (var >> 28) & FOUR_BITS_ON_MASK;
	unsigned long nibble_9 = (var >> 32) & FOUR_BITS_ON_MASK;
	unsigned long nibble_10 = (var >> 36) & FOUR_BITS_ON_MASK;
	unsigned long nibble_11 = (var >> 40) & FOUR_BITS_ON_MASK;
	unsigned long nibble_12 = (var >> 44) & FOUR_BITS_ON_MASK;
	unsigned long nibble_13 = (var >> 48) & FOUR_BITS_ON_MASK;
	unsigned long nibble_14 = (var >> 52) & FOUR_BITS_ON_MASK;
	unsigned long nibble_15 = (var >> 56) & FOUR_BITS_ON_MASK;
	unsigned long nibble_16 = (var >> 60) & FOUR_BITS_ON_MASK;
	
	size_t result = bit_on_lut[nibble_1] + bit_on_lut[nibble_2] + bit_on_lut[nibble_3] + bit_on_lut[nibble_4] + bit_on_lut[nibble_5] + 		   bit_on_lut[nibble_6] + bit_on_lut[nibble_7] + bit_on_lut[nibble_8] + bit_on_lut[nibble_9] + bit_on_lut[nibble_10] + bit_on_lut[nibble_11] + bit_on_lut[nibble_12] + bit_on_lut[nibble_13] + bit_on_lut[nibble_14] + bit_on_lut[nibble_15] + bit_on_lut[nibble_16];
	
	return result; 
	
}

size_t BitArrayCountOff(bits_arr64_t var)
{
	return (LUT_MASK_LENGTH - BitArrayCountOn(var));
}


bits_arr64_t BitArrayRotateRight(bits_arr64_t bit_array, unsigned int rotation) 
{     
return ((bit_array >> rotation) | bit_array << (LUT_MASK_LENGTH - rotation));
} 

bits_arr64_t BitArrayRotateLeft(bits_arr64_t bit_array, unsigned int rotation) 
{
	return(BitArrayRotateRight(bit_array ,LUT_MASK_LENGTH - rotation));
}

bits_arr64_t BitArraySetBit(bits_arr64_t bit_array, unsigned int index, bit_t value)
{

	return value == OFF ? BitArraySetOff(bit_array,index) : BitArraySetOn(bit_array,value);
}


bits_arr64_t BitArrayMirror(bits_arr64_t bit_array)
{

	size_t mirror = 0;
	
	mirror |= bit_mirror_lut[bit_array >> 60 & FOUR_BITS_ON_MASK];
	mirror |= bit_mirror_lut[bit_array >> 56 & FOUR_BITS_ON_MASK] << 4;
	mirror |= bit_mirror_lut[bit_array >> 52 & FOUR_BITS_ON_MASK] << 8;
	mirror |= bit_mirror_lut[bit_array >> 48 & FOUR_BITS_ON_MASK] << 12;
	mirror |= bit_mirror_lut[bit_array >> 44 & FOUR_BITS_ON_MASK] << 16;
	mirror |= bit_mirror_lut[bit_array >> 40 & FOUR_BITS_ON_MASK] << 20;
	mirror |= bit_mirror_lut[bit_array >> 36 & FOUR_BITS_ON_MASK] << 24;
	mirror |= bit_mirror_lut[bit_array >> 32 & FOUR_BITS_ON_MASK] << 28;
	mirror |= bit_mirror_lut[bit_array >> 28 & FOUR_BITS_ON_MASK] << 32;
	mirror |= bit_mirror_lut[bit_array >> 24 & FOUR_BITS_ON_MASK] << 36;
	mirror |= bit_mirror_lut[bit_array >> 20 & FOUR_BITS_ON_MASK] << 40;
	mirror |= bit_mirror_lut[bit_array >> 16 & FOUR_BITS_ON_MASK] << 44;
	mirror |= bit_mirror_lut[bit_array >> 12 & FOUR_BITS_ON_MASK] << 48;
	mirror |= bit_mirror_lut[bit_array >> 8  & FOUR_BITS_ON_MASK] << 52;
	mirror |= bit_mirror_lut[bit_array >> 4  & FOUR_BITS_ON_MASK] << 56;
	mirror |= bit_mirror_lut[bit_array & FOUR_BITS_ON_MASK ] << 60;

	return mirror;
}


