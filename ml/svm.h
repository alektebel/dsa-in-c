/**
 * Support Vector Machine (SVM) Implementation
 * 
 * SVM finds optimal hyperplane for classification with maximum margin.
 * Used extensively in:
 * - Binary classification
 * - Text classification
 * - Image recognition
 * - Bioinformatics
 */

#ifndef SVM_H
#define SVM_H

#include <stddef.h>
#include <stdbool.h>

// Kernel function type
typedef double (*kernel_func_t)(const double *x1, const double *x2, size_t n, void *params);

// SVM model
typedef struct {
    double *weights;           // Weight vector (for linear SVM)
    double bias;               // Bias term
    double **support_vectors;  // Support vectors
    double *alphas;            // Lagrange multipliers
    int *sv_labels;            // Support vector labels
    size_t n_support_vectors;
    size_t n_features;
    double C;                  // Regularization parameter
    kernel_func_t kernel;      // Kernel function
    void *kernel_params;       // Kernel parameters
} SVMModel;

// SVM training parameters
typedef struct {
    double C;                  // Regularization parameter
    size_t max_iterations;
    double tolerance;
    kernel_func_t kernel;      // Kernel function
    void *kernel_params;       // Kernel parameters (e.g., gamma for RBF)
} SVMParameters;

/**
 * Create SVM model
 * @param n_features Number of features
 * @param params SVM parameters
 * @return Model or NULL on failure
 */
SVMModel* svm_create(size_t n_features, SVMParameters *params);

/**
 * Free SVM model
 * @param model Model to free
 */
void svm_free(SVMModel *model);

/**
 * Train SVM using Sequential Minimal Optimization (SMO)
 * @param model SVM model
 * @param X Feature matrix (n_samples x n_features)
 * @param y Labels (+1 or -1)
 * @param n_samples Number of samples
 * @return True if training successful
 */
bool svm_train(SVMModel *model, double **X, int *y, size_t n_samples);

/**
 * Predict class for a single sample
 * @param model Trained model
 * @param features Feature vector
 * @return Predicted class (+1 or -1)
 */
int svm_predict(SVMModel *model, const double *features);

/**
 * Compute decision function value
 * @param model Model
 * @param features Feature vector
 * @return Decision function value (positive = class +1, negative = class -1)
 */
double svm_decision_function(SVMModel *model, const double *features);

/**
 * Linear kernel
 * @param x1 First vector
 * @param x2 Second vector
 * @param n Vector dimension
 * @param params Unused
 * @return x1 · x2
 */
double svm_kernel_linear(const double *x1, const double *x2, size_t n, void *params);

/**
 * Polynomial kernel
 * @param x1 First vector
 * @param x2 Second vector
 * @param n Vector dimension
 * @param params Pointer to struct {int degree; double coef0}
 * @return (x1 · x2 + coef0)^degree
 */
double svm_kernel_polynomial(const double *x1, const double *x2, size_t n, void *params);

/**
 * RBF (Gaussian) kernel
 * @param x1 First vector
 * @param x2 Second vector
 * @param n Vector dimension
 * @param params Pointer to double gamma
 * @return exp(-gamma * ||x1 - x2||^2)
 */
double svm_kernel_rbf(const double *x1, const double *x2, size_t n, void *params);

#endif // SVM_H
