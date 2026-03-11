/**
 * Gaussian Process Implementation
 *
 * A Gaussian Process (GP) is a probabilistic model that defines a distribution
 * over functions. Any finite set of function values follows a multivariate
 * Gaussian distribution, making GPs powerful for:
 * - Regression with uncertainty quantification
 * - Bayesian optimization (surrogate models)
 * - Active learning (query by uncertainty)
 * - Spatial statistics (Kriging / geostatistics)
 * - Time series forecasting
 *
 * Key idea: instead of learning a fixed function, a GP learns a distribution
 * over functions consistent with the training data.  Given n training points,
 * prediction requires solving an n×n linear system; the dominant cost is
 * O(n³) for the Cholesky factorisation and O(n) per new prediction.
 *
 * Terminology:
 *   K        – kernel (covariance) matrix evaluated on training inputs
 *   alpha    – K^{-1} y  (precomputed vector used for prediction)
 *   L        – lower-triangular Cholesky factor of K (K = L L^T)
 *   k*       – kernel vector between a new point and training inputs
 *   mu*      – predicted mean  = k*^T alpha
 *   sigma²*  – predicted variance = k(x*,x*) - k*^T (K^{-1}) k*
 */

#ifndef GAUSSIAN_PROCESS_H
#define GAUSSIAN_PROCESS_H

#include <stddef.h>
#include <stdbool.h>

/* -------------------------------------------------------------------------
 * Kernel types
 * ------------------------------------------------------------------------- */

/**
 * Supported covariance kernel functions.
 * Each kernel encodes different prior assumptions about the function.
 */
typedef enum {
    GP_KERNEL_RBF,        /* Radial Basis Function (squared exponential):
                             k(x,x') = sigma² exp(-||x-x'||² / (2 l²))
                             – infinitely differentiable, smooth functions */
    GP_KERNEL_MATERN52,   /* Matérn ν=5/2:
                             k(x,x') = sigma²(1 + √5 r/l + 5r²/(3l²)) exp(-√5 r/l)
                             – twice differentiable, used in Bayesian optimisation */
    GP_KERNEL_MATERN32,   /* Matérn ν=3/2:
                             k(x,x') = sigma²(1 + √3 r/l) exp(-√3 r/l)
                             – once differentiable */
    GP_KERNEL_LINEAR,     /* Linear (dot-product) kernel:
                             k(x,x') = sigma² (x · x')
                             – models linear functions */
    GP_KERNEL_PERIODIC    /* Periodic kernel:
                             k(x,x') = sigma² exp(-2 sin²(π|x-x'|/p) / l²)
                             – models periodic functions */
} GPKernelType;

/**
 * Hyperparameters shared across all kernels.
 * Not every field is used by every kernel type.
 */
typedef struct {
    double length_scale;  /* l  – controls how quickly correlations decay */
    double signal_var;    /* sigma² – overall output variance (amplitude) */
    double noise_var;     /* sigma_n² – observation noise (added to diagonal) */
    double period;        /* p  – period length (GP_KERNEL_PERIODIC only) */
} GPKernelParams;

/* -------------------------------------------------------------------------
 * Core Gaussian Process structure
 * ------------------------------------------------------------------------- */

/**
 * Gaussian Process model.
 *
 * After gp_fit() is called the model stores the Cholesky factor L of
 * (K + sigma_n² I) and the precomputed vector alpha = L^{-T} L^{-1} y,
 * enabling O(n) mean predictions and O(n²) variance predictions.
 */
typedef struct {
    GPKernelType   kernel_type;   /* Which kernel to use                     */
    GPKernelParams params;        /* Kernel hyperparameters                  */

    double        **X_train;      /* Training inputs  [n_train × n_features] */
    double         *y_train;      /* Training targets [n_train]              */
    size_t          n_train;      /* Number of training points               */
    size_t          n_features;   /* Dimensionality of input space           */

    double         *alpha;        /* K^{-1} y – precomputed prediction vector */
    double        **L;            /* Lower Cholesky factor of K              */
    bool            is_fitted;    /* True after gp_fit() succeeds            */
} GaussianProcess;

/**
 * Prediction result for a single query point.
 */
typedef struct {
    double mean;      /* Predicted mean  mu*      */
    double variance;  /* Predicted variance sigma²* (always >= 0) */
    double std_dev;   /* sqrt(variance) – std deviation            */
} GPPrediction;

/* -------------------------------------------------------------------------
 * Construction / destruction
 * ------------------------------------------------------------------------- */

/**
 * Create a new Gaussian Process with the specified kernel.
 *
 * @param kernel_type  Covariance kernel to use
 * @param params       Initial hyperparameter values
 * @param n_features   Dimensionality of the input space
 * @return Allocated GaussianProcess, or NULL on failure
 */
GaussianProcess* gp_create(GPKernelType kernel_type,
                           GPKernelParams params,
                           size_t n_features);

/**
 * Free all memory owned by a GaussianProcess.
 *
 * @param gp GaussianProcess to free (safe to call with NULL)
 */
void gp_free(GaussianProcess *gp);

/* -------------------------------------------------------------------------
 * Kernel evaluation
 * ------------------------------------------------------------------------- */

/**
 * Evaluate the kernel between two input vectors.
 *
 * @param gp  GaussianProcess (for kernel type and params)
 * @param x1  First input vector [n_features]
 * @param x2  Second input vector [n_features]
 * @return k(x1, x2)
 */
double gp_kernel(const GaussianProcess *gp,
                 const double *x1,
                 const double *x2);

/**
 * Build the n×n covariance matrix K for a set of n points.
 * Noise variance is added to the diagonal: K_ij = k(x_i, x_j) + sigma_n² δ_ij
 *
 * @param gp        GaussianProcess
 * @param X         Input matrix [n × n_features]
 * @param n         Number of points
 * @param add_noise Whether to add noise variance to the diagonal
 * @return Allocated n×n matrix, or NULL on failure (caller must free)
 */
double** gp_build_kernel_matrix(const GaussianProcess *gp,
                                double * const *X,
                                size_t n,
                                bool add_noise);

/* -------------------------------------------------------------------------
 * Fitting
 * ------------------------------------------------------------------------- */

/**
 * Fit the GP to training data.
 *
 * Computes the Cholesky factorisation L of K = k(X, X) + sigma_n² I and
 * precomputes alpha = K^{-1} y for fast prediction.
 *
 * @param gp         GaussianProcess to train
 * @param X_train    Training inputs [n_train × n_features]
 * @param y_train    Training targets [n_train]
 * @param n_train    Number of training samples
 * @return true on success, false on failure (e.g. non-positive-definite K)
 */
bool gp_fit(GaussianProcess *gp,
            double * const *X_train,
            const double *y_train,
            size_t n_train);

/* -------------------------------------------------------------------------
 * Prediction
 * ------------------------------------------------------------------------- */

/**
 * Predict the mean and variance at a single query point.
 *
 * Requires gp_fit() to have been called first.
 *
 * mu*    = k(x*, X)^T alpha
 * sigma²* = k(x*,x*) - k(x*, X)^T K^{-1} k(x*, X)
 *         = k(x*,x*) - ||L^{-1} k(x*, X)||²
 *
 * @param gp    Fitted GaussianProcess
 * @param x_new Query input [n_features]
 * @param out   Pointer to store prediction result
 * @return true on success
 */
bool gp_predict(const GaussianProcess *gp,
                const double *x_new,
                GPPrediction *out);

/**
 * Predict mean and variance for a batch of query points.
 *
 * @param gp        Fitted GaussianProcess
 * @param X_new     Query inputs [n_new × n_features]
 * @param n_new     Number of query points
 * @param out       Array to store n_new GPPrediction results (caller allocates)
 * @return true on success
 */
bool gp_predict_batch(const GaussianProcess *gp,
                      double * const *X_new,
                      size_t n_new,
                      GPPrediction *out);

/* -------------------------------------------------------------------------
 * Model selection
 * ------------------------------------------------------------------------- */

/**
 * Compute the log marginal likelihood of the training data.
 *
 * Used as an objective for hyperparameter optimisation:
 *   log p(y | X, theta) = -0.5 y^T K^{-1} y
 *                         - 0.5 log|K|
 *                         - (n/2) log(2 pi)
 *                       = -0.5 alpha^T y - sum(log diag(L)) - (n/2) log(2 pi)
 *
 * @param gp Fitted GaussianProcess
 * @return Log marginal likelihood (higher is better)
 */
double gp_log_marginal_likelihood(const GaussianProcess *gp);

/**
 * Optimise kernel hyperparameters by maximising the log marginal likelihood.
 *
 * Simple grid/gradient approach over (length_scale, signal_var, noise_var).
 * Calls gp_fit() internally for each candidate set of hyperparameters.
 *
 * @param gp              GaussianProcess to update in place
 * @param n_restarts      Number of random restarts for optimisation
 * @return true if optimisation improved the likelihood
 */
bool gp_optimize_hyperparams(GaussianProcess *gp, size_t n_restarts);

/* -------------------------------------------------------------------------
 * Utility
 * ------------------------------------------------------------------------- */

/**
 * Compute the Cholesky decomposition of a symmetric positive-definite matrix.
 *
 * Factors A into L L^T where L is lower triangular.
 *
 * @param A   Input n×n matrix (lower triangle used; upper ignored)
 * @param L   Output n×n lower-triangular Cholesky factor (caller allocates)
 * @param n   Matrix dimension
 * @return true on success, false if A is not positive definite
 */
bool gp_cholesky(double * const *A, double **L, size_t n);

/**
 * Solve the lower-triangular system L x = b in place (forward substitution).
 *
 * @param L   Lower-triangular n×n matrix
 * @param b   Right-hand side vector [n], overwritten with solution x
 * @param n   System dimension
 */
void gp_forward_solve(double * const *L, double *b, size_t n);

/**
 * Solve the upper-triangular system L^T x = b in place (back substitution).
 *
 * @param L   Lower-triangular n×n matrix (transpose is used)
 * @param b   Right-hand side vector [n], overwritten with solution x
 * @param n   System dimension
 */
void gp_back_solve(double * const *L, double *b, size_t n);

/**
 * Free a 2-D matrix allocated as an array of row pointers.
 *
 * @param M Matrix to free
 * @param n Number of rows
 */
void gp_free_matrix(double **M, size_t n);

#endif /* GAUSSIAN_PROCESS_H */
