/**
 * Binary Search Implementation
 * 
 * Binary search is a fundamental algorithm providing O(log n) search time
 * on sorted arrays. Used extensively in:
 * - System libraries (bsearch)
 * - Database indexing
 * - File systems
 * - Network protocols
 */

#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <stdbool.h>
#include <stddef.h>

// Comparison function type
typedef int (*compare_func_t)(const void *a, const void *b);

/**
 * Basic binary search for integers
 * @param array Sorted array of integers
 * @param size Number of elements in array
 * @param target Value to search for
 * @return Index of target if found, -1 otherwise
 */
int binary_search_int(const int *array, size_t size, int target);

/**
 * Generic binary search
 * @param array Sorted array
 * @param size Number of elements
 * @param element_size Size of each element in bytes
 * @param target Element to search for
 * @param compare Comparison function
 * @return Index of target if found, -1 otherwise
 */
int binary_search(const void *array, size_t size, size_t element_size,
                 const void *target, compare_func_t compare);

/**
 * Binary search that returns insertion point if not found
 * @param array Sorted array of integers
 * @param size Number of elements
 * @param target Value to search for
 * @return Index if found, or -(insertion_point + 1) if not found
 */
int binary_search_with_insert_point(const int *array, size_t size, int target);

/**
 * Find first occurrence of target in array with duplicates
 * @param array Sorted array of integers (may have duplicates)
 * @param size Number of elements
 * @param target Value to search for
 * @return Index of first occurrence, or -1 if not found
 */
int binary_search_first(const int *array, size_t size, int target);

/**
 * Find last occurrence of target in array with duplicates
 * @param array Sorted array of integers (may have duplicates)
 * @param size Number of elements
 * @param target Value to search for
 * @return Index of last occurrence, or -1 if not found
 */
int binary_search_last(const int *array, size_t size, int target);

/**
 * Count occurrences of target in sorted array
 * @param array Sorted array of integers
 * @param size Number of elements
 * @param target Value to count
 * @return Number of occurrences
 */
int binary_search_count(const int *array, size_t size, int target);

/**
 * Find lower bound (first element >= target)
 * @param array Sorted array of integers
 * @param size Number of elements
 * @param target Value to compare against
 * @return Index of lower bound, or size if all elements < target
 */
int binary_search_lower_bound(const int *array, size_t size, int target);

/**
 * Find upper bound (first element > target)
 * @param array Sorted array of integers
 * @param size Number of elements
 * @param target Value to compare against
 * @return Index of upper bound, or size if all elements <= target
 */
int binary_search_upper_bound(const int *array, size_t size, int target);

/**
 * Binary search on rotated sorted array
 * @param array Rotated sorted array of integers
 * @param size Number of elements
 * @param target Value to search for
 * @return Index of target if found, -1 otherwise
 */
int binary_search_rotated(const int *array, size_t size, int target);

/**
 * Find peak element in array (element greater than neighbors)
 * @param array Array of integers
 * @param size Number of elements
 * @return Index of a peak element
 */
int binary_search_peak(const int *array, size_t size);

/**
 * Binary search on infinite/unbounded array
 * @param array Sorted array (size unknown)
 * @param target Value to search for
 * @return Index of target if found, -1 otherwise
 */
int binary_search_unbounded(const int *array, int target);

#endif // BINARY_SEARCH_H
