/**
 * Depth First Search (DFS) Implementation
 * 
 * DFS is a fundamental graph traversal algorithm used in:
 * - Dependency resolution
 * - Topological sorting
 * - Cycle detection
 * - Path finding
 * - Connected components
 */

#ifndef DEPTH_FIRST_SEARCH_H
#define DEPTH_FIRST_SEARCH_H

#include <stdbool.h>
#include <stddef.h>

// Graph representation using adjacency list
typedef struct GraphNode {
    int vertex;                     // Vertex ID
    struct GraphNode *next;         // Next adjacent vertex
} GraphNode;

typedef struct Graph {
    int num_vertices;               // Number of vertices
    GraphNode **adjacency_list;     // Array of adjacency lists
} Graph;

// DFS result information
typedef struct DFSResult {
    int *visited_order;             // Order vertices were visited
    int *parent;                    // Parent of each vertex in DFS tree
    int *discovery_time;            // Discovery time of each vertex
    int *finish_time;               // Finish time of each vertex
    bool *visited;                  // Visited flag for each vertex
    int order_count;                // Number of vertices visited
} DFSResult;

/**
 * Create a new graph
 * @param num_vertices Number of vertices in the graph
 * @return Pointer to the newly created graph
 */
Graph* graph_create(int num_vertices);

/**
 * Add an edge to the graph
 * @param graph The graph
 * @param from Source vertex
 * @param to Destination vertex
 * @param directed If true, add directed edge; otherwise undirected
 * @return true if successful, false otherwise
 */
bool graph_add_edge(Graph *graph, int from, int to, bool directed);

/**
 * Perform DFS from a starting vertex
 * @param graph The graph
 * @param start Starting vertex
 * @return DFS result structure with traversal information
 */
DFSResult* dfs_search(Graph *graph, int start);

/**
 * Perform DFS on entire graph (handles disconnected components)
 * @param graph The graph
 * @return DFS result structure with traversal information
 */
DFSResult* dfs_search_all(Graph *graph);

/**
 * Check if there is a path between two vertices using DFS
 * @param graph The graph
 * @param start Start vertex
 * @param target Target vertex
 * @return true if path exists, false otherwise
 */
bool dfs_has_path(Graph *graph, int start, int target);

/**
 * Find a path between two vertices using DFS
 * @param graph The graph
 * @param start Start vertex
 * @param target Target vertex
 * @param path Array to store the path
 * @param max_length Maximum path length
 * @return Length of path found, or -1 if no path exists
 */
int dfs_find_path(Graph *graph, int start, int target, int *path, int max_length);

/**
 * Detect cycle in directed graph using DFS
 * @param graph The graph (must be directed)
 * @return true if cycle exists, false otherwise
 */
bool dfs_detect_cycle_directed(Graph *graph);

/**
 * Detect cycle in undirected graph using DFS
 * @param graph The graph (must be undirected)
 * @return true if cycle exists, false otherwise
 */
bool dfs_detect_cycle_undirected(Graph *graph);

/**
 * Perform topological sort using DFS
 * @param graph The graph (must be directed acyclic)
 * @param result Array to store topologically sorted vertices
 * @return Number of vertices in result, or -1 if graph has cycle
 */
int dfs_topological_sort(Graph *graph, int *result);

/**
 * Find strongly connected components using DFS
 * @param graph The graph
 * @param components Array to store component ID for each vertex
 * @return Number of strongly connected components
 */
int dfs_strongly_connected_components(Graph *graph, int *components);

/**
 * Find all articulation points (cut vertices) using DFS
 * @param graph The graph
 * @param articulation_points Array to store articulation points
 * @param max_points Maximum number of points to return
 * @return Number of articulation points found
 */
int dfs_find_articulation_points(Graph *graph, int *articulation_points, 
                                 int max_points);

/**
 * Destroy DFS result and free memory
 * @param result The DFS result to destroy
 */
void dfs_result_destroy(DFSResult *result);

/**
 * Destroy graph and free memory
 * @param graph The graph to destroy
 */
void graph_destroy(Graph *graph);

/**
 * Print graph (for debugging)
 * @param graph The graph to print
 */
void graph_print(Graph *graph);

#endif // DEPTH_FIRST_SEARCH_H
