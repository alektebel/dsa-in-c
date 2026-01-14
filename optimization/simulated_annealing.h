/**
 * Simulated Annealing Implementation
 * 
 * Simulated annealing is a probabilistic optimization technique inspired by metallurgy.
 * Used extensively in:
 * - Combinatorial optimization
 * - Circuit design
 * - Traveling salesman problem
 * - Scheduling problems
 */

#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H

#include <stddef.h>
#include <stdbool.h>

// SA parameters
typedef struct {
    double initial_temperature;
    double final_temperature;
    double cooling_rate;
    size_t max_iterations;
    size_t iterations_per_temp;
} SAParameters;

// Energy/cost function type
typedef double (*energy_func_t)(const double *solution, size_t size, void *data);

// Neighbor generation function type
typedef void (*neighbor_func_t)(const double *current, double *neighbor, size_t size, void *data);

// SA result
typedef struct {
    double *best_solution;
    size_t solution_size;
    double best_energy;
    size_t iterations_run;
} SAResult;

/**
 * Perform simulated annealing optimization
 * @param params SA parameters
 * @param initial_solution Initial solution
 * @param solution_size Size of solution
 * @param energy_func Energy/cost function to minimize
 * @param neighbor_func Function to generate neighbor solutions
 * @param user_data User data passed to callback functions
 * @return Result containing best solution found
 */
SAResult* sa_optimize(SAParameters *params, const double *initial_solution,
                      size_t solution_size, energy_func_t energy_func,
                      neighbor_func_t neighbor_func, void *user_data);

/**
 * Calculate acceptance probability for worse solution
 * @param current_energy Current solution energy
 * @param new_energy New solution energy
 * @param temperature Current temperature
 * @return Acceptance probability
 */
double sa_acceptance_probability(double current_energy, double new_energy, 
                                 double temperature);

/**
 * Free SA result
 * @param result Result to free
 */
void sa_result_free(SAResult *result);

#endif // SIMULATED_ANNEALING_H
