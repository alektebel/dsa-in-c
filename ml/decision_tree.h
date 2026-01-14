/**
 * Decision Tree Implementation
 * 
 * Decision trees are hierarchical models for classification and regression.
 * Used extensively in:
 * - Classification problems
 * - Feature importance analysis
 * - Ensemble methods (Random Forest, Gradient Boosting)
 * - Interpretable machine learning
 */

#ifndef DECISION_TREE_H
#define DECISION_TREE_H

#include <stddef.h>
#include <stdbool.h>

// Tree node
typedef struct DecisionTreeNode {
    bool is_leaf;
    int feature_index;         // Feature to split on
    double threshold;          // Split threshold
    int class_label;           // For classification (leaf nodes)
    double value;              // For regression (leaf nodes)
    struct DecisionTreeNode *left;
    struct DecisionTreeNode *right;
} DecisionTreeNode;

// Decision tree model
typedef struct {
    DecisionTreeNode *root;
    size_t max_depth;
    size_t min_samples_split;
    bool is_classifier;        // True for classification, false for regression
} DecisionTree;

// Training data
typedef struct {
    double **X;                // Feature matrix
    int *y;                    // Labels (classification) or values (regression)
    size_t n_samples;
    size_t n_features;
} TreeTrainingData;

/**
 * Create decision tree
 * @param max_depth Maximum tree depth
 * @param min_samples_split Minimum samples required to split
 * @param is_classifier True for classification, false for regression
 * @return Tree or NULL on failure
 */
DecisionTree* decision_tree_create(size_t max_depth, size_t min_samples_split,
                                   bool is_classifier);

/**
 * Free decision tree
 * @param tree Tree to free
 */
void decision_tree_free(DecisionTree *tree);

/**
 * Train decision tree
 * @param tree Decision tree model
 * @param data Training data
 * @return True if training successful
 */
bool decision_tree_train(DecisionTree *tree, TreeTrainingData *data);

/**
 * Predict for a single sample
 * @param tree Trained tree
 * @param features Feature vector
 * @return Predicted class (classification) or value (regression)
 */
int decision_tree_predict(DecisionTree *tree, const double *features);

/**
 * Compute Gini impurity
 * @param labels Array of labels
 * @param n_samples Number of samples
 * @param n_classes Number of classes
 * @return Gini impurity
 */
double decision_tree_gini_impurity(const int *labels, size_t n_samples, size_t n_classes);

/**
 * Compute information gain
 * @param parent_labels Parent node labels
 * @param parent_size Parent size
 * @param left_labels Left child labels
 * @param left_size Left child size
 * @param right_labels Right child labels
 * @param right_size Right child size
 * @param n_classes Number of classes
 * @return Information gain
 */
double decision_tree_information_gain(const int *parent_labels, size_t parent_size,
                                      const int *left_labels, size_t left_size,
                                      const int *right_labels, size_t right_size,
                                      size_t n_classes);

#endif // DECISION_TREE_H
