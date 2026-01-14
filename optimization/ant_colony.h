/**
 * Ant Colony Optimization Implementation
 * 
 * ACO is inspired by ant foraging behavior and pheromone trails.
 * Used extensively in:
 * - Traveling salesman problem
 * - Vehicle routing
 * - Network routing
 * - Job scheduling
 */

#ifndef ANT_COLONY_H
#define ANT_COLONY_H

#include <stddef.h>
#include <stdbool.h>

// ACO parameters
typedef struct {
    size_t num_ants;
    size_t num_iterations;
    double alpha;              // Pheromone importance
    double beta;               // Heuristic importance
    double evaporation_rate;   // Pheromone evaporation
    double pheromone_constant; // Pheromone deposit amount
} ACOParameters;

// Graph for ACO
typedef struct {
    size_t num_nodes;
    double **distances;        // Distance matrix
    double **pheromones;       // Pheromone matrix
    double **heuristic;        // Heuristic information matrix
} ACOGraph;

// ACO result
typedef struct {
    int *best_path;
    size_t path_length;
    double best_cost;
    size_t iterations_run;
} ACOResult;

/**
 * Create ACO graph
 * @param num_nodes Number of nodes in graph
 * @return ACO graph or NULL on failure
 */
ACOGraph* aco_graph_create(size_t num_nodes);

/**
 * Free ACO graph
 * @param graph Graph to free
 */
void aco_graph_free(ACOGraph *graph);

/**
 * Set distance between two nodes
 * @param graph ACO graph
 * @param from Source node
 * @param to Destination node
 * @param distance Distance value
 */
void aco_graph_set_distance(ACOGraph *graph, size_t from, size_t to, double distance);

/**
 * Perform ACO optimization
 * @param graph ACO graph
 * @param params ACO parameters
 * @param start_node Starting node
 * @return Result containing best path found
 */
ACOResult* aco_optimize(ACOGraph *graph, ACOParameters *params, size_t start_node);

/**
 * Free ACO result
 * @param result Result to free
 */
void aco_result_free(ACOResult *result);

#endif // ANT_COLONY_H
