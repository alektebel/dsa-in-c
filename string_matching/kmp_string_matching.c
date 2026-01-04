/**
 * Knuth-Morris-Pratt String Matching Implementation
 */

#include "kmp_string_matching.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool kmp_build_lps(const char *pattern, size_t pattern_len, int *lps) {
    // TODO: Build LPS (Longest Proper Prefix which is also Suffix) array
    // lps[i] = length of longest proper prefix of pattern[0..i]
    //          which is also a suffix of pattern[0..i]
    // 
    // Algorithm:
    // len = 0
    // lps[0] = 0
    // i = 1
    // while i < pattern_len:
    //   if pattern[i] == pattern[len]:
    //     len++
    //     lps[i] = len
    //     i++
    //   else:
    //     if len != 0:
    //       len = lps[len-1]
    //     else:
    //       lps[i] = 0
    //       i++
    
    if (!pattern || !lps || pattern_len == 0) return false;
    
    lps[0] = 0;
    // TODO: Complete implementation
    
    return true;
}

int kmp_search_with_lps(const char *text, size_t text_len,
                        const char *pattern, size_t pattern_len,
                        const int *lps) {
    // TODO: Implement KMP search with precomputed LPS
    // i = 0 (index for text)
    // j = 0 (index for pattern)
    // while i < text_len:
    //   if pattern[j] == text[i]:
    //     i++, j++
    //   if j == pattern_len:
    //     return i - j (match found)
    //   if i < text_len and pattern[j] != text[i]:
    //     if j != 0:
    //       j = lps[j-1]
    //     else:
    //       i++
    return -1;
}

int kmp_search(const char *text, size_t text_len, 
               const char *pattern, size_t pattern_len) {
    // TODO: Build LPS and search
    if (!text || !pattern || pattern_len == 0 || text_len < pattern_len)
        return -1;
    
    int *lps = (int*)malloc(pattern_len * sizeof(int));
    if (!lps) return -1;
    
    if (!kmp_build_lps(pattern, pattern_len, lps)) {
        free(lps);
        return -1;
    }
    
    int result = kmp_search_with_lps(text, text_len, pattern, pattern_len, lps);
    free(lps);
    return result;
}

int kmp_search_string(const char *text, const char *pattern) {
    if (!text || !pattern) return -1;
    return kmp_search(text, strlen(text), pattern, strlen(pattern));
}

int kmp_search_all(const char *text, size_t text_len,
                   const char *pattern, size_t pattern_len,
                   int *positions, int max_matches) {
    // TODO: Find all occurrences
    // Similar to kmp_search but continue after finding match
    return 0;
}

int kmp_count(const char *text, size_t text_len,
              const char *pattern, size_t pattern_len) {
    // TODO: Count all occurrences
    // Use kmp_search_all or implement similar logic
    return 0;
}

bool kmp_contains(const char *text, size_t text_len,
                  const char *pattern, size_t pattern_len) {
    return kmp_search(text, text_len, pattern, pattern_len) != -1;
}

int kmp_longest_prefix_suffix(const char *pattern, size_t pattern_len) {
    // TODO: Find longest prefix-suffix
    // This is lps[pattern_len - 1]
    if (!pattern || pattern_len == 0) return 0;
    
    int *lps = (int*)malloc(pattern_len * sizeof(int));
    if (!lps) return 0;
    
    kmp_build_lps(pattern, pattern_len, lps);
    int result = lps[pattern_len - 1];
    free(lps);
    
    return result;
}

void kmp_print_lps(const char *pattern, const int *lps, size_t pattern_len) {
    printf("Pattern: %.*s\n", (int)pattern_len, pattern);
    printf("LPS:     ");
    for (size_t i = 0; i < pattern_len; i++) {
        printf("%d ", lps[i]);
    }
    printf("\n");
}
