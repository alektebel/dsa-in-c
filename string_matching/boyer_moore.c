/**
 * Boyer-Moore Pattern Matching Implementation
 */

#include "boyer_moore.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void boyer_moore_build_bad_char(const char *pattern, size_t pattern_len,
                                int *bad_char) {
    // TODO: Build bad character table
    // Initialize all positions to -1
    // For each character in pattern, store its rightmost position
    // bad_char[c] = rightmost position of character c in pattern
    
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        bad_char[i] = -1;
    }
    
    // TODO: Fill in actual positions
    for (size_t i = 0; i < pattern_len; i++) {
        bad_char[(unsigned char)pattern[i]] = i;
    }
}

void boyer_moore_build_good_suffix(const char *pattern, size_t pattern_len,
                                   int *good_suffix) {
    // TODO: Build good suffix table
    // This is the more complex part of Boyer-Moore
    // For each position, compute the shift based on matching suffix
    
    // Initialize
    for (size_t i = 0; i < pattern_len; i++) {
        good_suffix[i] = pattern_len;
    }
    
    // TODO: Compute suffix shifts
}

int boyer_moore_search_with_tables(const char *text, size_t text_len,
                                   const char *pattern, size_t pattern_len,
                                   const int *bad_char, const int *good_suffix) {
    // TODO: Implement Boyer-Moore search
    // Start from pattern_len - 1 and compare right to left
    // On mismatch, shift using max of bad character and good suffix rules
    
    // int shift = 0;
    // while (shift <= text_len - pattern_len):
    //   j = pattern_len - 1
    //   while j >= 0 and pattern[j] == text[shift + j]:
    //     j--
    //   if j < 0:
    //     return shift (match found)
    //   else:
    //     shift += max(good_suffix[j], 
    //                  j - bad_char[text[shift + j]])
    
    return -1;
}

int boyer_moore_search(const char *text, size_t text_len,
                       const char *pattern, size_t pattern_len) {
    if (!text || !pattern || pattern_len == 0 || text_len < pattern_len)
        return -1;
    
    int *bad_char = (int*)malloc(ALPHABET_SIZE * sizeof(int));
    int *good_suffix = (int*)malloc(pattern_len * sizeof(int));
    
    if (!bad_char || !good_suffix) {
        free(bad_char);
        free(good_suffix);
        return -1;
    }
    
    boyer_moore_build_bad_char(pattern, pattern_len, bad_char);
    boyer_moore_build_good_suffix(pattern, pattern_len, good_suffix);
    
    int result = boyer_moore_search_with_tables(text, text_len, pattern, 
                                                pattern_len, bad_char, good_suffix);
    
    free(bad_char);
    free(good_suffix);
    return result;
}

int boyer_moore_search_string(const char *text, const char *pattern) {
    if (!text || !pattern) return -1;
    return boyer_moore_search(text, strlen(text), pattern, strlen(pattern));
}

int boyer_moore_simple(const char *text, size_t text_len,
                       const char *pattern, size_t pattern_len) {
    // TODO: Simplified version using only bad character rule
    return -1;
}

int boyer_moore_horspool(const char *text, size_t text_len,
                         const char *pattern, size_t pattern_len) {
    // TODO: Implement Boyer-Moore-Horspool variant
    // Simpler than full Boyer-Moore, often just as fast
    // Use bad character rule with rightmost character
    return -1;
}

int boyer_moore_search_all(const char *text, size_t text_len,
                           const char *pattern, size_t pattern_len,
                           int *positions, int max_matches) {
    // TODO: Find all occurrences
    return 0;
}

int boyer_moore_count(const char *text, size_t text_len,
                      const char *pattern, size_t pattern_len) {
    // TODO: Count occurrences
    return 0;
}

bool boyer_moore_contains(const char *text, size_t text_len,
                          const char *pattern, size_t pattern_len) {
    return boyer_moore_search(text, text_len, pattern, pattern_len) != -1;
}

void boyer_moore_print_bad_char(const char *pattern, const int *bad_char,
                                size_t pattern_len) {
    printf("Bad Character Table for pattern: %.*s\n", (int)pattern_len, pattern);
    printf("Character : Position\n");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (bad_char[i] != -1) {
            printf("'%c' (%3d) : %d\n", i, i, bad_char[i]);
        }
    }
}
