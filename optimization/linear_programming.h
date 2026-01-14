/**
 * Linear Programming (Simplex Method) Implementation
 * 
 * Linear programming finds optimal solutions to problems with linear constraints.
 * Used extensively in:
 * - Resource allocation
 * - Production planning
 * - Transportation problems
 * - Portfolio optimization
 */

#ifndef LINEAR_PROGRAMMING_H
#define LINEAR_PROGRAMMING_H

#include <stddef.h>
#include <stdbool.h>

// LP problem in standard form:
// Maximize: c^T * x
// Subject to: A * x <= b, x >= 0
typedef struct {
    double **A;              // Constraint matrix (m x n)
    double *b;               // Right-hand side (m)
    double *c;               // Objective coefficients (n)
    size_t m;                // Number of constraints
    size_t n;                // Number of variables
    bool is_maximization;    // True for max, false for min
} LPProblem;

// LP solution
typedef struct {
    double *x;               // Optimal solution
    double optimal_value;    // Optimal objective value
    bool is_feasible;
    bool is_unbounded;
    size_t iterations;
} LPSolution;

/**
 * Create LP problem
 * @param num_variables Number of variables
 * @param num_constraints Number of constraints
 * @param is_maximization True for maximization, false for minimization
 * @return LP problem or NULL on failure
 */
LPProblem* lp_problem_create(size_t num_variables, size_t num_constraints,
                             bool is_maximization);

/**
 * Free LP problem
 * @param problem Problem to free
 */
void lp_problem_free(LPProblem *problem);

/**
 * Solve LP problem using Simplex method
 * @param problem LP problem
 * @return Solution or NULL on failure
 */
LPSolution* lp_solve_simplex(LPProblem *problem);

/**
 * Solve LP problem using Dual Simplex method
 * @param problem LP problem
 * @return Solution or NULL on failure
 */
LPSolution* lp_solve_dual_simplex(LPProblem *problem);

/**
 * Add constraint to LP problem
 * @param problem LP problem
 * @param coefficients Constraint coefficients
 * @param rhs Right-hand side value
 * @param constraint_index Index to add constraint at
 */
void lp_add_constraint(LPProblem *problem, const double *coefficients,
                       double rhs, size_t constraint_index);

/**
 * Set objective function
 * @param problem LP problem
 * @param coefficients Objective coefficients
 */
void lp_set_objective(LPProblem *problem, const double *coefficients);

/**
 * Free LP solution
 * @param solution Solution to free
 */
void lp_solution_free(LPSolution *solution);

#endif // LINEAR_PROGRAMMING_H
