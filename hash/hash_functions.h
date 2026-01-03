/**
 * Hash Functions Implementation
 * 
 * Collection of hash functions commonly used in operating systems and applications:
 * - DJB2 (Daniel J. Bernstein)
 * - FNV-1a (Fowler-Noll-Vo)
 * - MurmurHash
 * - Jenkins hash
 * 
 * Used for hash tables, checksums, and data integrity verification.
 */

#ifndef HASH_FUNCTIONS_H
#define HASH_FUNCTIONS_H

#include <stddef.h>
#include <stdint.h>

/**
 * DJB2 hash function by Daniel J. Bernstein
 * Simple and fast, good distribution for strings
 * @param data Pointer to data to hash
 * @param len Length of data in bytes
 * @return 32-bit hash value
 */
uint32_t hash_djb2(const void *data, size_t len);

/**
 * DJB2 variant specifically for null-terminated strings
 * @param str String to hash
 * @return 32-bit hash value
 */
uint32_t hash_djb2_string(const char *str);

/**
 * FNV-1a hash function (32-bit variant)
 * Good distribution and speed, widely used
 * @param data Pointer to data to hash
 * @param len Length of data in bytes
 * @return 32-bit hash value
 */
uint32_t hash_fnv1a_32(const void *data, size_t len);

/**
 * FNV-1a hash function (64-bit variant)
 * Better distribution for larger hash tables
 * @param data Pointer to data to hash
 * @param len Length of data in bytes
 * @return 64-bit hash value
 */
uint64_t hash_fnv1a_64(const void *data, size_t len);

/**
 * MurmurHash3 (32-bit variant)
 * Excellent distribution and speed, non-cryptographic
 * @param data Pointer to data to hash
 * @param len Length of data in bytes
 * @param seed Seed value for hash function
 * @return 32-bit hash value
 */
uint32_t hash_murmur3_32(const void *data, size_t len, uint32_t seed);

/**
 * Jenkins One-at-a-time hash
 * Simple and effective for small keys
 * @param data Pointer to data to hash
 * @param len Length of data in bytes
 * @return 32-bit hash value
 */
uint32_t hash_jenkins(const void *data, size_t len);

/**
 * CRC32 checksum
 * Used for error detection and hash tables
 * @param data Pointer to data to hash
 * @param len Length of data in bytes
 * @return 32-bit CRC value
 */
uint32_t hash_crc32(const void *data, size_t len);

/**
 * Simple integer hash function
 * Useful for hashing integer keys
 * @param key Integer key to hash
 * @return Hashed value
 */
uint32_t hash_int(uint32_t key);

/**
 * Mix function for combining hash values
 * Useful when hashing composite keys
 * @param h1 First hash value
 * @param h2 Second hash value
 * @return Combined hash value
 */
uint32_t hash_mix(uint32_t h1, uint32_t h2);

/**
 * Avalanche/finalization function
 * Improves hash distribution by mixing bits
 * @param hash Input hash value
 * @return Improved hash value
 */
uint32_t hash_avalanche(uint32_t hash);

#endif // HASH_FUNCTIONS_H
