/**
 * Suffix Array Implementation
 *
 * A suffix array SA for a string S of length n is the array of the starting
 * indices of all suffixes of S, sorted in lexicographic order.  Combined with
 * the LCP (Longest Common Prefix) array it enables most suffix tree queries
 * in O(n) space, often with better cache behaviour than suffix trees.
 *
 * This file implements:
 *  - SA-IS (Suffix Array Induced Sorting): O(n) construction
 *  - LCP array construction via Kasai's algorithm: O(n)
 *  - Pattern matching: O(m log n) using binary search on SA
 *  - Pattern matching: O(m + log n) using LCP-accelerated search
 *
 * Real-Life Use Cases:
 * 1. Full-Text Search Indexes (grep, Lucene): Suffix arrays underlie many
 *    compressed full-text indexes (FM-index, CSA).  Grep-like tools use SA
 *    binary search to locate pattern occurrences in large text files in
 *    O(m log n) time without scanning the entire file.
 * 2. Genome Assembly (Overlap-Layout-Consensus): DNA assemblers compute
 *    all pairwise overlaps between sequencing reads.  A generalized suffix
 *    array over all reads lets the assembler find all overlaps in
 *    O(total_length) time instead of O(reads^2), enabling assembly of
 *    human-scale genomes.
 * 3. Plagiarism Detection and Document Similarity: Suffix arrays of
 *    concatenated documents enable efficient detection of shared substrings
 *    (longest common substrings, repeated fragments) between large text
 *    corpora, used in academic integrity systems and code clone detectors.
 *
 * References:
 *   - 6.897 Advanced Data Structures, MIT, Lecture 11 (Apr 2, 2003)
 *   - Kasai et al., "Linear-time longest common prefix computation", 2001
 *   - Nong, Zhang & Chan, "Two Efficient Algorithms for Linear Time Suffix
 *     Array Construction", 2009 (SA-IS)
 */

#ifndef SUFFIX_ARRAY_H
#define SUFFIX_ARRAY_H

#include <stdbool.h>
#include <stddef.h>

/**
 * Suffix array with LCP array support.
 */
typedef struct SuffixArray {
    char *text;      /* Copy of the input string */
    int n;           /* Length of text */
    int *sa;         /* sa[i] = starting index of i-th smallest suffix */
    int *rank;       /* rank[i] = position of suffix i in sorted order */
    int *lcp;        /* lcp[i] = length of LCP between sa[i-1] and sa[i] */
} SuffixArray;

/**
 * Build the suffix array (and LCP array) for text using SA-IS + Kasai.
 * @param text  Input string (NUL-terminated)
 * @return Pointer to the SuffixArray, or NULL on failure
 */
SuffixArray *sa_build(const char *text);

/**
 * Destroy the suffix array and free all memory.
 * @param sa  The suffix array to destroy
 */
void sa_destroy(SuffixArray *sa);

/**
 * Find the first occurrence of pattern using binary search.
 * @param sa       The suffix array
 * @param pattern  Pattern to search (NUL-terminated)
 * @return Starting index in text, or -1 if not found
 */
int sa_search(const SuffixArray *sa, const char *pattern);

/**
 * Count the number of occurrences of pattern in text.
 * @param sa       The suffix array
 * @param pattern  Pattern to search
 * @return Number of occurrences
 */
int sa_count(const SuffixArray *sa, const char *pattern);

/**
 * Find all occurrences of pattern.
 * @param sa        The suffix array
 * @param pattern   Pattern to search
 * @param positions Output array (caller allocates, size >= n)
 * @param count     Output: number of occurrences
 * @return true on success
 */
bool sa_find_all(const SuffixArray *sa, const char *pattern,
                 int *positions, int *count);

/**
 * Find the longest repeated substring using the LCP array.
 * @param sa      The suffix array
 * @param start   Output: starting index of the longest repeated substring
 * @param length  Output: length of the longest repeated substring
 */
void sa_longest_repeat(const SuffixArray *sa, int *start, int *length);

/**
 * Compute the longest common substring of two strings.
 * Builds a generalized suffix array over text1 + '$' + text2 + '#'.
 * @param text1   First string
 * @param text2   Second string
 * @param start1  Output: start in text1
 * @param start2  Output: start in text2
 * @param length  Output: length of the LCS
 */
void sa_longest_common_substring(const char *text1, const char *text2,
                                 int *start1, int *start2, int *length);

#endif /* SUFFIX_ARRAY_H */
