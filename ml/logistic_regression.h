/**
 * Logistic Regression Implementation
 * 
 * Logistic regression is a classification algorithm for binary outcomes.
 * Used extensively in:
 * - Binary classification
 * - Medical diagnosis
 * - Spam detection
 * - Credit scoring
 */

#ifndef LOGISTIC_REGRESSION_H
#define LOGISTIC_REGRESSION_H

#include <stddef.h>
#include <stdbool.h>

// Logistic regression model
typedef struct {
    double *weights;          // Model weights (including bias)
    size_t num_features;
    double learning_rate;
    size_t max_iterations;
} LogisticRegressionModel;

// Classification data
typedef struct {
    double **X;              // Feature matrix (n_samples x n_features)
    int *y;                  // Binary labels (0 or 1)
    size_t n_samples;
    size_t n_features;
} ClassificationData;

/**
 * Create logistic regression model
 * @param num_features Number of features
 * @param learning_rate Learning rate for gradient descent
 * @param max_iterations Maximum training iterations
 * @return Model or NULL on failure
 */
LogisticRegressionModel* logistic_regression_create(size_t num_features,
                                                    double learning_rate,
                                                    size_t max_iterations);

/**
 * Free logistic regression model
 * @param model Model to free
 */
void logistic_regression_free(LogisticRegressionModel *model);

/**
 * Train model using gradient descent
 * @param model Logistic regression model
 * @param data Training data
 * @return True if training successful
 */
bool logistic_regression_train(LogisticRegressionModel *model, ClassificationData *data);

/**
 * Predict probability for a single sample
 * @param model Trained model
 * @param features Feature vector
 * @return Predicted probability (0 to 1)
 */
double logistic_regression_predict_proba(LogisticRegressionModel *model,
                                         const double *features);

/**
 * Predict class label for a single sample
 * @param model Trained model
 * @param features Feature vector
 * @param threshold Classification threshold (typically 0.5)
 * @return Predicted class (0 or 1)
 */
int logistic_regression_predict(LogisticRegressionModel *model,
                                const double *features, double threshold);

/**
 * Sigmoid function
 * @param x Input value
 * @return Sigmoid(x) = 1 / (1 + exp(-x))
 */
double sigmoid(double x);

/**
 * Compute accuracy
 * @param model Model
 * @param data Data to evaluate on
 * @return Accuracy (0 to 1)
 */
double logistic_regression_accuracy(LogisticRegressionModel *model,
                                    ClassificationData *data);

/**
 * Compute log loss (cross-entropy)
 * @param model Model
 * @param data Data to evaluate on
 * @return Log loss
 */
double logistic_regression_log_loss(LogisticRegressionModel *model,
                                    ClassificationData *data);

#endif // LOGISTIC_REGRESSION_H
