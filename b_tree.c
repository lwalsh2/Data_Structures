/*
 * B Tree Operations
 * By: Liam P. Walsh
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct tree_node_ tree_node;
typedef struct tree_node_group_ tree_node_group;
typedef struct tree_ tree;

// Declares tree node struct.
struct tree_node_ {
  // Data of tree node
  int number;
  // Pointer to nodes
  tree_node_group * group;
};

// Declares tree struct. (hold root)
struct tree_node_group_ {
  // The root node of the tree
  tree_node * left;
  tree_node * right;
  tree_node_group * left_child;
  tree_node_group * middle_child;
  tree_node_group * right_child;
  tree_node_group * parent_group;
};

// Declares tree struct. (hold root)
struct tree_ {
  // The root node of the tree
  tree_node_group * root;
};

// Allocates node with the given data, and returns address.
tree_node * create_node(int number) {
	// Allocate data for node, setting values to NULL/0.
	tree_node * node = calloc(1, sizeof(tree_node));
	// Set the node's data
	node->number = number;
	return node;
}

// Allocates node with the given data, and returns address.
tree_node_group * create_node_group() {
	// Allocate data for node, setting values to NULL/0.
	tree_node_group * group = calloc(1, sizeof(tree_node_group));
	return group;
}

// Allocates tree with the given root, and returns address.
tree * create_list() {
	// Allocate list.
	tree * tree_struct = calloc(1, sizeof(tree));

	return tree_struct;
}

// Recursively frees nodes called by the node pointer.
void free_node(tree_node * node) {
	if (!node) {
		return;
	}
	// Frees node.
	free(node);
}

// Recursively frees nodes called by the node pointer.
void free_node_group(tree_node_group * group) {
	if (!group) {
		return;
	}
  // Free both nodes.
	free_node(group->left);
  free_node(group->right);
  // Recursively calls to the end of the list.
  free_node_group(group->left_child);
  free_node_group(group->middle_child);
  free_node_group(group->right_child);
	// Frees group, starting from the end of the list.
	free(group);
}

// Frees nodes and sets head to NULL.
int empty_list(tree * list) {
	// Verify there's a list
	if (!list) {
		return 0;
	}
	// Free any nodes attached to the list.
	if (list->root) {
		free_node_group(list->root);
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
  tree_node_group * iter = list->root;
  while (iter) {
    if (iter->right) {
      if (iter->right->number == key) {
        return iter->right;
      }
      if (iter->right->number < key) {
        iter = iter->right_child;
      }
      else if (iter->left->number > key) {
        iter = iter->left_child;
      }
      else {
        iter = iter->middle_child;
      }
    }
    else if (iter->left) {
      if (iter->left->number == key) {
        return iter->left;
      }
      else {
        return NULL;
      }
    }
    else {
      return NULL;
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
  tree_node_group * iter = list->root;
	while (iter->left_child) {
    iter = iter->left_child;
  }
  printf("   Left-most: %d\n", iter->left->number);
  // Find largest
  iter = list->root;
	while (iter->right_child) {
    iter = iter->right_child;
  }
  if (iter->right) {
    printf("   Right-most: %d\n", iter->right->number);
  }
  else {
    printf("   Right-most: %d\n", iter->left->number);
  }
}

// Parses list and prints node data.
void print_sub_tree(tree_node_group * group) {
	if (!group) {
		return;
	}
	printf("Group: ");
  if (group->left) {
    printf("Left: %d ", group->left->number);
  }
  if (group->right) {
    printf("Right: %d ", group->right->number);
  }
  if (group->left_child) {
    printf("\n Left ");
    print_sub_tree(group->left_child);
  }
  if (group->middle_child) {
    printf("\n Middle ");
    print_sub_tree(group->middle_child);
  }
  if (group->right_child) {
    printf("\n Right ");
    print_sub_tree(group->right_child);
  }
}

// Parses list and prints node data.
void print_tree(tree * list) {
	printf("\nPrinting Tree: \n");
	if (!list || !list->root) {
		printf("   No tree, root empty\n");
		return;
	}
	print_sub_tree(list->root);
  printf("\n");
}

// Counts the furthest level of child nodes.
int count_level(tree_node_group * root) {
  // Makes sure there is a  node.
	if (!root) {
		return 0;
	}
	// Finds the end of the list, and returns count.
  int cL = count_level(root->left_child);
  int cM = count_level(root->middle_child);
  int cR = count_level(root->right_child);
  if (cL > cM) {
    if (cL > cR) {
      return cL + 1;
    }
    return cR + 1;
  }
  else if (cM > cR) {
    return cM + 1;
  }
	return cR + 1;
}

/* Balance not implemented yet.
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
*/
// Append node to front of list. (Replaces head node)
int append_node(tree_node * new, tree * list) {
  // Makes sure there is a list and node to append.
	if (!list || !new) {
		return 0;
	}
	// If the list is empty, sets the node as root.
	if (!list->root) {
    list->root = create_node_group();
		list->root->left = new;
    new->group = list->root;
	}
	// Finds the end of the list, and appends to the end.
	else {
    tree_node_group * iter = list->root;
    tree_node_group * pri_iter = list->root;
    int direction = 0;
    int added = 0;
    while (iter) {
      if (iter->right) {
        if (iter->right->number < new->number) {
          pri_iter = iter;
          iter = iter->right_child;
          direction = 1;
        }
        else if (iter->left->number > new->number) {
          pri_iter = iter;
          iter = iter->left_child;
          direction = -1;
        }
        else {
          pri_iter = iter;
          iter = iter->middle_child;
          direction = 0;
        }
      }
      else if (iter->left) {
        if (iter->left->number < new->number) {
          iter->right = new;
          new->group = iter;
          added = 1;
        }
        else {
          iter->right = iter->left;
          iter->left = new;
          new->group = iter;
          added = 1;
        }
      }
    }
    if (!added) {
      iter = create_node_group();
      if (direction == -1) {
        pri_iter->left_child = iter;
        iter->parent_group = pri_iter;
      }
      else if (direction == 0) {
        pri_iter->middle_child = iter;
        iter->parent_group = pri_iter;
      }
      else {
        pri_iter->right_child = iter;
        iter->parent_group = pri_iter;
      }
      iter->left = new;
      new->group = iter;
    }
	}
  // balance_tree(list);
	return 1;
}

/* Remove node (Similar to swap/rotate)
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
  // balance_tree(list);
}*/

int main()
{
  printf("Creating Tree:\n");
	tree * list = create_list();
  if (!append_node(create_node(5), list)) {
		printf("Append failed.\n");
	}
  print_tree(list);
	if (!append_node(create_node(2), list)) {
		printf("Append failed.\n");
	}
  print_tree(list);
	if (!append_node(create_node(3), list)) {
		printf("Append failed.\n");
	}
  print_tree(list);
	if (!append_node(create_node(4), list)) {
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
  tree_node * node = search_tree(list, 4);

  if (node) {
    printf("Found node in tree.\n");
    /*
    remove_node(list, node);
    if (!search_tree(list, 4)) {
      printf("Successfully removed node from tree.\n");
    }
    else {
      printf("Didn't remove node from tree.\n");
    }*/
  }
  else {
    printf("Didn't find node in tree.\n");
  }
  printf("Number of levels: %d\n", count_level(list->root));
	printf("Deleting Tree:\n");
	if (!empty_list(list)) {
		printf("Empty List failed.\n");
	}
	print_tree(list);
  print_small_large_tree(list);
	free(list);
  return 0;
}
