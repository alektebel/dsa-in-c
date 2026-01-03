/**
 * Knuth-Morris-Pratt (KMP) String Matching Algorithm
 * 
 * KMP provides efficient pattern matching in O(n + m) time by avoiding
 * redundant comparisons using a preprocessing step to build a failure function.
 * 
 * Used in:
 * - Text editors (find/replace)
 * - Intrusion detection systems
 * - DNA sequence analysis
 * - Log file analysis
 */

#ifndef KMP_STRING_MATCHING_H
#define KMP_STRING_MATCHING_H

#include <stdbool.h>
#include <stddef.h>

/**
 * KMP pattern matching - find first occurrence
 * @param text Text to search in
 * @param text_len Length of text
 * @param pattern Pattern to search for
 * @param pattern_len Length of pattern
 * @return Index of first occurrence, or -1 if not found
 */
int kmp_search(const char *text, size_t text_len, 
               const char *pattern, size_t pattern_len);

/**
 * KMP pattern matching for null-terminated strings
 * @param text Text to search in
 * @param pattern Pattern to search for
 * @return Index of first occurrence, or -1 if not found
 */
int kmp_search_string(const char *text, const char *pattern);

/**
 * Find all occurrences of pattern in text
 * @param text Text to search in
 * @param text_len Length of text
 * @param pattern Pattern to search for
 * @param pattern_len Length of pattern
 * @param positions Array to store positions of matches
 * @param max_matches Maximum number of matches to return
 * @return Number of matches found
 */
int kmp_search_all(const char *text, size_t text_len,
                   const char *pattern, size_t pattern_len,
                   int *positions, int max_matches);

/**
 * Count occurrences of pattern in text
 * @param text Text to search in
 * @param text_len Length of text
 * @param pattern Pattern to search for
 * @param pattern_len Length of pattern
 * @return Number of occurrences
 */
int kmp_count(const char *text, size_t text_len,
              const char *pattern, size_t pattern_len);

/**
 * Build KMP failure function (LPS array)
 * @param pattern Pattern string
 * @param pattern_len Length of pattern
 * @param lps Array to store longest proper prefix which is also suffix
 * @return true if successful
 */
bool kmp_build_lps(const char *pattern, size_t pattern_len, int *lps);

/**
 * Search for pattern with precomputed LPS array (for multiple searches)
 * @param text Text to search in
 * @param text_len Length of text
 * @param pattern Pattern to search for
 * @param pattern_len Length of pattern
 * @param lps Precomputed LPS array
 * @return Index of first occurrence, or -1 if not found
 */
int kmp_search_with_lps(const char *text, size_t text_len,
                        const char *pattern, size_t pattern_len,
                        const int *lps);

/**
 * Check if text contains pattern
 * @param text Text to search in
 * @param text_len Length of text
 * @param pattern Pattern to search for
 * @param pattern_len Length of pattern
 * @return true if pattern found, false otherwise
 */
bool kmp_contains(const char *text, size_t text_len,
                  const char *pattern, size_t pattern_len);

/**
 * Find longest prefix of pattern that is also suffix
 * Used in computing the failure function
 * @param pattern Pattern string
 * @param pattern_len Length of pattern
 * @return Length of longest prefix-suffix
 */
int kmp_longest_prefix_suffix(const char *pattern, size_t pattern_len);

/**
 * Print LPS array for debugging
 * @param pattern Pattern string
 * @param lps LPS array
 * @param pattern_len Length of pattern
 */
void kmp_print_lps(const char *pattern, const int *lps, size_t pattern_len);

#endif // KMP_STRING_MATCHING_H
