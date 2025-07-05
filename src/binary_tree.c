/*
 * Binary Tree Operations
 * By: Liam P. Walsh
 * Tree uses AVL method (Balances after append and remove)
*/

#include <stdlib.h>
#include <stdio.h>
#include "binary_tree.h"

// Allocates node with the given data, and returns address.
tree_node * create_node(int number) {
	// Allocate data for node, setting values to NULL/0.
	tree_node * node = calloc(1, sizeof(tree_node));
	// Set the node's data
	node->number = number;
	return node;
}

// Allocates tree with the given root, and returns address.
tree * create_list(tree_node * root) {
	// Allocate list.
	tree * tree_struct = malloc(sizeof(tree));
	// Set the head of the list.
	tree_struct->root = root;

	return tree_struct;
}

// Recursively frees nodes called by the node pointer.
void free_node(tree_node * node, tree * list) {
	if (!node) {
		return;
	}
	// Recursively calls to the end of the list.
	if (node->left) {
		free_node(node->left, list);
	}
  if (node->right) {
    free_node(node->right, list);
	}
	// Frees nodes, starting from the end of the list.
	free(node);
}

// Frees nodes and sets head to NULL.
int empty_list(tree * list) {
	// Verify there's a list
	if (!list) {
		return 0;
	}
	// Free any nodes attached to the list.
	if (list->root) {
		free_node(list->root, list);
	}
	// Empties list by setting to NULL.
	list->root = NULL;
	return 1;
}

// Finds and returns first instance of a node with given key.
tree_node * search_tree(tree * list, int key) {
	if (!list || !list->root) {
		return NULL;
	}
  tree_node * iter = list->root;
  while (iter) {
    if (iter->number == key) {
      return iter;
    }
    if (iter->number > key) {
      iter = iter->left;
    }
    else {
      iter = iter->right;
    }
  }
  return NULL;
}

// Parses tree for largest and smallest nodes
void print_small_large_tree(tree * list) {
	printf("Printing Tree's L/R-most nodes: \n");
	if (!list || !list->root) {
		printf("   No tree, root empty\n");
		return;
	}
	// Find smallest
  tree_node * iter = list->root;
	while (iter->left) {
    iter = iter->left;
  }
  printf("   Left-most: %d\n", iter->number);
  // Find largest
  iter = list->root;
	while (iter->right) {
    iter = iter->right;
  }
  printf("   Right-most: %d\n", iter->number);
}

// Parses list and prints node data.
void print_sub_tree(tree_node * node) {
	if (!node) {
		return;
	}
	printf("\n   %d: ", node->number);
  if (node->left) {
    printf("Left: %d ", node->left->number);
  }
  if (node->right) {
    printf("Right: %d ", node->right->number);
  }
  if (node->left) {
    print_sub_tree(node->left);
  }
  if (node->right) {
    print_sub_tree(node->right);
  }
}

// Parses list and prints node data.
void print_tree(tree * list) {
	printf("\nPrinting Tree: \n");
	if (!list || !list->root) {
		printf("   No tree, root empty\n");
		return;
	}
	printf("   Root %d ", list->root->number);
	if (list->root->left) {
    printf("Left: %d ", list->root->left->number);
  }
  if (list->root->right) {
    printf("Right: %d ", list->root->right->number);
  }
  if (list->root->left) {
    print_sub_tree(list->root->left);
  }
  if (list->root->right) {
    print_sub_tree(list->root->right);
  }
  printf("\n");
}

// Counts the furthest level of child nodes.
int count_level(tree_node * root) {
  // Makes sure there is a  node.
	if (!root) {
		return 0;
	}
	// Finds the end of the list, and returns count.
  int cL = count_level(root->left);
  int cR = count_level(root->right);
  if (cL > cR) {
    return cL + 1;
  }
	return cR + 1;
}


// Swap/Rotate nodes
tree_node * swap_node(tree_node * root, int left) {
  // Makes sure there is a list and node.
  tree_node * tmp = root;
  if (root && left) {
    if (root->left->right)
    {
      root->left = swap_node(root->left, 0);
    }
    tmp = root->left;
    tmp->parent = root->parent;
    root->parent = tmp;
    root->left = tmp->right;
    tmp->right = root;
  }
  else if (root && !left) {
    if (root->right->left)
    {
      root->right = swap_node(root->right, 1);
    }
    tmp = root->right;
    tmp->parent = root->parent;
    root->parent = tmp;
    root->right = tmp->left;
    tmp->left = root;
  }
  return tmp;
}

// Recursively balances nodes by checking the node's left and right levels.
void balance_sub_tree(tree_node * parent, tree_node * node, int left_node) {
  // Makes sure there is a list and node to append.
	if (!node || !parent) {
		return;
	}
	// Checks balance of tree, and swaps if needed.
  int left = 0;
  int right = 0;
  balance_sub_tree(node, node->left, 1);
  balance_sub_tree(node, node->right, 0);
  left = count_level(node->left);
  right = count_level(node->right);
  while (left+1 < right || right+1 < left) {
    if (left+1 < right) {
      node = swap_node(node, 0);
    }
    else {
      node = swap_node(node, 1);
    }
    if (left_node) {
      parent->left = node;
    }
    else {
      parent->right = node;
    }
    left = count_level(node->left);
    right = count_level(node->right);
  }
}

// Balances tree by calling balance_sub_tree, and swap_node.
void balance_tree(tree * list) {
  // Makes sure there is a list and node to append.
	if (!list || !list->root) {
		return;
	}
	// Checks balance of tree, and swaps if needed.
  int left = 0;
  int right = 0;
  balance_sub_tree(list->root, list->root->left, 1);
  balance_sub_tree(list->root, list->root->right, 0);
  left = count_level(list->root->left);
  right = count_level(list->root->right);
  while (left+1 < right || right+1 < left) {
    if (left+1 < right) {
      list->root = swap_node(list->root, 0);
    }
    else {
      list->root = swap_node(list->root, 1);
    }
    left = count_level(list->root->left);
    right = count_level(list->root->right);
  }
}

// Append node to front of list. (Replaces head node)
int append_node(tree_node * new_node, tree * list) {
  // Makes sure there is a list and node to append.
	if (!list || !new_node) {
		return 0;
	}
	// If the list is empty, sets the node as root.
	if (!list->root) {
		list->root = new_node;
	}
	// Finds the end of the list, and appends to the end.
	else {
    tree_node * iter = list->root;
    int left = 1;
    while (iter) {
      if (new_node->number <= iter->number) {
				new_node->parent = iter;
        iter = iter->left;
        left = 1;
      }
      else {
				new_node->parent = iter;
        iter = iter->right;
        left = 0;
      }
    }
    iter = new_node->parent;
    if (left) {
      iter->left = new_node;
    }
    else {
      iter->right = new_node;
    }
	}
  balance_tree(list);
	return 1;
}

// Remove node (Similar to swap/rotate)
void remove_node(tree * list, tree_node * root) {
  // Makes sure there is a list and node.
  if (!list || !root) {
    return;
  }
  tree_node * tmp = root;
  if (list->root == root) {
    if (root->left->right)
    {
      root->left = swap_node(root->left, 0);
    }
    tmp = root->left;
    tmp->parent = NULL;
    list->root = tmp;
    free(root);
  }
  else if (root->parent->right == root) {
    if (root->left->right)
    {
      root->left = swap_node(root->left, 0);
    }
    tmp = root->left;
    tmp->right = root->right;
    tmp->parent = root->parent;
    tmp->parent->right = tmp;
    free(root);
  }
  else if (root->parent->left == root) {
    if (root->right->left)
    {
      root->right = swap_node(root->right, 1);
    }
    tmp = root->right;
    tmp->left = root->left;
    tmp->parent = root->parent;
    tmp->parent->left = tmp;
    free(root);
  }
  balance_tree(list);
}
