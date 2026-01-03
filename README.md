# DSA-in-C
Data Structures and Algorithms Implemented in C

A comprehensive collection of data structures and algorithms commonly used in operating systems, system programming, and high-performance applications.

## Overview

This repository provides clean, well-documented templates for implementing fundamental data structures and algorithms in C. Each implementation includes detailed comments explaining the concepts, use cases, and implementation approach.

## Project Structure

```
DSA-in-C/
├── trees/                    # Tree data structures
│   ├── bplus_tree.h/.c      # B+ Trees for databases and file systems
│   ├── interval_tree.h/.c   # Interval trees for scheduling and geometry
│   ├── red_black_tree.h/.c  # Red-Black trees for balanced search
│   └── radix_tree.h/.c      # Radix trees for IP routing and paths
├── lists/                    # List data structures
│   ├── priority_sorted_list.h/.c  # Priority sorted lists for scheduling
│   └── bit_array.h/.c       # Bit arrays for efficient set operations
├── heaps/                    # Heap data structures
│   └── priority_heap.h/.c   # Priority heaps for task scheduling
├── hash/                     # Hash-based structures
│   ├── hash_functions.h/.c  # Various hash functions (DJB2, FNV, MurmurHash)
│   └── hash_table.h/.c      # Hash tables with separate chaining
├── search_algorithms/        # Search and traversal algorithms
│   ├── binary_search.h/.c   # Binary search variants
│   ├── depth_first_search.h/.c   # DFS for graph traversal
│   ├── breadth_first_search.h/.c # BFS for shortest paths
│   └── merge_sort_list.h/.c # Merge sort for linked lists
├── string_matching/          # String matching algorithms
│   ├── kmp_string_matching.h/.c  # Knuth-Morris-Pratt algorithm
│   └── boyer_moore.h/.c     # Boyer-Moore pattern matching
└── synchronization/          # Synchronization primitives
    └── semaphores_spin_locks.h/.c  # Semaphores and spin locks
```

## Data Structures and Algorithms Included

### Tree Structures
- **B+ Trees**: Self-balancing trees used in databases and file systems for efficient range queries
- **Interval Trees**: Specialized trees for storing intervals and querying overlaps
- **Red-Black Trees**: Self-balancing BSTs used in Linux kernel for scheduling and memory management
- **Radix Trees**: Space-optimized prefix trees for IP routing and file paths

### Lists and Arrays
- **Priority Sorted Lists**: Sorted lists for mutex wait queues and driver queues
- **Bit Arrays**: Space-efficient arrays for set operations and bitmaps

### Heaps
- **Priority Heap**: Binary heap for O(log n) priority queue operations

### Hash Structures
- **Hash Functions**: Multiple hash algorithms (DJB2, FNV-1a, MurmurHash, Jenkins, CRC32)
- **Hash Tables**: Separate chaining hash tables with dynamic resizing

### Search and Sort
- **Binary Search**: Multiple variants including rotated arrays and unbounded search
- **Depth First Search**: Graph traversal with cycle detection and topological sort
- **Breadth First Search**: Shortest path in unweighted graphs and bipartite checking
- **Merge Sort on Lists**: Efficient in-place sorting for linked lists

### String Matching
- **Knuth-Morris-Pratt**: Linear-time pattern matching with failure function
- **Boyer-Moore**: Efficient pattern matching with bad character and good suffix rules

### Synchronization
- **Semaphores**: Counting semaphores for resource management
- **Spin Locks**: Busy-wait locks for short critical sections
- **Read-Write Locks**: Multiple readers or single writer
- **Barriers**: Synchronization point for multiple threads

## Building the Library

### Prerequisites
- GCC compiler (or compatible C compiler)
- Make utility

### Build Instructions

```bash
# Build the static library
make

# The library will be created at: lib/libdsa.a
# Object files will be in: build/

# Clean build artifacts
make clean

# Show build information
make info

# Show help
make help
```

## Usage

Each data structure and algorithm has a header file with function declarations and detailed documentation. Include the appropriate header in your C project:

```c
#include "trees/red_black_tree.h"
#include "hash/hash_table.h"
#include "search_algorithms/binary_search.h"

// Create and use data structures
RBTree *tree = rb_tree_create();
HashTable *table = hash_table_create(16);
int result = binary_search_int(array, size, target);
```

To link against the library:

```bash
gcc -o myapp myapp.c -I. -L./lib -ldsa
```

## Implementation Status

All files are currently **template implementations** with:
- ✅ Complete header files with function declarations
- ✅ Comprehensive documentation for each function
- ✅ Skeleton implementations with TODO comments
- ⏳ Full implementations (to be completed)

The templates provide a clear roadmap for implementation with detailed comments explaining the algorithms and expected behavior.

## Use Cases

These data structures and algorithms are used in:
- **Operating Systems**: Process scheduling, memory management, file systems
- **Databases**: Indexing, query optimization, transaction management
- **Networking**: Routing tables, packet filtering, connection management
- **Compilers**: Symbol tables, syntax trees, optimization
- **System Programming**: Resource management, concurrent access control

## Contributing

Contributions are welcome! To implement a data structure or algorithm:

1. Follow the existing code style and documentation patterns
2. Implement the functions marked with TODO comments
3. Add example usage if appropriate
4. Ensure code compiles without warnings
5. Test thoroughly before submitting

## License

This project is open source and available for educational and commercial use.

## References

The implementations are based on well-known algorithms from:
- "Introduction to Algorithms" by Cormen, Leiserson, Rivest, and Stein
- Linux Kernel source code
- Various computer science textbooks and papers

## Contact

For questions, issues, or contributions, please use the GitHub issue tracker.
