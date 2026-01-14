/**
 * Dijkstra's Shortest Path Algorithm Implementation
 */

#include "dijkstra.h"
#include <stdlib.h>
#include <string.h>

DijkstraGraph* dijkstra_graph_create(size_t num_vertices) {
    DijkstraGraph *graph = (DijkstraGraph*)malloc(sizeof(DijkstraGraph));
    if (!graph) return NULL;
    
    graph->num_vertices = num_vertices;
    
    // TODO: Allocate adjacency matrix
    // Initialize all weights to INFINITY
    graph->adjacency_matrix = NULL;
    
    return graph;
}

void dijkstra_graph_free(DijkstraGraph *graph) {
    if (!graph) return;
    
    // TODO: Free adjacency matrix
    if (graph->adjacency_matrix) {
        for (size_t i = 0; i < graph->num_vertices; i++) {
            free(graph->adjacency_matrix[i]);
        }
        free(graph->adjacency_matrix);
    }
    
    free(graph);
}

void dijkstra_add_edge(DijkstraGraph *graph, size_t from, size_t to,
                       double weight, bool directed) {
    // TODO: Add edge with given weight
    // If not directed, add edge in both directions
    (void)graph;
    (void)from;
    (void)to;
    (void)weight;
    (void)directed;
}

DijkstraResult* dijkstra_shortest_paths(DijkstraGraph *graph, size_t source) {
    // TODO: Implement Dijkstra's algorithm
    // 1. Initialize distances to INFINITY except source (0)
    // 2. Create priority queue with all vertices
    // 3. While queue not empty:
    //    - Extract vertex u with minimum distance
    //    - For each neighbor v of u:
    //      - If distance[u] + weight(u,v) < distance[v]:
    //        - Update distance[v] and predecessor[v]
    //        - Update v's priority in queue
    // 4. Return result
    (void)graph;
    (void)source;
    return NULL;
}

int dijkstra_get_path(DijkstraResult *result, size_t target, int *path, int max_length) {
    // TODO: Reconstruct path from source to target using predecessors
    // Traverse backwards from target to source, then reverse
    (void)result;
    (void)target;
    (void)path;
    (void)max_length;
    return -1;
}

double dijkstra_get_distance(DijkstraResult *result, size_t target) {
    if (!result || target >= result->num_vertices) {
        return DIJKSTRA_INFINITY;
    }
    return result->distances[target];
}

void dijkstra_result_free(DijkstraResult *result) {
    if (!result) return;
    free(result->distances);
    free(result->predecessors);
    free(result);
}
