/**
 * A* Search Algorithm Implementation
 */

#include "astar.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

AStarGraph* astar_graph_create(size_t num_vertices) {
    AStarGraph *graph = (AStarGraph*)malloc(sizeof(AStarGraph));
    if (!graph) return NULL;
    
    graph->num_vertices = num_vertices;
    
    // TODO: Allocate adjacency matrix
    // Initialize all weights to INFINITY
    graph->adjacency_matrix = NULL;
    
    return graph;
}

void astar_graph_free(AStarGraph *graph) {
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

void astar_add_edge(AStarGraph *graph, size_t from, size_t to,
                    double weight, bool directed) {
    // TODO: Add edge with given weight
    // If not directed, add edge in both directions
    (void)graph;
    (void)from;
    (void)to;
    (void)weight;
    (void)directed;
}

AStarResult* astar_find_path(AStarGraph *graph, size_t start, size_t goal,
                             heuristic_func_t heuristic, void *user_data) {
    // TODO: Implement A* algorithm
    // 1. Initialize:
    //    - g_score[start] = 0
    //    - f_score[start] = heuristic(start, goal)
    //    - Add start to open set (priority queue ordered by f_score)
    // 2. While open set not empty:
    //    - current = node in open set with lowest f_score
    //    - If current == goal: reconstruct and return path
    //    - Remove current from open set
    //    - For each neighbor of current:
    //      - tentative_g = g_score[current] + distance(current, neighbor)
    //      - If tentative_g < g_score[neighbor]:
    //        - Update g_score[neighbor] and predecessor
    //        - f_score[neighbor] = g_score[neighbor] + heuristic(neighbor, goal)
    //        - Add neighbor to open set if not already there
    // 3. Return failure if open set becomes empty
    (void)graph;
    (void)start;
    (void)goal;
    (void)heuristic;
    (void)user_data;
    return NULL;
}

double astar_heuristic_euclidean(size_t node, size_t goal, void *data) {
    // TODO: Compute Euclidean distance between node and goal
    // data should contain coordinate information
    (void)node;
    (void)goal;
    (void)data;
    return 0.0;
}

double astar_heuristic_manhattan(size_t node, size_t goal, void *data) {
    // TODO: Compute Manhattan distance between node and goal
    // data should contain coordinate information
    (void)node;
    (void)goal;
    (void)data;
    return 0.0;
}

double astar_heuristic_zero(size_t node, size_t goal, void *data) {
    (void)node;
    (void)goal;
    (void)data;
    return 0.0;
}

void astar_result_free(AStarResult *result) {
    if (!result) return;
    free(result->path);
    free(result);
}
