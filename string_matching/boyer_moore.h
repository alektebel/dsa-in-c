/**
 * Boyer-Moore Pattern Matching Algorithm
 * 
 * Boyer-Moore is often faster than KMP in practice, especially for longer
 * patterns, as it can skip sections of the text. It uses two heuristics:
 * - Bad character rule
 * - Good suffix rule
 * 
 * Used in:
 * - Text editors (GNU grep uses Boyer-Moore variant)
 * - Intrusion detection systems
 * - Anti-virus scanning
 * - Text processing tools
 */

#ifndef BOYER_MOORE_H
#define BOYER_MOORE_H

#include <stdbool.h>
#include <stddef.h>

#define ALPHABET_SIZE 256  // For extended ASCII

/**
 * Boyer-Moore pattern matching - find first occurrence
 * @param text Text to search in
 * @param text_len Length of text
 * @param pattern Pattern to search for
 * @param pattern_len Length of pattern
 * @return Index of first occurrence, or -1 if not found
 */
int boyer_moore_search(const char *text, size_t text_len,
                       const char *pattern, size_t pattern_len);

/**
 * Boyer-Moore pattern matching for null-terminated strings
 * @param text Text to search in
 * @param pattern Pattern to search for
 * @return Index of first occurrence, or -1 if not found
 */
int boyer_moore_search_string(const char *text, const char *pattern);

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
int boyer_moore_search_all(const char *text, size_t text_len,
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
int boyer_moore_count(const char *text, size_t text_len,
                      const char *pattern, size_t pattern_len);

/**
 * Build bad character table for Boyer-Moore
 * @param pattern Pattern string
 * @param pattern_len Length of pattern
 * @param bad_char Array to store bad character shifts
 */
void boyer_moore_build_bad_char(const char *pattern, size_t pattern_len,
                                int *bad_char);

/**
 * Build good suffix table for Boyer-Moore
 * @param pattern Pattern string
 * @param pattern_len Length of pattern
 * @param good_suffix Array to store good suffix shifts
 */
void boyer_moore_build_good_suffix(const char *pattern, size_t pattern_len,
                                   int *good_suffix);

/**
 * Boyer-Moore search with precomputed tables (for multiple searches)
 * @param text Text to search in
 * @param text_len Length of text
 * @param pattern Pattern to search for
 * @param pattern_len Length of pattern
 * @param bad_char Precomputed bad character table
 * @param good_suffix Precomputed good suffix table
 * @return Index of first occurrence, or -1 if not found
 */
int boyer_moore_search_with_tables(const char *text, size_t text_len,
                                   const char *pattern, size_t pattern_len,
                                   const int *bad_char, const int *good_suffix);

/**
 * Simplified Boyer-Moore (bad character rule only)
 * Simpler and often sufficient for many applications
 * @param text Text to search in
 * @param text_len Length of text
 * @param pattern Pattern to search for
 * @param pattern_len Length of pattern
 * @return Index of first occurrence, or -1 if not found
 */
int boyer_moore_simple(const char *text, size_t text_len,
                       const char *pattern, size_t pattern_len);

/**
 * Boyer-Moore-Horspool variant (simplified version)
 * Uses only bad character rule with rightmost occurrence
 * @param text Text to search in
 * @param text_len Length of text
 * @param pattern Pattern to search for
 * @param pattern_len Length of pattern
 * @return Index of first occurrence, or -1 if not found
 */
int boyer_moore_horspool(const char *text, size_t text_len,
                         const char *pattern, size_t pattern_len);

/**
 * Check if text contains pattern
 * @param text Text to search in
 * @param text_len Length of text
 * @param pattern Pattern to search for
 * @param pattern_len Length of pattern
 * @return true if pattern found, false otherwise
 */
bool boyer_moore_contains(const char *text, size_t text_len,
                          const char *pattern, size_t pattern_len);

/**
 * Print bad character table for debugging
 * @param pattern Pattern string
 * @param bad_char Bad character table
 * @param pattern_len Length of pattern
 */
void boyer_moore_print_bad_char(const char *pattern, const int *bad_char,
                                size_t pattern_len);

#endif // BOYER_MOORE_H
