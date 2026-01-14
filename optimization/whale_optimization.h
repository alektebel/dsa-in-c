/**
 * Whale Optimization Algorithm Implementation
 * 
 * WOA is a meta-heuristic optimization algorithm inspired by humpback whale hunting behavior.
 * Used extensively in:
 * - Engineering design optimization
 * - Feature selection
 * - Neural network training
 * - Scheduling problems
 */

#ifndef WHALE_OPTIMIZATION_H
#define WHALE_OPTIMIZATION_H

#include <stddef.h>
#include <stdbool.h>

// WOA parameters
typedef struct {
    size_t population_size;
    size_t max_iterations;
    size_t dimension;
    double a_max;                // Initial value for parameter a
    double a_min;                // Final value for parameter a
} WOAParameters;

// Fitness function type
typedef double (*woa_fitness_func_t)(const double *solution, size_t dim, void *data);

// WOA result
typedef struct {
    double *best_solution;
    size_t dimension;
    double best_fitness;
    size_t iterations_run;
} WOAResult;

/**
 * Perform whale optimization
 * @param params WOA parameters
 * @param fitness_func Fitness function to optimize
 * @param bounds_min Lower bounds for each dimension
 * @param bounds_max Upper bounds for each dimension
 * @param user_data User data passed to fitness function
 * @return Result containing best solution
 */
WOAResult* woa_optimize(WOAParameters *params, woa_fitness_func_t fitness_func,
                        double *bounds_min, double *bounds_max, void *user_data);

/**
 * Free WOA result
 * @param result Result to free
 */
void woa_result_free(WOAResult *result);

#endif // WHALE_OPTIMIZATION_H
