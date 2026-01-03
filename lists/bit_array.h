/**
 * Bit Array Implementation
 * 
 * Bit arrays are space-efficient data structures used for:
 * - Memory allocation bitmaps
 * - Process scheduling (CPU affinity masks)
 * - Network packet filtering
 * - Bloom filters
 * - Set operations
 */

#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Bit array structure
typedef struct BitArray {
    uint32_t *bits;         // Array of 32-bit words
    size_t num_bits;        // Total number of bits
    size_t num_words;       // Number of 32-bit words
} BitArray;

/**
 * Create a new bit array
 * @param num_bits Number of bits in the array
 * @return Pointer to the newly created bit array
 */
BitArray* bit_array_create(size_t num_bits);

/**
 * Set a bit to 1
 * @param array The bit array
 * @param index Index of the bit to set
 * @return true if successful, false if index out of bounds
 */
bool bit_array_set(BitArray *array, size_t index);

/**
 * Clear a bit to 0
 * @param array The bit array
 * @param index Index of the bit to clear
 * @return true if successful, false if index out of bounds
 */
bool bit_array_clear(BitArray *array, size_t index);

/**
 * Toggle a bit (flip its value)
 * @param array The bit array
 * @param index Index of the bit to toggle
 * @return true if successful, false if index out of bounds
 */
bool bit_array_toggle(BitArray *array, size_t index);

/**
 * Get the value of a bit
 * @param array The bit array
 * @param index Index of the bit to get
 * @return true if bit is 1, false if bit is 0 or index out of bounds
 */
bool bit_array_get(BitArray *array, size_t index);

/**
 * Set all bits to 1
 * @param array The bit array
 */
void bit_array_set_all(BitArray *array);

/**
 * Clear all bits to 0
 * @param array The bit array
 */
void bit_array_clear_all(BitArray *array);

/**
 * Count the number of set bits (population count)
 * @param array The bit array
 * @return Number of bits set to 1
 */
size_t bit_array_count(BitArray *array);

/**
 * Find the index of the first set bit
 * @param array The bit array
 * @return Index of first set bit, or -1 if no bits are set
 */
int bit_array_find_first_set(BitArray *array);

/**
 * Find the index of the first clear bit
 * @param array The bit array
 * @return Index of first clear bit, or -1 if all bits are set
 */
int bit_array_find_first_clear(BitArray *array);

/**
 * Perform bitwise AND operation
 * @param dest Destination bit array
 * @param src Source bit array
 * @return true if successful, false if arrays have different sizes
 */
bool bit_array_and(BitArray *dest, BitArray *src);

/**
 * Perform bitwise OR operation
 * @param dest Destination bit array
 * @param src Source bit array
 * @return true if successful, false if arrays have different sizes
 */
bool bit_array_or(BitArray *dest, BitArray *src);

/**
 * Perform bitwise XOR operation
 * @param dest Destination bit array
 * @param src Source bit array
 * @return true if successful, false if arrays have different sizes
 */
bool bit_array_xor(BitArray *dest, BitArray *src);

/**
 * Perform bitwise NOT operation (invert all bits)
 * @param array The bit array
 */
void bit_array_not(BitArray *array);

/**
 * Copy one bit array to another
 * @param dest Destination bit array
 * @param src Source bit array
 * @return true if successful, false if arrays have different sizes
 */
bool bit_array_copy(BitArray *dest, BitArray *src);

/**
 * Compare two bit arrays for equality
 * @param array1 First bit array
 * @param array2 Second bit array
 * @return true if arrays are equal, false otherwise
 */
bool bit_array_equals(BitArray *array1, BitArray *array2);

/**
 * Destroy the bit array and free all allocated memory
 * @param array The bit array to destroy
 */
void bit_array_destroy(BitArray *array);

/**
 * Print the bit array (for debugging)
 * @param array The bit array to print
 */
void bit_array_print(BitArray *array);

#endif // BIT_ARRAY_H
