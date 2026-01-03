/**
 * Breadth First Search (BFS) Implementation
 * 
 * BFS is a fundamental graph traversal algorithm used in:
 * - Shortest path in unweighted graphs
 * - Level-order traversal
 * - Network broadcasting
 * - Social network analysis
 * - Web crawling
 */

#ifndef BREADTH_FIRST_SEARCH_H
#define BREADTH_FIRST_SEARCH_H

#include <stdbool.h>
#include <stddef.h>

// Use same graph structure as DFS
typedef struct GraphNode {
    int vertex;
    struct GraphNode *next;
} GraphNode;

typedef struct Graph {
    int num_vertices;
    GraphNode **adjacency_list;
} Graph;

// BFS result information
typedef struct BFSResult {
    int *visited_order;             // Order vertices were visited
    int *parent;                    // Parent of each vertex in BFS tree
    int *distance;                  // Distance from source to each vertex
    bool *visited;                  // Visited flag for each vertex
    int order_count;                // Number of vertices visited
} BFSResult;

// Queue for BFS (simple implementation)
typedef struct QueueNode {
    int vertex;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
    int size;
} Queue;

/**
 * Create a new graph
 * @param num_vertices Number of vertices
 * @return Pointer to newly created graph
 */
Graph* bfs_graph_create(int num_vertices);

/**
 * Add edge to graph
 * @param graph The graph
 * @param from Source vertex
 * @param to Destination vertex
 * @param directed If true, add directed edge
 * @return true if successful
 */
bool bfs_graph_add_edge(Graph *graph, int from, int to, bool directed);

/**
 * Perform BFS from a starting vertex
 * @param graph The graph
 * @param start Starting vertex
 * @return BFS result with traversal information
 */
BFSResult* bfs_search(Graph *graph, int start);

/**
 * Perform BFS on entire graph (handles disconnected components)
 * @param graph The graph
 * @return BFS result with traversal information
 */
BFSResult* bfs_search_all(Graph *graph);

/**
 * Find shortest path between two vertices using BFS
 * @param graph The graph (unweighted)
 * @param start Start vertex
 * @param target Target vertex
 * @param path Array to store the path
 * @param max_length Maximum path length
 * @return Length of shortest path, or -1 if no path exists
 */
int bfs_shortest_path(Graph *graph, int start, int target, int *path, int max_length);

/**
 * Find shortest distance between two vertices
 * @param graph The graph
 * @param start Start vertex
 * @param target Target vertex
 * @return Shortest distance, or -1 if no path exists
 */
int bfs_shortest_distance(Graph *graph, int start, int target);

/**
 * Check if graph is bipartite using BFS
 * @param graph The graph
 * @return true if graph is bipartite, false otherwise
 */
bool bfs_is_bipartite(Graph *graph);

/**
 * Find all vertices at a given distance from start
 * @param graph The graph
 * @param start Start vertex
 * @param distance Target distance
 * @param vertices Array to store vertices at distance
 * @param max_vertices Maximum number of vertices to return
 * @return Number of vertices found at given distance
 */
int bfs_vertices_at_distance(Graph *graph, int start, int distance, 
                             int *vertices, int max_vertices);

/**
 * Find connected components using BFS
 * @param graph The graph
 * @param components Array to store component ID for each vertex
 * @return Number of connected components
 */
int bfs_connected_components(Graph *graph, int *components);

/**
 * Multi-source BFS (BFS from multiple starting points)
 * @param graph The graph
 * @param sources Array of source vertices
 * @param num_sources Number of source vertices
 * @return BFS result with distances from nearest source
 */
BFSResult* bfs_multi_source(Graph *graph, int *sources, int num_sources);

/**
 * Create a queue for BFS
 * @return Pointer to newly created queue
 */
Queue* queue_create(void);

/**
 * Enqueue an element
 * @param queue The queue
 * @param vertex Vertex to enqueue
 * @return true if successful
 */
bool queue_enqueue(Queue *queue, int vertex);

/**
 * Dequeue an element
 * @param queue The queue
 * @return Dequeued vertex, or -1 if queue is empty
 */
int queue_dequeue(Queue *queue);

/**
 * Check if queue is empty
 * @param queue The queue
 * @return true if empty
 */
bool queue_is_empty(Queue *queue);

/**
 * Destroy queue
 * @param queue The queue to destroy
 */
void queue_destroy(Queue *queue);

/**
 * Destroy BFS result
 * @param result The BFS result to destroy
 */
void bfs_result_destroy(BFSResult *result);

/**
 * Destroy graph
 * @param graph The graph to destroy
 */
void bfs_graph_destroy(Graph *graph);

/**
 * Print graph
 * @param graph The graph to print
 */
void bfs_graph_print(Graph *graph);

#endif // BREADTH_FIRST_SEARCH_H
