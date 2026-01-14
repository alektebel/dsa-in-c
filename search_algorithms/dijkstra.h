/**
 * Dijkstra's Shortest Path Algorithm Implementation
 * 
 * Dijkstra's algorithm finds shortest paths from a source to all vertices in a weighted graph.
 * Used extensively in:
 * - Network routing protocols (OSPF)
 * - GPS navigation systems
 * - Traffic routing
 * - Social network analysis
 */

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stddef.h>
#include <stdbool.h>
#include <limits.h>

#define DIJKSTRA_INFINITY INT_MAX

// Graph representation for Dijkstra
typedef struct {
    size_t num_vertices;
    double **adjacency_matrix;  // Weight matrix (0 or INFINITY for no edge)
} DijkstraGraph;

// Result structure
typedef struct {
    double *distances;          // Shortest distances from source
    int *predecessors;          // Previous vertex in shortest path
    size_t num_vertices;
    int source_vertex;
} DijkstraResult;

/**
 * Create Dijkstra graph
 * @param num_vertices Number of vertices in graph
 * @return Graph or NULL on failure
 */
DijkstraGraph* dijkstra_graph_create(size_t num_vertices);

/**
 * Free Dijkstra graph
 * @param graph Graph to free
 */
void dijkstra_graph_free(DijkstraGraph *graph);

/**
 * Add weighted edge to graph
 * @param graph Dijkstra graph
 * @param from Source vertex
 * @param to Destination vertex
 * @param weight Edge weight (must be non-negative)
 * @param directed If false, adds edge in both directions
 */
void dijkstra_add_edge(DijkstraGraph *graph, size_t from, size_t to,
                       double weight, bool directed);

/**
 * Run Dijkstra's algorithm from source vertex
 * @param graph Dijkstra graph
 * @param source Source vertex
 * @return Result containing shortest paths
 */
DijkstraResult* dijkstra_shortest_paths(DijkstraGraph *graph, size_t source);

/**
 * Get shortest path from source to target
 * @param result Dijkstra result
 * @param target Target vertex
 * @param path Output array for path (caller allocates)
 * @param max_length Maximum path length
 * @return Length of path, or -1 if no path exists
 */
int dijkstra_get_path(DijkstraResult *result, size_t target, int *path, int max_length);

/**
 * Get distance from source to target
 * @param result Dijkstra result
 * @param target Target vertex
 * @return Distance, or DIJKSTRA_INFINITY if unreachable
 */
double dijkstra_get_distance(DijkstraResult *result, size_t target);

/**
 * Free Dijkstra result
 * @param result Result to free
 */
void dijkstra_result_free(DijkstraResult *result);

#endif // DIJKSTRA_H
