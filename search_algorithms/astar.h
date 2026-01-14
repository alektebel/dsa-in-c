/**
 * A* Search Algorithm Implementation
 * 
 * A* is an informed search algorithm that uses heuristics to find optimal paths efficiently.
 * Used extensively in:
 * - Pathfinding in games and robotics
 * - GPS navigation
 * - Puzzle solving (15-puzzle, Rubik's cube)
 * - Motion planning
 */

#ifndef ASTAR_H
#define ASTAR_H

#include <stddef.h>
#include <stdbool.h>
#include <limits.h>

#define ASTAR_INFINITY INT_MAX

// Heuristic function type (estimates cost from node to goal)
typedef double (*heuristic_func_t)(size_t node, size_t goal, void *data);

// Graph representation for A*
typedef struct {
    size_t num_vertices;
    double **adjacency_matrix;  // Weight matrix
} AStarGraph;

// A* result
typedef struct {
    int *path;                  // Path from start to goal
    size_t path_length;
    double path_cost;
    size_t nodes_expanded;
    bool path_found;
} AStarResult;

/**
 * Create A* graph
 * @param num_vertices Number of vertices
 * @return Graph or NULL on failure
 */
AStarGraph* astar_graph_create(size_t num_vertices);

/**
 * Free A* graph
 * @param graph Graph to free
 */
void astar_graph_free(AStarGraph *graph);

/**
 * Add weighted edge to graph
 * @param graph A* graph
 * @param from Source vertex
 * @param to Destination vertex
 * @param weight Edge weight (must be non-negative)
 * @param directed If false, adds edge in both directions
 */
void astar_add_edge(AStarGraph *graph, size_t from, size_t to,
                    double weight, bool directed);

/**
 * Find shortest path from start to goal using A*
 * @param graph A* graph
 * @param start Start vertex
 * @param goal Goal vertex
 * @param heuristic Heuristic function (admissible for optimal path)
 * @param user_data User data passed to heuristic
 * @return Result containing path if found
 */
AStarResult* astar_find_path(AStarGraph *graph, size_t start, size_t goal,
                             heuristic_func_t heuristic, void *user_data);

/**
 * Euclidean distance heuristic (for grid-based graphs)
 * @param node Current node
 * @param goal Goal node
 * @param data User data (should be coordinate array)
 * @return Euclidean distance estimate
 */
double astar_heuristic_euclidean(size_t node, size_t goal, void *data);

/**
 * Manhattan distance heuristic (for grid-based graphs)
 * @param node Current node
 * @param goal Goal node
 * @param data User data (should be coordinate array)
 * @return Manhattan distance estimate
 */
double astar_heuristic_manhattan(size_t node, size_t goal, void *data);

/**
 * Zero heuristic (reduces A* to Dijkstra)
 * @param node Current node
 * @param goal Goal node
 * @param data User data (unused)
 * @return Always 0
 */
double astar_heuristic_zero(size_t node, size_t goal, void *data);

/**
 * Free A* result
 * @param result Result to free
 */
void astar_result_free(AStarResult *result);

#endif // ASTAR_H
