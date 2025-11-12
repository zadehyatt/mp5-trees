/* tree.c
 * Binary Search Tree Module Implementation
 * ECE 2230, Fall 2025
 * Zade Hyatt
 * This file implements a binary search tree module with support for
 * insertion, deletion, searching, and various utility functions.
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "tree.h"

/* Helper function to create a new node */
static node_in_tree_t *create_node(tree_key_t key, data_t *data_ptr)
{
    node_in_tree_t *node = (node_in_tree_t *)malloc(sizeof(node_in_tree_t));
    assert(node != NULL);
    node->key = key;
    node->data_ptr = data_ptr;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/* Helper function to recursively free nodes */
static void free_nodes(node_in_tree_t *node)
{
    if (node == NULL)
        return;
    free_nodes(node->left);
    free_nodes(node->right);
    if (node->data_ptr != NULL)
        free(node->data_ptr);
    free(node);
}

/* Helper function to find minimum node in subtree */
static node_in_tree_t *find_min(node_in_tree_t *node)
{
    if (node == NULL)
        return NULL;
    while (node->left != NULL)
        node = node->left;
    return node;
}

/* Helper function for recursive insert */
/* Returns the node (possibly new) and sets *was_new to 1 if a new node was created */
static node_in_tree_t *insert_recursive(node_in_tree_t *node, tree_key_t key,
                                        data_t *data_ptr, int *comparisons, int *was_new)
{
    if (node == NULL) {
        *was_new = 1;
        return create_node(key, data_ptr);
    }
    
    /* Comparison 1: check if key matches current node */
    (*comparisons)++;
    if (key == node->key) {
        /* Key found - replace data */
        if (node->data_ptr != NULL)
            free(node->data_ptr);
        node->data_ptr = data_ptr;
        *was_new = 0;
        return node;
    }
    
    /* Comparison 2: determine left or right */
    (*comparisons)++;
    if (key < node->key) {
        node->left = insert_recursive(node->left, key, data_ptr, comparisons, was_new);
    } else {
        node->right = insert_recursive(node->right, key, data_ptr, comparisons, was_new);
    }
    
    return node;
}

/* Helper function to remove successor without counting comparisons */
static node_in_tree_t *remove_successor(node_in_tree_t *node, tree_key_t *successor_key, data_t **successor_data)
{
    if (node->left == NULL) {
        /* This node is the successor */
        *successor_key = node->key;
        *successor_data = node->data_ptr;
        node_in_tree_t *temp = node->right;
        free(node);
        return temp;
    }
    node->left = remove_successor(node->left, successor_key, successor_data);
    return node;
}

/* Helper function for recursive remove */
static node_in_tree_t *remove_node(node_in_tree_t *node, tree_key_t key,
                                   data_t **removed_data, int *comparisons)
{
    if (node == NULL) {
        return NULL;
    }
    
    /* Comparison 1: check if key matches current node */
    (*comparisons)++;
    if (key == node->key) {
        /* Found the node to remove */
        *removed_data = node->data_ptr;
        
        /* Case 1: No children */
        if (node->left == NULL && node->right == NULL) {
            free(node);
            return NULL;
        }
        
        /* Case 2: One child */
        if (node->left == NULL) {
            node_in_tree_t *temp = node->right;
            free(node);
            return temp;
        }
        if (node->right == NULL) {
            node_in_tree_t *temp = node->left;
            free(node);
            return temp;
        }
        
        /* Case 3: Two children - find inorder successor (minimum in right subtree) */
        tree_key_t successor_key;
        data_t *successor_data;
        /* Remove successor from right subtree (without counting comparisons) */
        node->right = remove_successor(node->right, &successor_key, &successor_data);
        /* Copy successor's key and data to current node */
        /* Note: removed_data already points to node->data_ptr (set on line 107) */
        /* We need to return that data, so we don't free it here */
        node->key = successor_key;
        node->data_ptr = successor_data;
        return node;
    }
    
    /* Comparison 2: determine left or right */
    (*comparisons)++;
    if (key < node->key) {
        node->left = remove_node(node->left, key, removed_data, comparisons);
    } else {
        node->right = remove_node(node->right, key, removed_data, comparisons);
    }
    
    return node;
}

/* Helper function for recursive search */
static data_t *search_recursive(node_in_tree_t *node, tree_key_t key, int *comparisons)
{
    if (node == NULL) {
        return NULL;
    }
    
    /* Comparison 1: check if key matches current node */
    (*comparisons)++;
    if (key == node->key) {
        return node->data_ptr;
    }
    
    /* Comparison 2: determine left or right */
    (*comparisons)++;
    if (key < node->key) {
        return search_recursive(node->left, key, comparisons);
    } else {
        return search_recursive(node->right, key, comparisons);
    }
}

/* Helper function for recursive level finding */
static int level_recursive(node_in_tree_t *node, tree_key_t key, int current_level, int *comparisons)
{
    if (node == NULL) {
        return current_level;
    }
    
    /* Comparison 1: check if key matches current node */
    (*comparisons)++;
    if (key == node->key) {
        return current_level;
    }
    
    /* Comparison 2: determine left or right */
    (*comparisons)++;
    if (key < node->key) {
        return level_recursive(node->left, key, current_level + 1, comparisons);
    } else {
        return level_recursive(node->right, key, current_level + 1, comparisons);
    }
}

/* Helper function for recursive internal path length calculation */
static int ipl_recursive(node_in_tree_t *node, int level)
{
    if (node == NULL)
        return 0;
    return level + ipl_recursive(node->left, level + 1) + 
           ipl_recursive(node->right, level + 1);
}

/* Helper function for recursive size calculation */
static int size_recursive(node_in_tree_t *node)
{
    if (node == NULL)
        return 0;
    return 1 + size_recursive(node->left) + size_recursive(node->right);
}

/* Create and initialize a new tree */
tree_t *tree_construct(void)
{
    tree_t *T = (tree_t *)malloc(sizeof(tree_t));
    assert(T != NULL);
    T->root = NULL;
    T->size = 0;
    T->comparisons = 0;
    return T;
}

/* Free all memory associated with the tree */
void tree_destruct(tree_t *T)
{
    if (T == NULL)
        return;
    free_nodes(T->root);
    free(T);
}

/* Insert a key-data pair into the tree */
int tree_insert(tree_t *T, tree_key_t key, data_t *data_ptr)
{
    assert(T != NULL);
    
    int comparisons = 0;
    int was_new = 0;
    
    T->root = insert_recursive(T->root, key, data_ptr, &comparisons, &was_new);
    
    /* Update size if a new node was added */
    if (was_new) {
        T->size++;
    }
    T->comparisons = comparisons;
    
    /* Return 0 if key was already in tree (replaced), 1 if new */
    return was_new;
}

/* Remove a key from the tree and return its data pointer */
data_t *tree_remove(tree_t *T, tree_key_t key)
{
    assert(T != NULL);
    
    data_t *removed_data = NULL;
    int comparisons = 0;
    
    T->root = remove_node(T->root, key, &removed_data, &comparisons);
    
    /* Update size if a node was removed */
    if (removed_data != NULL) {
        T->size--;
    }
    T->comparisons = comparisons;
    
    return removed_data;
}

/* Search for a key in the tree and return its data pointer */
data_t *tree_search(tree_t *T, tree_key_t key)
{
    assert(T != NULL);
    
    int comparisons = 0;
    data_t *result = search_recursive(T->root, key, &comparisons);
    
    T->comparisons = comparisons;
    return result;
}

/* Find the level of a key in the tree */
int tree_level(tree_t *T, tree_key_t key)
{
    assert(T != NULL);
    
    int comparisons = 0;
    int level = level_recursive(T->root, key, 0, &comparisons);
    
    T->comparisons = comparisons;
    return level;
}

/* Return the number of keys in the tree */
int tree_size(tree_t *T)
{
    assert(T != NULL);
    return T->size;
}

/* Return the number of comparisons from the most recent operation */
int tree_stats(tree_t *T)
{
    assert(T != NULL);
    return T->comparisons;
}

/* Calculate and return the internal path length of the tree */
int tree_internal_path_len(tree_t *T)
{
    assert(T != NULL);
    return ipl_recursive(T->root, 0);
}

/* Print the tree structure (crude but simple) */
static void ugly_print(node_in_tree_t *node, int level)
{
    if (node == NULL)
        return;
    ugly_print(node->right, level + 1);
    for (int i = 0; i < level; i++)
        printf("     ");  /* print 5 spaces */
    printf("%5d\n", node->key);  /* field width is 5 */
    ugly_print(node->left, level + 1);
}

/* Debug function to print the tree */
void tree_debug_print_tree(tree_t *T)
{
    assert(T != NULL);
    printf("Tree with %d keys\n", T->size);
    ugly_print(T->root, 0);
    printf("\n");
    tree_debug_validate(T);
}

/* Helper function for recursive validation */
static int debug_val_rec(node_in_tree_t *node, int min, int max, int *count)
{
    if (node == NULL)
        return 1;  /* TRUE */
    if (node->key <= min || node->key >= max)
        return 0;  /* FALSE */
    assert(node->data_ptr != NULL);
    (*count)++;
    return debug_val_rec(node->left, min, node->key, count) &&
           debug_val_rec(node->right, node->key, max, count);
}

/* Debug function to validate the tree structure */
void tree_debug_validate(tree_t *T)
{
    assert(T != NULL);
    int size = 0;
    assert(debug_val_rec(T->root, INT_MIN, INT_MAX, &size) == 1);
    assert(size == T->size);
}

