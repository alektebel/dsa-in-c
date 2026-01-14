/**
 * SHA-256 Hash Algorithm Implementation
 * 
 * SHA-256 is a cryptographic hash function from the SHA-2 family.
 * Used extensively in:
 * - Digital signatures
 * - SSL/TLS certificates
 * - Blockchain and cryptocurrencies
 * - Data integrity verification
 */

#ifndef SHA256_H
#define SHA256_H

#include <stddef.h>
#include <stdint.h>

#define SHA256_BLOCK_SIZE 64    // 512 bits
#define SHA256_DIGEST_SIZE 32   // 256 bits

// SHA-256 context for incremental hashing
typedef struct {
    uint32_t state[8];          // Hash state (A, B, C, D, E, F, G, H)
    uint8_t buffer[SHA256_BLOCK_SIZE];  // Message block buffer
    uint64_t bitlen;            // Total message length in bits
    uint32_t buflen;            // Current buffer length
} SHA256Context;

/**
 * Initialize SHA-256 context
 * @param ctx Context to initialize
 */
void sha256_init(SHA256Context *ctx);

/**
 * Update hash with new data
 * @param ctx SHA-256 context
 * @param data Input data
 * @param len Length of input data in bytes
 */
void sha256_update(SHA256Context *ctx, const uint8_t *data, size_t len);

/**
 * Finalize hash computation
 * @param ctx SHA-256 context
 * @param hash Output buffer (must be at least 32 bytes)
 */
void sha256_final(SHA256Context *ctx, uint8_t *hash);

/**
 * Compute SHA-256 hash in one call
 * @param data Input data
 * @param len Length of input data
 * @param hash Output buffer (must be at least 32 bytes)
 */
void sha256_hash(const uint8_t *data, size_t len, uint8_t *hash);

/**
 * Convert hash to hexadecimal string
 * @param hash Hash bytes (32 bytes)
 * @param hex_string Output string buffer (must be at least 65 bytes)
 */
void sha256_to_hex(const uint8_t *hash, char *hex_string);

#endif // SHA256_H
