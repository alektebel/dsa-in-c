/**
 * Conjugate Gradient Method Implementation
 * 
 * Conjugate gradient is an efficient method for solving linear systems and optimization.
 * Used extensively in:
 * - Solving large sparse linear systems
 * - Optimization of quadratic functions
 * - Machine learning
 * - Numerical simulations
 */

#ifndef CONJUGATE_GRADIENT_H
#define CONJUGATE_GRADIENT_H

#include <stddef.h>
#include <stdbool.h>

// CG parameters
typedef struct {
    size_t max_iterations;
    double tolerance;
} CGParameters;

// Matrix-vector multiplication function type
typedef void (*matvec_func_t)(const double *x, double *result, size_t n, void *data);

// CG result
typedef struct {
    double *solution;
    size_t dimension;
    size_t iterations_run;
    double residual_norm;
    bool converged;
} CGResult;

/**
 * Solve linear system Ax = b using conjugate gradient
 * @param A_matvec Function to compute A*x
 * @param b Right-hand side vector
 * @param initial_guess Initial guess for solution
 * @param dimension Problem dimension
 * @param params CG parameters
 * @param user_data User data passed to A_matvec
 * @return Result containing solution
 */
CGResult* conjugate_gradient_solve(matvec_func_t A_matvec, const double *b,
                                   const double *initial_guess, size_t dimension,
                                   CGParameters *params, void *user_data);

/**
 * Optimize quadratic function using conjugate gradient
 * @param gradient_func Gradient function
 * @param initial_point Starting point
 * @param dimension Problem dimension
 * @param params CG parameters
 * @param user_data User data passed to gradient_func
 * @return Result containing optimal point
 */
CGResult* conjugate_gradient_optimize(matvec_func_t gradient_func,
                                      const double *initial_point,
                                      size_t dimension, CGParameters *params,
                                      void *user_data);

/**
 * Compute dot product of two vectors
 * @param a First vector
 * @param b Second vector
 * @param n Vector length
 * @return Dot product
 */
double vector_dot(const double *a, const double *b, size_t n);

/**
 * Compute L2 norm of a vector
 * @param x Vector
 * @param n Vector length
 * @return L2 norm
 */
double vector_norm(const double *x, size_t n);

/**
 * Free CG result
 * @param result Result to free
 */
void cg_result_free(CGResult *result);

#endif // CONJUGATE_GRADIENT_H
