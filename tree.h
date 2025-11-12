/* tree.h
 * Binary Search Tree Module Header
 * ECE 2230, Fall 2025
 * Zade Hyatt
 * This header file defines the data structures and function prototypes
 * for a binary search tree module.
 */

#ifndef TREE_H //This is just to prevent file from being included multiple times
#define TREE_H

#include <limits.h>

/* Fixed type definitions - DO NOT CHANGE */
typedef int tree_key_t;
typedef int data_t;

/* Tree node structure */
typedef struct NodeTag {
    tree_key_t key;
    data_t *data_ptr;
    struct NodeTag *left;
    struct NodeTag *right;
} node_in_tree_t;

/* Tree header structure */
typedef struct TreeTag {
    node_in_tree_t *root;
    int size;
    int comparisons;
} tree_t;

/* Function prototypes */

/* Construction and destruction */
tree_t *tree_construct(void);
void tree_destruct(tree_t *T);


int tree_insert(tree_t *T, tree_key_t key, data_t *data_ptr);
data_t *tree_remove(tree_t *T, tree_key_t key);
data_t *tree_search(tree_t *T, tree_key_t key);
int tree_level(tree_t *T, tree_key_t key);
int tree_size(tree_t *T);
int tree_stats(tree_t *T);

/* Additional functions */
int tree_internal_path_len(tree_t *T);

/* Debugging functions */
void tree_debug_print_tree(tree_t *T);
void tree_debug_validate(tree_t *T);

#endif /* TREE_H */

