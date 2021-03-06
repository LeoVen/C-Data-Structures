/**
 * @file BinarySearchTree.h
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 17/05/2018
 *
 * @brief Header file for @c BinarySearchTree implementations in C
 *
 */

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "Core.h"

#ifndef BT_PRINT_SPACES

#define BT_PRINT_SPACES 4

#endif

	/**
	 * A @c BinarySearchTreeNode is what a @c BinarySearchTree is composed of.
	 * It it much like a @c BinaryTree (Node) with one pointer to its left
	 * child, one to its right child and another to its parent, being NULL if
	 * that Node is the @c root.
	 */
	typedef struct BinarySearchTreeNode
	{
		int key;                             /*!< Node's key */
		int count;                           /*!< Amount of keys */
		struct BinarySearchTreeNode *right;  /*!< Pointer to right child */
		struct BinarySearchTreeNode *left;   /*!< Pointer to left child */
		struct BinarySearchTreeNode *parent; /*!< Pointer to parent Node */
	} BinarySearchTreeNode;

	/**
	 * A @c BinarySearchTree is much like a @c BinaryTree but now with a rule
	 * for inserting the nodes. This now makes every @c BinarySearchTreeNode
	 * binded to its descriptor, the @c BinarySearchTree, which has a size
	 * variable counting the amount of elements in that tree and a pointer to
	 * the first node added, the @c root. The insertion rule is that every Node
	 * to the left must have a lower (key) value (data in this case) than its
	 * parent, higher values to the right and no duplicate nodes.
	 *
	 * @b Advantages over @c BinaryTree
	 * - All nodes are ordered by their @c key value where the left node has a
	 * key lower and the right node has a higher key value
	 * - Useful to implement binary search algorithm
	 *
	 * @b Drawbacks
	 * - The tree structure might be askew with worst case search as
	 * <code>O(n)</code>
	 * - The search might not always be <code>O(log n)</code>
	 *
	 * @b Functions
	 *
	 * @c BinarySearchTree.c
	 */
	typedef struct BinarySearchTree
	{
		size_t size;					   /*!< Total @c BinarySearchTree elements */
		struct BinarySearchTreeNode *root; /*!< Pointer to the very first node in the @c BinarySearchTree */
	} BinarySearchTree;

	Status bst_init_tree(BinarySearchTree **bst);
	Status bst_init_node(BinarySearchTreeNode **node);

	Status bst_make_node(BinarySearchTreeNode **node, int value);

	Status bst_insert(BinarySearchTree *bst, int value);

	Status bst_remove(BinarySearchTree *bst, int value);

	Status bst_pop(BinarySearchTree *bst, int *result);

	Status bst_display_wrapper(BinarySearchTree *bst, int display);
	Status bst_display_raw(BinarySearchTreeNode *node, size_t spaces);
	Status bst_display_interactive(BinarySearchTreeNode *node, size_t spaces);
	Status bst_display_clean(BinarySearchTreeNode *node, size_t spaces);

	Status bst_delete(BinarySearchTree **bst);
	Status bst_delete_node(BinarySearchTreeNode **node);
	Status bst_erase(BinarySearchTree **bst);

	Status bst_key_max(BinarySearchTree *bst, int *result);
	Status bst_key_min(BinarySearchTree *bst, int *result);
	Status bst_find_max(BinarySearchTree *bst, BinarySearchTreeNode **result);
	Status bst_find_min(BinarySearchTree *bst, BinarySearchTreeNode **result);

	Status bst_search(BinarySearchTree *bst, int key, BinarySearchTreeNode **result);
	BinarySearchTreeNode* bst_node_find(BinarySearchTreeNode *root, int value);

	bool bst_is_empty(BinarySearchTree *bst);

	size_t bst_height(BinarySearchTreeNode *node);
	size_t bst_depth(BinarySearchTreeNode *node);

	Status bst_traversal_wrapper(BinarySearchTree *bst, int traversal);
	Status bst_traversal_preorder(BinarySearchTreeNode *node);
	Status bst_traversal_inorder(BinarySearchTreeNode *node);
	Status bst_traversal_postorder(BinarySearchTreeNode *node);

	Status bst_traversal_leaves(BinarySearchTreeNode *node);

#ifdef __cplusplus
}
#endif;
