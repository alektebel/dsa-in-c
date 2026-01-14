/**
 * ECDSA (Elliptic Curve Digital Signature Algorithm) Implementation
 * 
 * ECDSA provides digital signatures using elliptic curve cryptography.
 * Used extensively in:
 * - Bitcoin and cryptocurrencies
 * - SSL/TLS certificates
 * - Secure messaging
 * - Code signing
 */

#ifndef ECDSA_H
#define ECDSA_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// Elliptic curve point
typedef struct {
    uint8_t *x;              // X coordinate (big integer)
    uint8_t *y;              // Y coordinate (big integer)
    size_t coord_size;       // Size of coordinates in bytes
    bool is_infinity;        // Point at infinity flag
} ECPoint;

// ECDSA key pair
typedef struct {
    uint8_t *private_key;    // Private key (random integer)
    ECPoint *public_key;     // Public key (point on curve)
    size_t key_size;         // Key size in bytes
} ECDSAKeyPair;

// ECDSA signature
typedef struct {
    uint8_t *r;              // Signature component r
    uint8_t *s;              // Signature component s
    size_t size;             // Size in bytes
} ECDSASignature;

// Elliptic curve parameters (e.g., secp256k1)
typedef struct {
    uint8_t *p;              // Prime modulus
    uint8_t *a;              // Curve parameter a
    uint8_t *b;              // Curve parameter b
    ECPoint *G;              // Generator point
    uint8_t *n;              // Order of G
    size_t param_size;       // Size of parameters in bytes
} ECCurveParams;

/**
 * Create elliptic curve point
 * @param coord_size Size of coordinates in bytes
 * @return Point or NULL on failure
 */
ECPoint* ec_point_create(size_t coord_size);

/**
 * Free elliptic curve point
 * @param point Point to free
 */
void ec_point_free(ECPoint *point);

/**
 * Generate ECDSA key pair
 * @param curve Elliptic curve parameters
 * @return Key pair or NULL on failure
 */
ECDSAKeyPair* ecdsa_generate_keypair(ECCurveParams *curve);

/**
 * Free ECDSA key pair
 * @param keypair Key pair to free
 */
void ecdsa_keypair_free(ECDSAKeyPair *keypair);

/**
 * Sign a message hash
 * @param message_hash Hash of message (typically SHA-256)
 * @param hash_len Length of hash
 * @param keypair Signer's key pair
 * @param curve Elliptic curve parameters
 * @return Signature or NULL on failure
 */
ECDSASignature* ecdsa_sign(const uint8_t *message_hash, size_t hash_len,
                           ECDSAKeyPair *keypair, ECCurveParams *curve);

/**
 * Verify a signature
 * @param message_hash Hash of message
 * @param hash_len Length of hash
 * @param signature Signature to verify
 * @param public_key Signer's public key
 * @param curve Elliptic curve parameters
 * @return True if signature is valid
 */
bool ecdsa_verify(const uint8_t *message_hash, size_t hash_len,
                  ECDSASignature *signature, ECPoint *public_key,
                  ECCurveParams *curve);

/**
 * Free ECDSA signature
 * @param signature Signature to free
 */
void ecdsa_signature_free(ECDSASignature *signature);

#endif // ECDSA_H
