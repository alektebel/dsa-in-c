/**
 * Burrows-Wheeler Transform (BWT) Implementation
 *
 * The Burrows-Wheeler Transform (Burrows & Wheeler, 1994) is a reversible
 * permutation of a string that groups similar characters together, making
 * the transformed string highly amenable to compression by run-length coding
 * and move-to-front transforms.
 *
 * Algorithm:
 *   Forward: form all cyclic rotations of S+'$', sort them lexicographically,
 *   collect the last characters into the BWT string L; record the index I of
 *   the original string in the sorted order.
 *
 *   Inverse: from (L, I), reconstruct S using the LF-mapping:
 *   LF(i) = rank of L[i] among all L[j] with L[j] == L[i] and j <= i,
 *   offset by the count of characters lexicographically smaller than L[i].
 *
 * Real-Life Use Cases:
 * 1. bzip2 File Compression: bzip2 applies BWT then move-to-front then
 *    Huffman coding to blocks of 900 KB.  BWT is the key step: it creates
 *    runs of identical characters that compress dramatically.  bzip2 achieves
 *    better ratios than gzip on typical text data because of BWT.
 * 2. FM-Index / Compressed Full-Text Search: The FM-index (Ferragina &
 *    Manzini 2000) stores only the BWT of a text and supports pattern matching
 *    via backward search entirely within the compressed representation—no
 *    decompression needed.  Tools like BWA (DNA aligner) use the FM-index
 *    to map billions of sequencing reads against the human genome.
 * 3. DNA Sequence Assembly and Repeat Masking: Genome repeat regions produce
 *    identical character runs in the BWT.  Assembly tools exploit BWT-based
 *    compressed de Bruijn graphs to represent and analyse repetitive regions
 *    of large genomes using orders of magnitude less memory than explicit
 *    de Bruijn graphs.
 *
 * References:
 *   - 6.897 Advanced Data Structures, MIT, Lecture 13 (Apr 9, 2003)
 *   - Burrows & Wheeler, "A Block Sorting Lossless Data Compression
 *     Algorithm", DEC SRC Technical Report 124, 1994
 */

#ifndef BWT_H
#define BWT_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * Result of a forward BWT.
 */
typedef struct BWTResult {
    uint8_t *L;     /* BWT string (length n; caller must free) */
    int index;      /* Position of the original string in the sorted rotations */
    int n;          /* Length of the transformed string */
} BWTResult;

/**
 * Compute the Burrows-Wheeler Transform of data[0..n-1].
 * A sentinel character (0x00) is appended internally.
 *
 * @param data  Input byte array
 * @param n     Length of input
 * @return BWTResult with allocated L; call bwt_free() when done
 */
BWTResult bwt_forward(const uint8_t *data, int n);

/**
 * Free the BWT result.
 * @param r  Result to free
 */
void bwt_free(BWTResult *r);

/**
 * Invert the Burrows-Wheeler Transform.
 * Reconstructs the original data from (L, index).
 *
 * @param L      BWT string (length n)
 * @param n      Length of L
 * @param index  Original index returned by bwt_forward
 * @param out    Output buffer (caller allocates, size >= n)
 * @return true on success
 */
bool bwt_inverse(const uint8_t *L, int n, int index, uint8_t *out);

/**
 * Apply BWT followed by move-to-front transform and run-length encoding.
 * This is the compression pipeline used by bzip2.
 *
 * @param data    Input byte array
 * @param n       Length of input
 * @param out_len Output: length of compressed output
 * @return Allocated compressed buffer, or NULL on failure
 */
uint8_t *bwt_compress(const uint8_t *data, int n, int *out_len);

/**
 * Invert the bwt_compress pipeline (RLE -> inverse MTF -> inverse BWT).
 *
 * @param data    Compressed input
 * @param in_len  Length of compressed input
 * @param out_len Output: length of decompressed output
 * @return Allocated decompressed buffer, or NULL on failure
 */
uint8_t *bwt_decompress(const uint8_t *data, int in_len, int *out_len);

#endif /* BWT_H */
