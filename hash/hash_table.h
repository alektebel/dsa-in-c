/**
 * Hash Table Implementation
 * 
 * Hash tables provide O(1) average case lookup, insertion, and deletion.
 * This implementation uses separate chaining for collision resolution.
 * 
 * Used extensively in:
 * - Symbol tables in compilers
 * - Database indexing
 * - Caching systems
 * - Network routing
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Hash table entry (for chaining)
typedef struct HashEntry {
    char *key;                      // Key string
    void *value;                    // Associated value
    uint32_t hash;                  // Cached hash value
    struct HashEntry *next;         // Next entry in chain
} HashEntry;

// Hash table structure
typedef struct HashTable {
    HashEntry **buckets;            // Array of bucket chains
    size_t num_buckets;             // Number of buckets
    size_t num_entries;             // Number of entries
    float load_factor_threshold;    // When to resize
} HashTable;

// Hash function type
typedef uint32_t (*hash_function_t)(const void *data, size_t len);

/**
 * Create a new hash table
 * @param initial_size Initial number of buckets
 * @return Pointer to the newly created hash table
 */
HashTable* hash_table_create(size_t initial_size);

/**
 * Insert a key-value pair into the hash table
 * @param table The hash table
 * @param key The key string
 * @param value The value to associate with the key
 * @return true if insertion was successful, false otherwise
 */
bool hash_table_insert(HashTable *table, const char *key, void *value);

/**
 * Search for a key in the hash table
 * @param table The hash table
 * @param key The key to search for
 * @return The value associated with the key, or NULL if not found
 */
void* hash_table_get(HashTable *table, const char *key);

/**
 * Delete a key from the hash table
 * @param table The hash table
 * @param key The key to delete
 * @return true if deletion was successful, false otherwise
 */
bool hash_table_delete(HashTable *table, const char *key);

/**
 * Update the value for an existing key
 * @param table The hash table
 * @param key The key to update
 * @param value The new value
 * @return true if update was successful, false if key not found
 */
bool hash_table_update(HashTable *table, const char *key, void *value);

/**
 * Check if a key exists in the hash table
 * @param table The hash table
 * @param key The key to check
 * @return true if key exists, false otherwise
 */
bool hash_table_contains(HashTable *table, const char *key);

/**
 * Get all keys in the hash table
 * @param table The hash table
 * @param keys Array to store the keys
 * @param max_keys Maximum number of keys to return
 * @return Number of keys returned
 */
int hash_table_keys(HashTable *table, char **keys, int max_keys);

/**
 * Get the number of entries in the hash table
 * @param table The hash table
 * @return Number of entries
 */
size_t hash_table_size(HashTable *table);

/**
 * Check if the hash table is empty
 * @param table The hash table
 * @return true if table is empty, false otherwise
 */
bool hash_table_is_empty(HashTable *table);

/**
 * Get the load factor of the hash table
 * @param table The hash table
 * @return Load factor (entries / buckets)
 */
float hash_table_load_factor(HashTable *table);

/**
 * Clear all entries from the hash table
 * @param table The hash table
 */
void hash_table_clear(HashTable *table);

/**
 * Resize the hash table to a new number of buckets
 * @param table The hash table
 * @param new_size New number of buckets
 * @return true if resize was successful, false otherwise
 */
bool hash_table_resize(HashTable *table, size_t new_size);

/**
 * Destroy the hash table and free all allocated memory
 * @param table The hash table to destroy
 */
void hash_table_destroy(HashTable *table);

/**
 * Print hash table statistics (for debugging)
 * @param table The hash table
 */
void hash_table_print_stats(HashTable *table);

/**
 * Iterate over all entries in the hash table
 * @param table The hash table
 * @param callback Function to call for each entry
 * @param user_data User data to pass to callback
 */
void hash_table_foreach(HashTable *table, 
                       void (*callback)(const char *key, void *value, void *user_data),
                       void *user_data);

#endif // HASH_TABLE_H
