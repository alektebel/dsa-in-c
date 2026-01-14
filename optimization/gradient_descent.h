/**
 * Gradient Descent Implementation
 * 
 * Gradient descent is a first-order optimization algorithm for finding local minima.
 * Used extensively in:
 * - Machine learning training
 * - Neural network optimization
 * - Parameter estimation
 * - Convex optimization
 */

#ifndef GRADIENT_DESCENT_H
#define GRADIENT_DESCENT_H

#include <stddef.h>
#include <stdbool.h>

// Gradient descent parameters
typedef struct {
    double learning_rate;
    size_t max_iterations;
    double tolerance;         // Convergence threshold
    bool use_momentum;
    double momentum_factor;
} GDParameters;

// Objective function type
typedef double (*objective_func_t)(const double *x, size_t n, void *data);

// Gradient function type
typedef void (*gradient_func_t)(const double *x, double *grad, size_t n, void *data);

// GD result
typedef struct {
    double *optimal_point;
    size_t dimension;
    double optimal_value;
    size_t iterations_run;
    bool converged;
} GDResult;

/**
 * Perform gradient descent optimization
 * @param initial_point Starting point
 * @param dimension Problem dimension
 * @param params GD parameters
 * @param objective Objective function to minimize
 * @param gradient Gradient function
 * @param user_data User data passed to callbacks
 * @return Result containing optimal point found
 */
GDResult* gradient_descent(const double *initial_point, size_t dimension,
                          GDParameters *params, objective_func_t objective,
                          gradient_func_t gradient, void *user_data);

/**
 * Perform stochastic gradient descent
 * @param initial_point Starting point
 * @param dimension Problem dimension
 * @param params GD parameters
 * @param objective Objective function to minimize
 * @param gradient Stochastic gradient function
 * @param user_data User data passed to callbacks
 * @return Result containing optimal point found
 */
GDResult* stochastic_gradient_descent(const double *initial_point, size_t dimension,
                                     GDParameters *params, objective_func_t objective,
                                     gradient_func_t gradient, void *user_data);

/**
 * Compute numerical gradient using finite differences
 * @param x Point to compute gradient at
 * @param grad Output gradient vector
 * @param dimension Problem dimension
 * @param objective Objective function
 * @param user_data User data
 * @param epsilon Finite difference step size
 */
void gradient_numerical(const double *x, double *grad, size_t dimension,
                       objective_func_t objective, void *user_data, double epsilon);

/**
 * Free GD result
 * @param result Result to free
 */
void gd_result_free(GDResult *result);

#endif // GRADIENT_DESCENT_H
