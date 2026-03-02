/**
 * Fault-Tolerant Stack Implementation
 *
 * A fault-tolerant stack operates correctly even in the presence of up to
 * δ memory faults (bit flips, random corruptions) in its storage cells.
 * The model (Finocchi & Italiano, 2004) distinguishes between "safe"
 * memory (a small O(δ) buffer immune to faults, e.g., CPU registers) and
 * "unsafe" memory (the main array, subject to faults).
 *
 * Key idea (Iyer et al. 2002 / Lecture 19):
 *   Maintain a "trusted" top-of-stack pointer in safe memory.
 *   Each stack cell is written with a checksum (or redundant copy) so that
 *   corrupted cells can be detected and skipped.  When popping, scan
 *   backward from the trusted pointer until a valid (uncorrupted) element
 *   is found.
 *
 * Complexity: Push O(1), Pop O(δ) amortized.
 *
 * Real-Life Use Cases:
 * 1. Spacecraft / Embedded Systems with Radiation Hardening: Memory in
 *    satellites and deep-space probes is exposed to cosmic rays that flip
 *    bits (Single Event Upsets).  A fault-tolerant stack for the flight
 *    computer's call stack or task queue lets the system continue operating
 *    after transient errors without halting for error correction.
 * 2. Non-Volatile Memory (NVM) Data Structures: NVM (Intel Optane, MRAM)
 *    may have higher cell-error rates than DRAM.  Fault-tolerant stacks
 *    for persistent undo-logs or write-ahead logs in databases built on NVM
 *    ensure crash-and-fault recovery without the overhead of full ECC codes.
 * 3. Secure Enclaves (TEE / SGX): Intel SGX enclaves have a trusted stack
 *    in protected memory but access potentially hostile host memory.  A
 *    fault-tolerant data structure that validates every read from untrusted
 *    memory prevents a compromised OS from corrupting enclave state via
 *    controlled memory faults.
 *
 * References:
 *   - 6.897 Advanced Data Structures, MIT, Lecture 19 (May 5, 2003)
 *   - Finocchi & Italiano, "Sorting and searching in the presence of memory
 *     faults (without redundancy)", STOC 2004
 */

#ifndef FAULT_TOLERANT_STACK_H
#define FAULT_TOLERANT_STACK_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define FT_MAGIC  0xDEADBEEFu  /* Magic value for cell validation */
#define FT_DELTA  8            /* Default fault tolerance: up to δ faults */

/**
 * A single cell in the fault-tolerant stack.
 * Each cell stores a magic number and a redundant copy for verification.
 */
typedef struct FTCell {
    uint32_t magic;     /* Should equal FT_MAGIC; detects corruption */
    int value;          /* Stored value */
    int value_copy;     /* Redundant copy for single-fault detection */
} FTCell;

/**
 * Fault-tolerant stack.
 */
typedef struct FTStack {
    FTCell *storage;    /* "Unsafe" memory: array of cells */
    int capacity;       /* Total allocated cells */
    int top;            /* "Safe" trusted top-of-stack index (in safe memory) */
    int delta;          /* Fault tolerance parameter */
} FTStack;

/**
 * Create a fault-tolerant stack with the given capacity.
 * @param capacity  Number of elements the stack can hold
 * @param delta     Maximum number of faults to tolerate
 * @return Pointer to the new stack, or NULL on failure
 */
FTStack *ft_stack_create(int capacity, int delta);

/**
 * Destroy the fault-tolerant stack and free all memory.
 * @param stack  The stack to destroy
 */
void ft_stack_destroy(FTStack *stack);

/**
 * Push a value onto the stack.
 * @param stack  The stack
 * @param value  Value to push
 * @return true on success, false if stack is full
 */
bool ft_stack_push(FTStack *stack, int value);

/**
 * Pop the top value from the stack.
 * Scans backward past corrupted cells (up to delta of them).
 * @param stack  The stack
 * @param value  Output: popped value
 * @return true if a valid value was found, false if stack appears empty
 */
bool ft_stack_pop(FTStack *stack, int *value);

/**
 * Peek at the top value without removing it.
 * @param stack  The stack
 * @param value  Output: top value
 * @return true if valid value found, false if stack appears empty
 */
bool ft_stack_peek(const FTStack *stack, int *value);

/**
 * Check whether the stack is empty.
 * @param stack  The stack
 * @return true if empty
 */
bool ft_stack_is_empty(const FTStack *stack);

/**
 * Return the logical size (may differ from top if cells are corrupted).
 * @param stack  The stack
 * @return trusted top-of-stack index
 */
int ft_stack_size(const FTStack *stack);

/**
 * Simulate a memory fault: corrupt the cell at the given position.
 * Used for testing fault-tolerance.
 * @param stack  The stack
 * @param pos    Position to corrupt
 */
void ft_stack_inject_fault(FTStack *stack, int pos);

#endif /* FAULT_TOLERANT_STACK_H */
