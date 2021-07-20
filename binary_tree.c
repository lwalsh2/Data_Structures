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
int search_tree(tree * list, tree_node * key) {
	if (!list || !list->root) {
		return 0;
	}
  tree_node * iter = list->root;
  while (iter) {
    if (iter == key) {
      return 1;
    }
    if (iter->number > key->number) {
      iter = iter->left;
    }
    else {
      iter = iter->right;
    }
  }
  return 0;
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

int count_nodes(tree_node * root) {
  // Makes sure there is a  node.
	if (!root) {
		return 0;
	}
	// Finds the end of the list, and returns count.
  int count = 1;
  count += count_nodes(root->left);
  count += count_nodes(root->right);
	return count;
}

/*
// Swap nodes
tree_node * swap_node(tree_node * root, int left) {
  // Makes sure there is a list and node to append.
  tree_node * tmp = root;
  if (root) {
    if (left && root->left) {
      if (root->left->right) {
        root->left = swap_node(root->right, 0);
      }
      tmp = root->left;
      tmp->parent = root->parent;
      if(root->parent)
      {
        if (root->parent->left == root) {
          root->parent->left = tmp;
        }
        else {
          root->parent->right = tmp;
        }
      }
      root->parent = tmp;
      root->left->right = root;
      root->left = root->left->right;
      }
    }
    else if (!left && root->right) {
      if (root->right->left) {
        root->right = swap_node(root->right, 1);
      }
      tmp = root->right;
      tmp->parent = root->parent;
      if(root->parent)
      {
        if (root->parent->right == root) {
          root->parent->right = tmp;
        }
        else {
          root->parent->right = tmp;
        }
      }
      root->parent = tmp;
      root->right->left = root;
      root->right = root->right->left;
    }
  return tmp;
}
*/

void balance_tree(tree * list) {
  // Makes sure there is a list and node to append.
	if (!list || !list->root) {
		return;
	}
	// Checks balance of tree, and swaps if needed.
  int left = 0;
  int right = 0;
  tree_node * old_root = list->root;
  left = count_nodes(list->root->left);
  right = count_nodes(list->root->right);
  while (left < right/3 || right < left/3) {
    if (left < right/3) {
      printf("Needs root right swap\n");
      //list->root = swap_node(list->root, 0);
    }
    else {
      printf("Needs root left swap\n");
      //list->root = swap_node(list->root, 1);
    }
    left = count_nodes(list->root->left);
    right = count_nodes(list->root->right);
    break; // Swap doesn't work yet
  }
}

int main()
{
  printf("Creating Tree:\n");
	tree * list = create_list(create_node(3));
	if (!append_node(create_node(2), list)) {
		printf("Append failed.\n");
	}
	if (!append_node(create_node(5), list)) {
		printf("Append failed.\n");
	}
  tree_node * node = create_node(4);
	if (!append_node(node, list)) {
		printf("Append failed.\n");
	}
	if (!append_node(create_node(6), list)) {
		printf("Append failed.\n");
	}
  if (!append_node(create_node(7), list)) {
		printf("Append failed.\n");
	}
  if (!append_node(create_node(8), list)) {
		printf("Append failed.\n");
	}
  if (!append_node(create_node(9), list)) {
		printf("Append failed.\n");
	}
  if (!append_node(create_node(10), list)) {
		printf("Append failed.\n");
	}
  if (!append_node(create_node(11), list)) {
		printf("Append failed.\n");
	}
  if (!append_node(create_node(12), list)) {
		printf("Append failed.\n");
	}
	if (!append_node(create_node(1), list)) {
		printf("Append failed.\n");
	}
  print_tree(list);
  print_small_large_tree(list);
  if (search_tree(list, node)) {
    printf("Found node in tree.\n");
  }
  else {
    printf("Didn't find node in tree.\n");
  }
  printf("Number of nodes: %d\n", count_nodes(list->root));
  printf("Number Left: %d\n", count_nodes(list->root->left));
  printf("Number Right: %d\n", count_nodes(list->root->right));
  balance_tree(list);
  print_tree(list);
	printf("Deleting Tree:\n");
	if (!empty_list(list)) {
		printf("Empty List failed.\n");
	}
	print_tree(list);
  print_small_large_tree(list);
	free(list);
  return 0;
}
