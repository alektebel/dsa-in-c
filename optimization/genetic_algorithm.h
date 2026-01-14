/**
 * Genetic Algorithm Implementation
 * 
 * Genetic algorithms are evolutionary optimization techniques inspired by natural selection.
 * Used extensively in:
 * - Parameter optimization
 * - Machine learning hyperparameter tuning
 * - Scheduling and resource allocation
 * - Combinatorial optimization problems
 */

#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <stddef.h>
#include <stdbool.h>

// Chromosome representation
typedef struct {
    double *genes;        // Gene values
    size_t gene_count;    // Number of genes
    double fitness;       // Fitness score
} Chromosome;

// GA parameters
typedef struct {
    size_t population_size;
    size_t gene_count;
    size_t max_generations;
    double mutation_rate;
    double crossover_rate;
    double elitism_rate;
} GAParameters;

// Fitness function type
typedef double (*fitness_func_t)(const double *genes, size_t gene_count, void *data);

// GA result
typedef struct {
    Chromosome best_chromosome;
    double best_fitness;
    size_t generations_run;
} GAResult;

/**
 * Create a genetic algorithm optimizer
 * @param params GA parameters
 * @return Initialized GA or NULL on failure
 */
GAResult* ga_optimize(GAParameters *params, fitness_func_t fitness_func, 
                      void *user_data, double *gene_min, double *gene_max);

/**
 * Create a random chromosome
 * @param gene_count Number of genes
 * @param gene_min Minimum gene values
 * @param gene_max Maximum gene values
 * @return Chromosome or NULL on failure
 */
Chromosome* ga_chromosome_create(size_t gene_count, double *gene_min, double *gene_max);

/**
 * Free chromosome memory
 * @param chromosome Chromosome to free
 */
void ga_chromosome_free(Chromosome *chromosome);

/**
 * Perform crossover between two parent chromosomes
 * @param parent1 First parent
 * @param parent2 Second parent
 * @param child1 First child output
 * @param child2 Second child output
 */
void ga_crossover(const Chromosome *parent1, const Chromosome *parent2,
                  Chromosome *child1, Chromosome *child2);

/**
 * Mutate a chromosome
 * @param chromosome Chromosome to mutate
 * @param mutation_rate Probability of mutation per gene
 * @param gene_min Minimum gene values
 * @param gene_max Maximum gene values
 */
void ga_mutate(Chromosome *chromosome, double mutation_rate,
               double *gene_min, double *gene_max);

/**
 * Free GA result
 * @param result Result to free
 */
void ga_result_free(GAResult *result);

#endif // GENETIC_ALGORITHM_H
