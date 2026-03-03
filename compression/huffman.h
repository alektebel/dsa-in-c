/**
 * Huffman Coding Implementation
 *
 * Huffman coding is an optimal prefix-free variable-length code: given a
 * set of symbols with known probabilities, it assigns shorter codes to more
 * frequent symbols, achieving the minimum expected codeword length among all
 * uniquely decodable codes.  Expected length = H(X) to H(X)+1 bits per
 * symbol, where H(X) is the Shannon entropy.
 *
 * Algorithm:
 *   1. Build a min-heap of (frequency, symbol) pairs.
 *   2. Repeatedly extract the two minimum-frequency nodes and combine them
 *      into a new internal node with frequency = sum of children.
 *   3. Repeat until one node (the root) remains.
 *   4. Assign 0/1 to left/right edges; the path from root to a leaf gives
 *      the codeword for that symbol.
 *
 * Real-Life Use Cases:
 * 1. JPEG / PNG / DEFLATE Compression: JPEG uses Huffman coding for entropy
 *    coding of DCT coefficients; PNG and DEFLATE (gzip, zlib) use adaptive
 *    Huffman (or static Huffman with fixed tables) to compress LZ77 output.
 *    Huffman trees in these formats are the final compression step and
 *    account for several bits of savings per symbol.
 * 2. Fax Compression (ITU-T T.4/T.6): Modified Huffman and Modified READ
 *    codes—both Huffman-based—compress bilevel (black-and-white) fax images,
 *    reducing a typical page from several MB to tens of KB.
 * 3. MP3 / AAC Audio Coding: After quantization, audio codecs use Huffman
 *    tables (specified in ISO/IEC 11172-3) to entropy-code the quantized
 *    spectral coefficients, forming the last compression stage before the
 *    bitstream is written to file or transmitted.
 *
 * References:
 *   - 6.897 Advanced Data Structures, MIT, Lecture 13 (Apr 9, 2003)
 *   - Huffman, "A Method for the Construction of Minimum-Redundancy Codes",
 *     Proc. IRE, 1952
 */

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define HUFFMAN_ALPHA_SIZE 256  /* Byte alphabet */
#define HUFFMAN_MAX_CODE_LEN 32 /* Maximum codeword length in bits */

/** A node in the Huffman tree. */
typedef struct HuffNode {
    int symbol;             /* Leaf: byte value 0-255; internal: -1 */
    long long freq;         /* Frequency / weight */
    struct HuffNode *left;
    struct HuffNode *right;
} HuffNode;

/** Huffman code table entry. */
typedef struct HuffCode {
    uint32_t bits;  /* Codeword bits (MSB-first, left-justified) */
    int length;     /* Codeword length in bits (0 = symbol not present) */
} HuffCode;

/** Huffman encoder/decoder context. */
typedef struct HuffTree {
    HuffNode *root;                     /* Root of the Huffman tree */
    HuffCode table[HUFFMAN_ALPHA_SIZE]; /* Encode table */
} HuffTree;

/**
 * Build a Huffman tree from symbol frequency counts.
 * @param freqs  Array of HUFFMAN_ALPHA_SIZE frequency counts
 * @return Pointer to the HuffTree, or NULL on failure
 */
HuffTree *huffman_build(const long long freqs[HUFFMAN_ALPHA_SIZE]);

/**
 * Build a Huffman tree by scanning the input data for frequencies.
 * @param data  Input byte array
 * @param n     Length of input
 * @return Pointer to the HuffTree, or NULL on failure
 */
HuffTree *huffman_build_from_data(const uint8_t *data, size_t n);

/**
 * Destroy the Huffman tree and free all memory.
 * @param tree  The Huffman tree to destroy
 */
void huffman_destroy(HuffTree *tree);

/**
 * Encode data using the Huffman tree.
 * @param tree      The Huffman tree
 * @param input     Input byte array
 * @param in_len    Length of input
 * @param out_len   Output: length of compressed output in BYTES
 * @param num_bits  Output: exact number of valid bits in last byte
 * @return Allocated byte array with compressed data, or NULL on failure
 */
uint8_t *huffman_encode(const HuffTree *tree, const uint8_t *input,
                        size_t in_len, size_t *out_len, int *num_bits);

/**
 * Decode compressed data using the Huffman tree.
 * @param tree      The Huffman tree
 * @param input     Compressed byte array
 * @param in_len    Length of compressed input in bytes
 * @param num_bits  Number of valid bits in the last byte
 * @param out_len   Output: length of decompressed output
 * @return Allocated byte array with original data, or NULL on failure
 */
uint8_t *huffman_decode(const HuffTree *tree, const uint8_t *input,
                        size_t in_len, int num_bits, size_t *out_len);

/**
 * Print the Huffman code table (for debugging).
 * @param tree  The Huffman tree
 */
void huffman_print_table(const HuffTree *tree);

#endif /* HUFFMAN_H */
