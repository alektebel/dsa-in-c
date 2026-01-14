/**
 * Newton's Method (with Hessian) Implementation
 * 
 * Newton's method uses second-order derivatives (Hessian) for optimization.
 * Used extensively in:
 * - Nonlinear optimization
 * - Machine learning (Newton-CG, L-BFGS)
 * - Root finding
 * - Parameter estimation
 */

#ifndef NEWTON_METHOD_H
#define NEWTON_METHOD_H

#include <stddef.h>
#include <stdbool.h>

// Newton method parameters
typedef struct {
    size_t max_iterations;
    double tolerance;
    bool use_line_search;      // Use line search for step size
} NewtonParameters;

// Objective function type
typedef double (*newton_objective_t)(const double *x, size_t n, void *data);

// Gradient function type
typedef void (*newton_gradient_t)(const double *x, double *grad, size_t n, void *data);

// Hessian function type (returns Hessian matrix)
typedef void (*newton_hessian_t)(const double *x, double **hessian, size_t n, void *data);

// Newton result
typedef struct {
    double *optimal_point;
    size_t dimension;
    double optimal_value;
    size_t iterations_run;
    bool converged;
} NewtonResult;

/**
 * Optimize using Newton's method
 * @param initial_point Starting point
 * @param dimension Problem dimension
 * @param params Newton parameters
 * @param objective Objective function
 * @param gradient Gradient function
 * @param hessian Hessian function
 * @param user_data User data passed to callbacks
 * @return Result containing optimal point
 */
NewtonResult* newton_optimize(const double *initial_point, size_t dimension,
                              NewtonParameters *params, newton_objective_t objective,
                              newton_gradient_t gradient, newton_hessian_t hessian,
                              void *user_data);

/**
 * Solve linear system using Cholesky decomposition
 * @param A Symmetric positive definite matrix (n x n)
 * @param b Right-hand side vector
 * @param x Solution vector (output)
 * @param n Dimension
 * @return True if successful
 */
bool newton_solve_linear_system(double **A, const double *b, double *x, size_t n);

/**
 * Compute numerical Hessian using finite differences
 * @param x Point to compute Hessian at
 * @param hessian Output Hessian matrix
 * @param dimension Problem dimension
 * @param objective Objective function
 * @param user_data User data
 * @param epsilon Finite difference step size
 */
void newton_numerical_hessian(const double *x, double **hessian, size_t dimension,
                              newton_objective_t objective, void *user_data,
                              double epsilon);

/**
 * Free Newton result
 * @param result Result to free
 */
void newton_result_free(NewtonResult *result);

#endif // NEWTON_METHOD_H
