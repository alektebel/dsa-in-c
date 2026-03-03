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
│   ├── radix_tree.h/.c      # Radix trees for IP routing and paths
│   ├── van_emde_boas.h/.c   # van Emde Boas trees (O(log log U) successor)
│   ├── y_fast_trie.h/.c     # y-fast tries (O(log log U), O(n) space)
│   ├── fusion_tree.h/.c     # Fusion trees (O(log_w n) search)
│   ├── splay_tree.h/.c      # Splay trees (self-adjusting, working-set)
│   ├── trie.h/.c            # Character trie and binary trie
│   ├── lca.h/.c             # LCA and Range Minimum Query (RMQ)
│   └── succinct.h/.c        # Succinct rank/select and balanced-paren trees
├── lists/                    # List data structures
│   ├── priority_sorted_list.h/.c  # Priority sorted lists for scheduling
│   ├── bit_array.h/.c       # Bit arrays for efficient set operations
│   ├── move_to_front.h/.c   # Move-to-front list and MTF transform
│   └── ordered_file.h/.c    # Ordered-file maintenance (packed-memory array)
├── heaps/                    # Heap data structures
│   └── priority_heap.h/.c   # Priority heaps for task scheduling
├── hash/                     # Hash-based structures
│   ├── hash_functions.h/.c  # Various hash functions (DJB2, FNV, MurmurHash)
│   └── hash_table.h/.c      # Hash tables with separate chaining
├── search_algorithms/        # Search and traversal algorithms
│   ├── binary_search.h/.c   # Binary search variants
│   ├── depth_first_search.h/.c   # DFS for graph traversal
│   ├── breadth_first_search.h/.c # BFS for shortest paths
│   ├── merge_sort_list.h/.c # Merge sort for linked lists
│   ├── dijkstra.h/.c        # Dijkstra's shortest path algorithm
│   └── astar.h/.c           # A* pathfinding algorithm
├── string_matching/          # String matching algorithms
│   ├── kmp_string_matching.h/.c  # Knuth-Morris-Pratt algorithm
│   ├── boyer_moore.h/.c     # Boyer-Moore pattern matching
│   ├── suffix_tree.h/.c     # Suffix trees (Ukkonen's O(n) construction)
│   └── suffix_array.h/.c    # Suffix arrays with LCP (SA-IS + Kasai)
├── compression/              # Compression algorithms
│   ├── huffman.h/.c         # Huffman coding (optimal prefix-free codes)
│   ├── arithmetic_coding.h/.c   # Arithmetic coding (near-entropy compression)
│   └── bwt.h/.c             # Burrows-Wheeler Transform + inverse
├── cache_oblivious/          # Cache-oblivious data structures
│   ├── cache_oblivious_list.h/.c # Cache-oblivious linked list
│   ├── funnel_sort.h/.c     # Funnelsort (cache-oblivious O(n log n) sort)
│   └── funnel_heap.h/.c     # Funnelheap (cache-oblivious priority queue)
├── fault_tolerant/           # Fault-tolerant data structures
│   ├── fault_tolerant_stack.h/.c # Stack resilient to δ memory faults
│   └── fault_tolerant_list.h/.c  # Linked list resilient to δ memory faults
├── synchronization/          # Synchronization primitives
│   └── semaphores_spin_locks.h/.c  # Semaphores and spin locks
├── optimization/             # Optimization algorithms
│   ├── genetic_algorithm.h/.c     # Genetic algorithm
│   ├── ant_colony.h/.c           # Ant colony optimization
│   ├── simulated_annealing.h/.c  # Simulated annealing
│   ├── whale_optimization.h/.c   # Whale optimization algorithm
│   ├── gradient_descent.h/.c     # Gradient descent
│   ├── conjugate_gradient.h/.c   # Conjugate gradient method
│   ├── newton_method.h/.c        # Newton's method with Hessian
│   ├── linear_programming.h/.c   # Linear programming (Simplex)
│   └── integer_programming.h/.c  # Integer programming (Branch and Bound)
├── ml/                       # Machine learning algorithms
│   ├── linear_regression.h/.c    # Linear regression
│   ├── logistic_regression.h/.c  # Logistic regression
│   ├── decision_tree.h/.c        # Decision trees (CART)
│   └── svm.h/.c                  # Support vector machines
├── crypto/                   # Cryptographic algorithms
│   ├── sha256.h/.c          # SHA-256 hash function
│   └── ecdsa.h/.c           # ECDSA digital signatures
└── quantum/                  # Quantum algorithms (classical simulations)
    ├── grover.h/.c          # Grover's search algorithm
    └── shor.h/.c            # Shor's factoring algorithm
```

## Data Structures and Algorithms Included

### Tree Structures
- **B+ Trees**: Self-balancing trees used in databases and file systems for efficient range queries
- **Interval Trees**: Specialized trees for storing intervals and querying overlaps
- **Red-Black Trees**: Self-balancing BSTs used in Linux kernel for scheduling and memory management
- **Radix Trees**: Space-optimized prefix trees for IP routing and file paths
- **van Emde Boas Trees** *(Lecture 1–3)*: O(log log U) successor/predecessor for integer universes. Use cases: IP routing tables, OS process scheduling, event calendar systems
- **y-fast Tries** *(Lecture 2)*: O(log log U) operations with O(n) space via x-fast hash layer + local BSTs. Use cases: memory-constrained routers, database integer indexes, sensor timestamp stores
- **Fusion Trees** *(Lecture 4)*: B-tree with O(1) node search via word-level parallelism; O(log_w n) per query. Use cases: integer sorting pipelines, compiler symbol tables, packet classification
- **Splay Trees** *(Lecture 7)*: Self-adjusting BST with working-set property; amortized O(log n). Use cases: cache-friendly symbol tables, link-cut trees for network flow, rope data structures
- **Tries (character and binary)** *(Lectures 10, 12)*: Digital search trees branching per character/bit. Use cases: auto-complete/spell check, IP longest-prefix matching, DNA sequence indexing
- **LCA and Range Minimum Query** *(Lectures 10–11)*: O(n) preprocessing, O(1) LCA queries via Euler tour + sparse table. Use cases: suffix tree queries, XML/JSON document processing, Git merge-base computation
- **Succinct Data Structures** *(Lecture 12)*: Bit-vector rank/select in O(n/log n) extra bits; succinct ordered-rooted trees via balanced parentheses. Use cases: compressed inverted indexes, wavelet trees for genome browsers, FM-index for compressed full-text search

### Lists and Arrays
- **Priority Sorted Lists**: Sorted lists for mutex wait queues and driver queues
- **Bit Arrays**: Space-efficient arrays for set operations and bitmaps
- **Move-to-Front List** *(Lectures 5–6)*: Self-organizing list with competitive ratio 2; also the MTF byte transform for compression preprocessing. Use cases: CPU cache/LRU replacement, adaptive Huffman/bzip2 compression, recently-used menus
- **Ordered-File Maintenance** *(Lecture 14)*: Packed-memory array maintaining n elements in O(1) order queries; O(log² n) amortized insert. Use cases: cache-oblivious B-tree leaf layer, persistent sorted arrays, list labeling for order-maintenance

### Heaps
- **Priority Heap**: Binary heap for O(log n) priority queue operations
- **Funnelheap** *(Lecture 17)*: Cache-oblivious priority queue with optimal O(log N / B) amortized cache misses per operation. Use cases: external-memory Dijkstra, discrete-event simulation, k-way external merge sort

### Hash Structures
- **Hash Functions**: Multiple hash algorithms (DJB2, FNV-1a, MurmurHash, Jenkins, CRC32)
- **Hash Tables**: Separate chaining hash tables with dynamic resizing

### Search and Sort
- **Binary Search**: Multiple variants including rotated arrays and unbounded search
- **Depth First Search**: Graph traversal with cycle detection and topological sort
- **Breadth First Search**: Shortest path in unweighted graphs and bipartite checking
- **Merge Sort on Lists**: Efficient in-place sorting for linked lists
- **Dijkstra's Algorithm**: Shortest path algorithm for weighted graphs
- **A* Search**: Informed search algorithm with heuristics for optimal pathfinding
- **Funnelsort** *(Lecture 17)*: Cache-oblivious O(n log n) sort; optimal cache misses at all memory levels. Use cases: external sort in databases, cache-efficient parallel sorting, scientific simulation data pipelines

### String Matching
- **Knuth-Morris-Pratt**: Linear-time pattern matching with failure function
- **Boyer-Moore**: Efficient pattern matching with bad character and good suffix rules
- **Suffix Trees** *(Lecture 10)*: Compressed trie of all suffixes; O(n) construction (Ukkonen's algorithm). Use cases: full-text search, bioinformatics read mapping, LZ77/78 compression
- **Suffix Arrays** *(Lecture 11)*: Sorted suffix index with LCP array; O(n) via SA-IS + Kasai. Use cases: grep/Lucene full-text search, DNA genome assembly, plagiarism detection

### Compression *(Lecture 13)*
- **Huffman Coding**: Optimal prefix-free variable-length code; minimum expected codeword length. Use cases: JPEG/PNG/DEFLATE, fax compression (ITU-T T.4/T.6), MP3/AAC audio
- **Arithmetic Coding**: Near-entropy coder representing a message as a single interval. Use cases: JPEG 2000 / JBIG2 (MQ coder), H.264/H.265 CABAC, bzip3/ZPAQ high-compression archives
- **Burrows-Wheeler Transform (BWT)**: Reversible permutation grouping similar characters for compression. Use cases: bzip2 file compression, FM-index/BWA DNA alignment, genome assembly repeat masking

### Cache-Oblivious Structures *(Lectures 14–18)*
- **Cache-Oblivious Linked List** *(Lecture 15)*: Nodes embedded in a packed-memory array for O(N/B) sequential scan. Use cases: in-memory DB table scans, cache-oblivious B-tree leaf layer, streaming graph processing
- **Funnelsort** *(Lecture 17)*: see Search and Sort above
- **Funnelheap** *(Lecture 17)*: see Heaps above

### Fault-Tolerant Data Structures *(Lecture 19)*
- **Fault-Tolerant Stack**: Stack with magic/checksum cells; correct under up to δ memory faults. Use cases: spacecraft/embedded systems with radiation hardening, NVM persistent undo-logs, Intel SGX secure enclave stacks
- **Fault-Tolerant Linked List**: Linked list with per-node checksums and redundant next pointers. Use cases: fault-tolerant file system metadata, safety-critical RTOS task queues, NVM write-ahead log recovery

### Synchronization
- **Semaphores**: Counting semaphores for resource management
- **Spin Locks**: Busy-wait locks for short critical sections
- **Read-Write Locks**: Multiple readers or single writer
- **Barriers**: Synchronization point for multiple threads

### Optimization Algorithms
- **Genetic Algorithm**: Evolutionary optimization inspired by natural selection
- **Ant Colony Optimization**: Swarm intelligence based on ant foraging behavior
- **Simulated Annealing**: Probabilistic optimization inspired by metallurgy
- **Whale Optimization**: Meta-heuristic based on humpback whale hunting
- **Gradient Descent**: First-order optimization with momentum support
- **Conjugate Gradient**: Efficient method for quadratic optimization and linear systems
- **Newton's Method**: Second-order optimization using Hessian matrix
- **Linear Programming**: Simplex and dual simplex methods for LP problems
- **Integer Programming**: Branch and bound for integer constrained optimization

### Machine Learning
- **Linear Regression**: Linear models for continuous target prediction
- **Logistic Regression**: Binary classification with sigmoid activation
- **Decision Trees**: Hierarchical models using CART algorithm
- **Support Vector Machines**: Maximum margin classification with kernel support

### Cryptography
- **SHA-256**: Secure Hash Algorithm from SHA-2 family
- **ECDSA**: Elliptic Curve Digital Signature Algorithm for authentication

### Quantum Algorithms (Classical Simulations)
- **Grover's Algorithm**: Quantum search with quadratic speedup
- **Shor's Algorithm**: Quantum factoring algorithm for breaking RSA

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

# Build and run the example program
make example
./example

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
#include "trees/van_emde_boas.h"
#include "trees/splay_tree.h"
#include "trees/trie.h"
#include "trees/lca.h"
#include "trees/succinct.h"
#include "hash/hash_table.h"
#include "search_algorithms/binary_search.h"
#include "string_matching/suffix_tree.h"
#include "string_matching/suffix_array.h"
#include "compression/huffman.h"
#include "compression/bwt.h"
#include "cache_oblivious/funnel_sort.h"
#include "cache_oblivious/funnel_heap.h"
#include "fault_tolerant/fault_tolerant_stack.h"

// Create and use data structures
RBTree *tree = rb_tree_create();
HashTable *table = hash_table_create(16);
int result = binary_search_int(array, size, target);
```

To link against the library:

```bash
gcc -o myapp myapp.c -I. -L./lib -ldsa
```

### Example Program

An example program (`example.c`) is included to demonstrate how to use the library:

```bash
make example
./example
```

This will show basic usage of various data structures and algorithms.

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
- **Machine Learning**: Model training, optimization, prediction
- **Cryptography**: Secure communications, digital signatures, data integrity
- **Scientific Computing**: Numerical optimization, simulation, quantum computing research

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
- MIT 6.897 Advanced Data Structures (Spring 2003) lecture notes:
  - Lecture 1–3: van Emde Boas trees, y-fast tries, RAMBO model
  - Lecture 4: Fusion trees (Fredman & Willard 1993)
  - Lectures 5–6: Move-to-front, self-organizing lists (Sleator & Tarjan 1985)
  - Lecture 7: Splay trees, optimal BSTs (Sleator & Tarjan 1985)
  - Lectures 8–9: Unified / working-set structures, Wilber's lower bound
  - Lecture 10–11: Suffix trees (Ukkonen 1995), suffix arrays, LCA (Bender & Farach-Colton 2000)
  - Lecture 12: Succinct data structures, rank/select (Jacobson 1989)
  - Lecture 13: Huffman coding, arithmetic coding, Burrows-Wheeler transform (1994)
  - Lecture 14: Ordered-file maintenance, cache-oblivious model
  - Lectures 15–18: Cache-oblivious linked lists, Funnelsort, Funnelheap (Frigo et al. 1999)
  - Lecture 19: Fault-tolerant data structures (Finocchi & Italiano 2004)

## Contact

For questions, issues, or contributions, please use the GitHub issue tracker.
