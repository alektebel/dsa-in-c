/**
 * Grover's Search Algorithm (Quantum Algorithm Simulation)
 * 
 * Grover's algorithm provides quadratic speedup for unstructured search.
 * Used in:
 * - Database search
 * - Constraint satisfaction
 * - Cryptanalysis
 * - Optimization problems
 * 
 * Note: This is a classical simulation of quantum behavior.
 * Real implementation requires quantum hardware.
 */

#ifndef GROVER_H
#define GROVER_H

#include <stddef.h>
#include <stdbool.h>
#include <complex.h>

// Quantum state representation (classical simulation)
typedef struct {
    double complex *amplitudes;  // Probability amplitudes
    size_t num_qubits;          // Number of qubits
    size_t state_size;          // 2^num_qubits
} QuantumState;

// Oracle function type (marks target states)
typedef bool (*oracle_func_t)(size_t state, void *data);

// Grover result
typedef struct {
    size_t *solutions;          // Found solutions
    size_t num_solutions;
    size_t iterations_run;
    double success_probability;
} GroverResult;

/**
 * Create quantum state
 * @param num_qubits Number of qubits
 * @return Quantum state or NULL on failure
 */
QuantumState* grover_state_create(size_t num_qubits);

/**
 * Free quantum state
 * @param state State to free
 */
void grover_state_free(QuantumState *state);

/**
 * Initialize state in equal superposition
 * @param state Quantum state
 */
void grover_initialize_superposition(QuantumState *state);

/**
 * Apply oracle operation (marks target states with phase flip)
 * @param state Quantum state
 * @param oracle Oracle function
 * @param user_data User data passed to oracle
 */
void grover_apply_oracle(QuantumState *state, oracle_func_t oracle, void *user_data);

/**
 * Apply diffusion operator (amplifies marked states)
 * @param state Quantum state
 */
void grover_apply_diffusion(QuantumState *state);

/**
 * Run Grover's algorithm
 * @param num_qubits Number of qubits (search space size = 2^num_qubits)
 * @param oracle Oracle function marking target states
 * @param user_data User data passed to oracle
 * @param num_solutions Expected number of solutions (for optimal iterations)
 * @return Result containing found solutions
 */
GroverResult* grover_search(size_t num_qubits, oracle_func_t oracle,
                           void *user_data, size_t num_solutions);

/**
 * Measure quantum state (collapse to classical state)
 * @param state Quantum state
 * @return Measured state index
 */
size_t grover_measure(QuantumState *state);

/**
 * Free Grover result
 * @param result Result to free
 */
void grover_result_free(GroverResult *result);

#endif // GROVER_H
