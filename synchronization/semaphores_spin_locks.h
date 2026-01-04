/**
 * Semaphores and Spin Locks Implementation
 * 
 * These are fundamental synchronization primitives used in operating systems
 * and concurrent programming:
 * 
 * Semaphores: Used for resource counting and signaling between threads
 * Spin Locks: Busy-wait locks for short critical sections in kernel space
 * 
 * Used extensively in:
 * - Linux kernel synchronization
 * - Thread pools and task queues
 * - Producer-consumer problems
 * - Reader-writer locks
 * - Barrier synchronization
 */

#ifndef SEMAPHORES_SPIN_LOCKS_H
#define SEMAPHORES_SPIN_LOCKS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// ============================================================================
// Semaphore Implementation
// ============================================================================

typedef struct Semaphore {
    int value;                  // Current semaphore value
    void *wait_queue;          // Queue of waiting threads (platform specific)
    void *mutex;               // Mutex for protecting semaphore state
} Semaphore;

/**
 * Create a new semaphore
 * @param initial_value Initial value of the semaphore
 * @return Pointer to newly created semaphore
 */
Semaphore* semaphore_create(int initial_value);

/**
 * Wait (P operation, down, acquire)
 * Decrements the semaphore value. If value becomes negative, blocks.
 * @param sem The semaphore
 * @return true if successful, false on error
 */
bool semaphore_wait(Semaphore *sem);

/**
 * Try wait (non-blocking wait)
 * Attempts to decrement without blocking
 * @param sem The semaphore
 * @return true if acquired, false if would block
 */
bool semaphore_try_wait(Semaphore *sem);

/**
 * Timed wait
 * Wait with timeout
 * @param sem The semaphore
 * @param timeout_ms Timeout in milliseconds
 * @return true if acquired, false on timeout
 */
bool semaphore_timed_wait(Semaphore *sem, int timeout_ms);

/**
 * Post (V operation, up, release)
 * Increments the semaphore value and wakes up waiting thread if any
 * @param sem The semaphore
 * @return true if successful, false on error
 */
bool semaphore_post(Semaphore *sem);

/**
 * Get current semaphore value
 * @param sem The semaphore
 * @return Current value
 */
int semaphore_get_value(Semaphore *sem);

/**
 * Destroy semaphore
 * @param sem The semaphore to destroy
 */
void semaphore_destroy(Semaphore *sem);

// ============================================================================
// Spin Lock Implementation
// ============================================================================

typedef struct SpinLock {
    volatile int locked;        // Lock state (0 = unlocked, 1 = locked)
    int owner_id;              // ID of owning thread (for debugging)
} SpinLock;

/**
 * Initialize a spin lock
 * @param lock The spin lock to initialize
 */
void spinlock_init(SpinLock *lock);

/**
 * Acquire spin lock
 * Busy-waits until lock is acquired
 * @param lock The spin lock
 */
void spinlock_lock(SpinLock *lock);

/**
 * Try to acquire spin lock
 * Returns immediately whether successful or not
 * @param lock The spin lock
 * @return true if lock acquired, false if already locked
 */
bool spinlock_try_lock(SpinLock *lock);

/**
 * Release spin lock
 * @param lock The spin lock
 */
void spinlock_unlock(SpinLock *lock);

/**
 * Check if spin lock is locked
 * @param lock The spin lock
 * @return true if locked, false if unlocked
 */
bool spinlock_is_locked(SpinLock *lock);

// ============================================================================
// Read-Write Lock (using semaphores)
// ============================================================================

typedef struct RWLock {
    Semaphore *read_sem;        // Semaphore for readers
    Semaphore *write_sem;       // Semaphore for writers
    int readers;                // Current number of readers
    void *mutex;               // Mutex for reader count
} RWLock;

/**
 * Create a read-write lock
 * @return Pointer to newly created RW lock
 */
RWLock* rwlock_create(void);

/**
 * Acquire read lock
 * Multiple readers can hold the lock simultaneously
 * @param lock The RW lock
 * @return true if successful
 */
bool rwlock_read_lock(RWLock *lock);

/**
 * Release read lock
 * @param lock The RW lock
 * @return true if successful
 */
bool rwlock_read_unlock(RWLock *lock);

/**
 * Acquire write lock
 * Exclusive access - no readers or other writers
 * @param lock The RW lock
 * @return true if successful
 */
bool rwlock_write_lock(RWLock *lock);

/**
 * Release write lock
 * @param lock The RW lock
 * @return true if successful
 */
bool rwlock_write_unlock(RWLock *lock);

/**
 * Destroy RW lock
 * @param lock The RW lock to destroy
 */
void rwlock_destroy(RWLock *lock);

// ============================================================================
// Barrier Synchronization (using semaphores)
// ============================================================================

typedef struct Barrier {
    int count;                  // Number of threads required
    int waiting;                // Number of threads currently waiting
    Semaphore *mutex;          // Protects barrier state
    Semaphore *turnstile1;     // First turnstile
    Semaphore *turnstile2;     // Second turnstile
} Barrier;

/**
 * Create a barrier
 * @param count Number of threads that must arrive before releasing
 * @return Pointer to newly created barrier
 */
Barrier* barrier_create(int count);

/**
 * Wait at barrier
 * Thread blocks until all threads have arrived
 * @param barrier The barrier
 * @return true if successful
 */
bool barrier_wait(Barrier *barrier);

/**
 * Destroy barrier
 * @param barrier The barrier to destroy
 */
void barrier_destroy(Barrier *barrier);

#endif // SEMAPHORES_SPIN_LOCKS_H
