/**
 * Shor's Factoring Algorithm (Quantum Algorithm Simulation)
 * 
 * Shor's algorithm factors integers in polynomial time using quantum computation.
 * Used in:
 * - Breaking RSA encryption
 * - Number theory research
 * - Cryptanalysis
 * 
 * Note: This is a classical simulation of the quantum components.
 * Real implementation requires quantum hardware.
 */

#ifndef SHOR_H
#define SHOR_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

// Shor's algorithm result
typedef struct {
    uint64_t factor1;           // First non-trivial factor
    uint64_t factor2;           // Second non-trivial factor
    bool success;               // Whether factorization succeeded
    size_t attempts;            // Number of attempts made
} ShorResult;

/**
 * Factor an integer using Shor's algorithm
 * @param N Number to factor (must be composite)
 * @return Result containing factors
 */
ShorResult* shor_factor(uint64_t N);

/**
 * Classical part: Find period of function f(x) = a^x mod N
 * @param a Base (coprime to N)
 * @param N Modulus
 * @return Period r such that a^r = 1 (mod N)
 */
uint64_t shor_find_period_classical(uint64_t a, uint64_t N);

/**
 * Quantum part: Find period using quantum Fourier transform
 * (This is a simulation - real version requires quantum computer)
 * @param a Base
 * @param N Modulus
 * @param num_qubits Number of qubits to use
 * @return Estimated period
 */
uint64_t shor_find_period_quantum(uint64_t a, uint64_t N, size_t num_qubits);

/**
 * Compute greatest common divisor using Euclidean algorithm
 * @param a First number
 * @param b Second number
 * @return GCD(a, b)
 */
uint64_t gcd(uint64_t a, uint64_t b);

/**
 * Compute modular exponentiation: (base^exp) mod mod
 * @param base Base
 * @param exp Exponent
 * @param mod Modulus
 * @return (base^exp) mod mod
 */
uint64_t mod_exp(uint64_t base, uint64_t exp, uint64_t mod);

/**
 * Check if number is prime
 * @param n Number to check
 * @return True if prime
 */
bool is_prime(uint64_t n);

/**
 * Check if number is power of another
 * @param n Number to check
 * @param base If n = base^k, stores base here
 * @param exponent If n = base^k, stores k here
 * @return True if n is a perfect power
 */
bool is_power(uint64_t n, uint64_t *base, uint64_t *exponent);

/**
 * Free Shor result
 * @param result Result to free
 */
void shor_result_free(ShorResult *result);

#endif // SHOR_H
