/**
 * Linear Regression Implementation
 * 
 * Linear regression models the relationship between features and a continuous target.
 * Used extensively in:
 * - Predictive modeling
 * - Statistical analysis
 * - Trend analysis
 * - Financial forecasting
 */

#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include <stddef.h>
#include <stdbool.h>

// Linear regression model
typedef struct {
    double *weights;          // Model weights (including bias)
    size_t num_features;
    double learning_rate;
    size_t max_iterations;
} LinearRegressionModel;

// Training data
typedef struct {
    double **X;              // Feature matrix (n_samples x n_features)
    double *y;               // Target vector (n_samples)
    size_t n_samples;
    size_t n_features;
} RegressionData;

/**
 * Create linear regression model
 * @param num_features Number of features
 * @param learning_rate Learning rate for gradient descent
 * @param max_iterations Maximum training iterations
 * @return Model or NULL on failure
 */
LinearRegressionModel* linear_regression_create(size_t num_features,
                                                double learning_rate,
                                                size_t max_iterations);

/**
 * Free linear regression model
 * @param model Model to free
 */
void linear_regression_free(LinearRegressionModel *model);

/**
 * Train model using gradient descent
 * @param model Linear regression model
 * @param data Training data
 * @return True if training successful
 */
bool linear_regression_train(LinearRegressionModel *model, RegressionData *data);

/**
 * Train model using normal equation (closed-form solution)
 * @param model Linear regression model
 * @param data Training data
 * @return True if training successful
 */
bool linear_regression_train_normal_equation(LinearRegressionModel *model,
                                             RegressionData *data);

/**
 * Make prediction for a single sample
 * @param model Trained model
 * @param features Feature vector
 * @return Predicted value
 */
double linear_regression_predict(LinearRegressionModel *model, const double *features);

/**
 * Compute mean squared error
 * @param model Model
 * @param data Data to evaluate on
 * @return MSE
 */
double linear_regression_mse(LinearRegressionModel *model, RegressionData *data);

/**
 * Compute R-squared score
 * @param model Model
 * @param data Data to evaluate on
 * @return R-squared value
 */
double linear_regression_r2_score(LinearRegressionModel *model, RegressionData *data);

#endif // LINEAR_REGRESSION_H
