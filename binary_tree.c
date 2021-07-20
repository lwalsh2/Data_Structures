/*
 * Binary Tree Operations
 * By: Liam P. Walsh
*/

#include <stdlib.h>
#include <stdio.h>

// Declares tree node struct.
typedef struct tree_node_ {
  // Data of tree node
  int number;
  // Pointers to nodes
  struct tree_node_ * right;
	struct tree_node_ * left;
  struct tree_node_ * parent;
} tree_node;

// Declares tree struct. (hold root)
typedef struct tree_ {
  // The root node of the tree
  tree_node * root;
} tree;

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

// Append node to front of list. (Replaces head node)
int append_node(tree_node * new, tree * list) {
  // Makes sure there is a list and node to append.
	if (!list || !new) {
		return 0;
	}
	// If the list is empty, sets the node as root.
	if (!list->root) {
		list->root = new;
	}
	// Finds the end of the list, and appends to the end.
	else {
    tree_node * iter = list->root;
    int left = 1;
    while (iter) {
      if (new->number <= iter->number) {
				new->parent = iter;
        iter = iter->left;
        left = 1;
      }
      else {
				new->parent = iter;
        iter = iter->right;
        left = 0;
      }
    }
    iter = new->parent;
    if (left) {
      iter->left = new;
    }
    else {
      iter->right = new;
    }
	}
	return 1;
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
	printf("Printing Tree: \n");
	if (!list || !list->root) {
		printf("   No tree, root empty\n");
		return;
	}
	printf("   Root %d ", list->root->number);
	if (list->root->left) {
    printf("Left: %d ", list->root->left->number);
    print_sub_tree(list->root->left);
  }
  if (list->root->right) {
    printf("Right: %d ", list->root->right->number);
    print_sub_tree(list->root->right);
  }
  printf("\n");
}

int main()
{
  printf("Creating Tree:\n");
	tree * list = create_list(create_node(3));
  print_tree(list);
	if (!append_node(create_node(1), list)) {
		printf("Append failed.\n");
	}
  print_tree(list);
	if (!append_node(create_node(4), list)) {
		printf("Append failed.\n");
	}
  print_tree(list);
	if (!append_node(create_node(3), list)) {
		printf("Append failed.\n");
	}
  print_tree(list);
	if (!append_node(create_node(1), list)) {
		printf("Append failed.\n");
	}
  print_tree(list);
  print_small_large_tree(list);

	printf("Deleting Tree:\n");
	if (!empty_list(list)) {
		printf("Empty List failed.\n");
	}
	print_tree(list);
  print_small_large_tree(list);
	free(list);
  return 0;
}
