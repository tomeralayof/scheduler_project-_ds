#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

#include <stdlib.h> /* size_t */

typedef unsigned long bits_arr64_t;

typedef enum bit 
{ 
	OFF = 0, 
	ON 
} bit_t;

/* For all indexes: 0 is LSB and 63 is MSB */
/* All indexes must be between 0 to 63 otherwise its an undefined behavior */


/* DESCRIPTION: 
 * Return all bits of the bit array set to ON
 *
 * PARAMS: 
 * bit_array    variable to be modified
 * 
 * RETURN:
 * modified variable
 */
bits_arr64_t BitArraySetAll(bits_arr64_t bit_array);


/* DESCRIPTION: 
 * turn all bits of the bit array to Off
 *
 * PARAMS: 
 * bit_array    variable to be modified
 * 
 * RETURN:
 * modified variable
 */
bits_arr64_t BitArrayResetAll(bits_arr64_t bit_array);


/* DESCRIPTION: 
 * Converts bit array to string
 * undefined behavior: The string is too small to contain all bits
 *
 * PARAMS: 
 * bit_array    variable to be modified
 * string       pointer to the output string
 *
 * RETURN:
 * Pointer to the bits string
 */
char *BitArrayToString(bits_arr64_t bit_array, char *str);


/* DESCRIPTION: 
 * Set a specific indexed bit to on
 *
 * PARAMS: 
 * bit_array        variable to be modified
 * index            the index of the bit. 
 *
 * RETURN:
 * the variable with the modified bit
 */
bits_arr64_t BitArraySetOn(bits_arr64_t bit_array, unsigned int index);


/* DESCRIPTION: 
 * Set a specific index to off
 * undefined behavior: index is larger than number of bits
 *
 * PARAMS: 
 * bits_array  variable to be modified
 * index       the index of the bit
 *
 * RETURN:
 * the variable with the modified bit
 */
bits_arr64_t BitArraySetOff(bits_arr64_t bit_array, unsigned int index);


/* DESCRIPTION: 
 * Set a specific index to on or off
 *
 * PARAMS: 
 * bits_array       variable to be modified
 * index            the index of the bit
 * value 			target value for the bit
 *
 * RETURN:
 * the variable with the modified bit
 */
bits_arr64_t BitArraySetBit(bits_arr64_t bit_array, unsigned int index, bit_t value);


/* DESCRIPTION: 
 * get the specific indexed bit value
 *
 * PARAMS: 
 * bit_array        variable to be modified
 * index            the index of the bit
 *
 * RETURN:
 * the value of the specific bit
 */
bit_t BitArrayGetVal(bits_arr64_t bit_array, unsigned int index);


/* DESCRIPTION: 
 * flip the value of a specific bit
 *
 * PARAMS: 
 * bit_array        variable to be modified
 * index            the index of the bit
 *
 * RETURN:
 * The flliped variable
 */
bits_arr64_t BitArrayFlip(bits_arr64_t bit_array, unsigned int index);


/* DESCRIPTION: 
 * Mirror the bits in the array
 * the new bit in the i index will be the old value of the 63 - i bit
 *
 * PARAMS: 
 * bit_array    variable to be modified
 *
 * RETURN:
 * mirrored var
 */
bits_arr64_t BitArrayMirror(bits_arr64_t bit_array);


/* DESCRIPTION: 
 * shift right bits of bitarray rotation positions 
 *
 * PARAMS: 
 * bits_array        variable to be modified
 * rotation          number of rotations
 *
 * RETURN:
 * rotated variable
 */
bits_arr64_t BitArrayRotateRight(bits_arr64_t bit_array, unsigned int rotation);


/* DESCRIPTION: 
 * shift left bits of bitarray rotation positions 
 *
 * PARAMS: 
 * bit_array        variable to be modified
 * rotation          number of rotations
 *
 * RETURN:
 * rotated variable
 */
bits_arr64_t BitArrayRotateLeft(bits_arr64_t bit_array, unsigned int rotation);


/* DESCRIPTION: 
 * count how many bits are on
 *
 * PARAMS: 
 * bit_array    variable to be modified
 *
 * RETURN:
 * number of set bits
 */
size_t BitArrayCountOn(bits_arr64_t var);


/* DESCRIPTION: 
 * count how many bits are off
 *
 * PARAMS: 
 * bit_array    variable to be modified
 *
 * RETURN:
 * number of Off bits
 */
size_t BitArrayCountOff(bits_arr64_t var);


#endif /* __BIT_ARRAY_H__ */










