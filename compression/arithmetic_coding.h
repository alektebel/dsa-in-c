/**
 * Arithmetic Coding Implementation
 *
 * Arithmetic coding is an entropy coder that represents the entire message
 * as a single number in the interval [0, 1).  Unlike Huffman coding, it
 * can represent fractional bits per symbol, achieving the entropy H(X) bits
 * per symbol exactly (no +1 overhead).
 *
 * Algorithm:
 *   Encoding: maintain a current interval [low, high).  For each symbol,
 *     shrink the interval to the sub-interval corresponding to that symbol's
 *     probability range.  Output bits as they become determined.
 *   Decoding: maintain the current interval and the received bit stream;
 *     identify which symbol's sub-interval the received value falls in.
 *
 * This implementation uses integer arithmetic (scaling by 2^16 or 2^32)
 * for precision, following the "carry-free" method (Witten, Neal & Cleary 1987).
 *
 * Real-Life Use Cases:
 * 1. JPEG 2000 / JBIG2 Compression: JPEG 2000 uses arithmetic coding (MQ
 *    coder) instead of Huffman for its entropy stage, achieving better
 *    compression on images with non-dyadic probability distributions—
 *    important for medical imaging (DICOM) where every bit counts.
 * 2. H.264 / H.265 Video: CABAC (Context-Adaptive Binary Arithmetic Coding)
 *    is the entropy stage of H.264/AVC and H.265/HEVC.  By using per-context
 *    adaptive probability models, CABAC achieves 10–15% better compression
 *    than CAVLC (Huffman-based) used in earlier standards.
 * 3. bzip3 / ZPAQ Compression: File archivers targeting near-optimal
 *    compression use arithmetic coding over context models (PPM, CM/PAQ)
 *    that maintain per-context symbol probability tables, yielding some of
 *    the highest compression ratios available for general data.
 *
 * References:
 *   - 6.897 Advanced Data Structures, MIT, Lecture 13 (Apr 9, 2003)
 *   - Witten, Neal & Cleary, "Arithmetic coding for data compression",
 *     CACM 1987
 */

#ifndef ARITHMETIC_CODING_H
#define ARITHMETIC_CODING_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define AC_ALPHA_SIZE 256   /* Byte alphabet */
#define AC_SCALE      (1u << 16)  /* Fixed-point scaling factor */

/**
 * Symbol probability model (static/adaptive).
 * cumulative[i] = sum of counts for symbols 0..i-1.
 * cumulative[AC_ALPHA_SIZE] = total count.
 */
typedef struct ACModel {
    uint32_t cumulative[AC_ALPHA_SIZE + 1]; /* Cumulative frequency table */
    bool adaptive;  /* If true, update counts as symbols are processed */
} ACModel;

/**
 * Arithmetic encoder state.
 */
typedef struct ACEncoder {
    uint32_t low;          /* Current interval lower bound */
    uint32_t high;         /* Current interval upper bound */
    int pending_bits;      /* Bits pending output (for carry propagation) */
    uint8_t *out;          /* Output buffer (caller manages) */
    size_t out_len;        /* Number of bytes written */
    size_t out_cap;        /* Capacity of output buffer */
} ACEncoder;

/**
 * Arithmetic decoder state.
 */
typedef struct ACDecoder {
    uint32_t low;
    uint32_t high;
    uint32_t value;        /* Current value read from input */
    const uint8_t *in;     /* Input buffer */
    size_t in_len;         /* Length of input buffer */
    size_t in_pos;         /* Byte position in input */
    int bit_pos;           /* Bit position within current byte (0-7) */
} ACDecoder;

/**
 * Build a static probability model from frequency counts.
 * @param freqs  Array of AC_ALPHA_SIZE frequency counts
 * @return Initialized model
 */
ACModel ac_model_build(const uint32_t freqs[AC_ALPHA_SIZE]);

/**
 * Build a uniform (flat) model for all AC_ALPHA_SIZE symbols.
 * @return Uniform model
 */
ACModel ac_model_uniform(void);

/**
 * Update an adaptive model after encoding/decoding symbol s.
 * @param model  The model to update
 * @param s      Symbol (0-255)
 */
void ac_model_update(ACModel *model, int s);

/**
 * Initialize an arithmetic encoder.
 * @param enc      Encoder to initialize
 * @param out      Output byte buffer (caller allocates)
 * @param out_cap  Capacity of out buffer
 */
void ac_encoder_init(ACEncoder *enc, uint8_t *out, size_t out_cap);

/**
 * Encode one symbol.
 * @param enc    Encoder state
 * @param model  Probability model
 * @param s      Symbol (0-255)
 * @return true on success
 */
bool ac_encode_symbol(ACEncoder *enc, const ACModel *model, int s);

/**
 * Finalize encoding: flush remaining bits.
 * @param enc     Encoder state
 * @param out_len Output: total bytes written
 */
void ac_encoder_finish(ACEncoder *enc, size_t *out_len);

/**
 * Initialize an arithmetic decoder.
 * @param dec    Decoder to initialize
 * @param in     Compressed input buffer
 * @param in_len Length of compressed input
 */
void ac_decoder_init(ACDecoder *dec, const uint8_t *in, size_t in_len);

/**
 * Decode one symbol.
 * @param dec    Decoder state
 * @param model  Probability model (same as used during encoding)
 * @return Decoded symbol (0-255), or -1 on error
 */
int ac_decode_symbol(ACDecoder *dec, const ACModel *model);

/**
 * Encode an entire byte array.
 * @param input    Input bytes
 * @param in_len   Length of input
 * @param model    Probability model
 * @param out_len  Output: length of compressed output
 * @return Allocated compressed buffer, or NULL on failure
 */
uint8_t *ac_compress(const uint8_t *input, size_t in_len,
                     const ACModel *model, size_t *out_len);

/**
 * Decode an entire compressed buffer.
 * @param input    Compressed input
 * @param in_len   Length of compressed input
 * @param model    Probability model
 * @param sym_cnt  Number of symbols to decode
 * @param out_len  Output: length of decompressed output
 * @return Allocated decompressed buffer, or NULL on failure
 */
uint8_t *ac_decompress(const uint8_t *input, size_t in_len,
                       const ACModel *model, size_t sym_cnt, size_t *out_len);

#endif /* ARITHMETIC_CODING_H */
