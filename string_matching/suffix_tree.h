/**
 * Suffix Tree Implementation
 *
 * A suffix tree for a string S of length n is a compressed trie of all n
 * suffixes of S, using O(n) space.  It supports a rich set of string queries:
 *  - Pattern matching:            O(m) per query (m = pattern length)
 *  - Longest repeated substring:  O(n)
 *  - Longest common substring:    O(n + m) for two strings
 *  - All occurrences of pattern:  O(m + occ) where occ = number of occurrences
 *
 * Construction in O(n) time: Ukkonen's online algorithm (1995).
 *
 * Real-Life Use Cases:
 * 1. Full-Text Search in Databases: A suffix tree over a text corpus enables
 *    O(m) pattern search independent of the corpus size, powering substring
 *    search in document databases, code search engines, and log analysis tools
 *    where queries arrive at high rate.
 * 2. Bioinformatics Sequence Analysis: Genome assemblers and alignment tools
 *    build a suffix tree (or the equivalent generalized suffix tree) over
 *    reference sequences to find all positions where a sequencing read appears
 *    in O(read_length) time, enabling rapid read mapping and variant detection.
 * 3. Data Compression (LZ77/LZ78): LZ-family compressors find the longest
 *    previous match for the current position using a sliding-window suffix
 *    structure. A suffix tree allows O(1)-per-character online construction
 *    and O(m) match finding, forming the algorithmic core of gzip and zstd.
 *
 * References:
 *   - 6.897 Advanced Data Structures, MIT, Lecture 10 (Mar 31, 2003)
 *   - Ukkonen, "On-line construction of suffix trees", 1995
 *   - Gusfield, "Algorithms on Strings, Trees and Sequences", 1997
 */

#ifndef SUFFIX_TREE_H
#define SUFFIX_TREE_H

#include <stdbool.h>
#include <stddef.h>

#define ST_ALPHA_SIZE 256   /* ASCII alphabet */
#define ST_INF        (-1)  /* Sentinel for open-ended edge (end of string) */

/**
 * A node in the suffix tree.
 * Edges are represented implicitly by the substring [start, end) of the text.
 */
typedef struct STNode {
    int start;                     /* Start index of the edge label in text */
    int *end;                      /* Pointer to end index (open if ST_INF) */
    int suffix_index;              /* For leaves: index of the suffix; -1 for internal */
    int suffix_link;               /* Suffix link (index into nodes array) */
    int children[ST_ALPHA_SIZE];   /* Child indices (-1 = no child) */
} STNode;

/**
 * Suffix tree structure.
 */
typedef struct SuffixTree {
    char *text;          /* Input string (NUL-terminated copy) */
    int n;               /* Length of text (excluding NUL) */
    STNode *nodes;       /* Node pool */
    int num_nodes;       /* Number of nodes allocated */
    int nodes_cap;       /* Capacity of node pool */
    int root;            /* Index of root node */
    int leaf_end;        /* Current end of all open-ended leaves (Ukkonen) */
} SuffixTree;

/**
 * Build a suffix tree for the given string using Ukkonen's algorithm.
 * @param text  Input string (NUL-terminated)
 * @return Pointer to the new SuffixTree, or NULL on failure
 */
SuffixTree *suffix_tree_build(const char *text);

/**
 * Destroy the suffix tree and free all memory.
 * @param tree  The suffix tree to destroy
 */
void suffix_tree_destroy(SuffixTree *tree);

/**
 * Check whether the pattern is a substring of the text.
 * @param tree     The suffix tree
 * @param pattern  Pattern to search (NUL-terminated)
 * @return true if pattern is found
 */
bool suffix_tree_search(const SuffixTree *tree, const char *pattern);

/**
 * Count the number of occurrences of pattern in the text.
 * @param tree     The suffix tree
 * @param pattern  Pattern to search
 * @return Number of occurrences
 */
int suffix_tree_count(const SuffixTree *tree, const char *pattern);

/**
 * Find all starting positions of pattern in the text.
 * @param tree     The suffix tree
 * @param pattern  Pattern to search
 * @param positions Output array (caller allocates, size >= n)
 * @param count    Output: number of positions found
 * @return true on success
 */
bool suffix_tree_find_all(const SuffixTree *tree, const char *pattern,
                          int *positions, int *count);

/**
 * Find the longest repeated substring in the text.
 * @param tree    The suffix tree
 * @param start   Output: start index of the longest repeated substring
 * @param length  Output: length of the longest repeated substring
 */
void suffix_tree_longest_repeat(const SuffixTree *tree,
                                int *start, int *length);

/**
 * Find the longest palindromic substring using the suffix tree of
 * text + '$' + reverse(text) + '#'.
 * @param tree    A suffix tree built on the combined string
 * @param n       Length of the original string (before '$')
 * @param start   Output: start index in original text
 * @param length  Output: length of the palindrome
 */
void suffix_tree_longest_palindrome(const SuffixTree *tree, int n,
                                    int *start, int *length);

#endif /* SUFFIX_TREE_H */
