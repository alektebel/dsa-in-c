/**
 * Integer Programming (Branch and Bound) Implementation
 * 
 * Integer programming solves optimization problems with integer constraints.
 * Used extensively in:
 * - Scheduling and timetabling
 * - Resource allocation
 * - Network design
 * - Combinatorial optimization
 */

#ifndef INTEGER_PROGRAMMING_H
#define INTEGER_PROGRAMMING_H

#include <stddef.h>
#include <stdbool.h>

// IP problem in standard form:
// Maximize/Minimize: c^T * x
// Subject to: A * x <= b, x >= 0, x integer
typedef struct {
    double **A;              // Constraint matrix (m x n)
    double *b;               // Right-hand side (m)
    double *c;               // Objective coefficients (n)
    size_t m;                // Number of constraints
    size_t n;                // Number of variables
    bool is_maximization;    // True for max, false for min
    bool *is_integer;        // True if variable must be integer (for MILP)
} IPProblem;

// IP solution
typedef struct {
    int *x;                  // Optimal integer solution
    double optimal_value;    // Optimal objective value
    bool is_feasible;
    size_t nodes_explored;   // Branch and bound nodes
    size_t iterations;
} IPSolution;

/**
 * Create IP problem
 * @param num_variables Number of variables
 * @param num_constraints Number of constraints
 * @param is_maximization True for maximization, false for minimization
 * @return IP problem or NULL on failure
 */
IPProblem* ip_problem_create(size_t num_variables, size_t num_constraints,
                             bool is_maximization);

/**
 * Free IP problem
 * @param problem Problem to free
 */
void ip_problem_free(IPProblem *problem);

/**
 * Solve IP problem using Branch and Bound
 * @param problem IP problem
 * @return Solution or NULL on failure
 */
IPSolution* ip_solve_branch_and_bound(IPProblem *problem);

/**
 * Solve IP problem using Cutting Plane method
 * @param problem IP problem
 * @return Solution or NULL on failure
 */
IPSolution* ip_solve_cutting_plane(IPProblem *problem);

/**
 * Mark variable as integer
 * @param problem IP problem
 * @param variable_index Variable index
 */
void ip_set_integer_variable(IPProblem *problem, size_t variable_index);

/**
 * Add constraint to IP problem
 * @param problem IP problem
 * @param coefficients Constraint coefficients
 * @param rhs Right-hand side value
 * @param constraint_index Index to add constraint at
 */
void ip_add_constraint(IPProblem *problem, const double *coefficients,
                       double rhs, size_t constraint_index);

/**
 * Set objective function
 * @param problem IP problem
 * @param coefficients Objective coefficients
 */
void ip_set_objective(IPProblem *problem, const double *coefficients);

/**
 * Free IP solution
 * @param solution Solution to free
 */
void ip_solution_free(IPSolution *solution);

#endif // INTEGER_PROGRAMMING_H
