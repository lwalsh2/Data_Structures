/*
 * Max Heap Operations
 * By: Liam P. Walsh
 * heap uses AVL method (Balances after append and remove)
*/

#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

// Allocates node with the given data, and returns address.
heap_node * create_node(int number) {
	// Allocate data for node, setting values to NULL/0.
	heap_node * node = calloc(1, sizeof(heap_node));
	// Set the node's data
	node->number = number;
	return node;
}

// Allocates heap with the given max, and returns address.
heap * create_list() {
	// Allocate list.
	heap * heap_struct = calloc(1, sizeof(heap));

	return heap_struct;
}

// Recursively frees nodes called by the node pointer.
void free_node(heap_node * node, heap * list) {
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
int empty_list(heap * list) {
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

// Parses list and prints node data.
void print_sub_heap(heap_node * node) {
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
    print_sub_heap(node->left);
  }
  if (node->right) {
    print_sub_heap(node->right);
  }
}

// Parses list and prints node data.
void print_heap(heap * list) {
	printf("\nPrinting heap: \n");
	if (!list || !list->root) {
		printf("   No heap, root empty\n");
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
    print_sub_heap(list->root->left);
  }
  if (list->root->right) {
    print_sub_heap(list->root->right);
  }
  printf("\n");
}

// Counts the furthest level of child nodes.
int count_level(heap_node * root) {
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

// Counts the furthest level of child nodes.
int count_full_left(heap_node * root) {
  // Makes sure there is a  node.
	if (!root) {
		return 0;
	}
	// Finds the end of the list, and returns count.
	return 1 + count_level(root->left);
}

// Counts the furthest level of child nodes.
int count_full_right(heap_node * root) {
  // Makes sure there is a  node.
	if (!root) {
		return 0;
	}
	// Finds the end of the list, and returns count.
  return 1 + count_level(root->right);
}

// Swaps as needed until max heap is valid.
void balance_up_heap(heap_node * node, heap * list) {
  // Makes sure there is a list and node to append.
	if (!node || !list) {
		return;
	}
  int tmp_number = 0;
  // If parent is smaller, swap data of nodes.
  while (node->parent != NULL && node->number > node->parent->number) {
    tmp_number = node->number;
    node->number = node->parent->number;
    node->parent->number = tmp_number;
    node = node->parent;
  }
}

// Append node to front of list. (Replaces head node)
int append_node(heap_node * new_node, heap * list) {
  // Makes sure there is a list and node to append.
	if (!list || !new_node) {
		return 0;
	}
  list->size += 1;
	// If the list is empty, sets the node as root.
	if (!list->root) {
		list->root = new_node;
	}
	// Finds the end of the list, and appends to the end.
	else {
    heap_node * iter = list->root;
    int parent = 0; // 0 - L, 1 - R
    int cL = 0;
    int cLL = 0;
    int cR = 0;
    int cRL = 0;
    while (iter) {
      cL = count_full_left(iter);
      cLL = count_full_left(iter->left);
      cR = count_full_right(iter);
      cRL = count_full_right(iter->left);
      if (cL <= cR+1 && cLL != cRL) {
				new_node->parent = iter;
        iter = iter->left;
        parent = 0;
      }
      else if (cL <= cR && cLL == cRL) {
				new_node->parent = iter;
        iter = iter->left;
        parent = 0;
      }
      else {
				new_node->parent = iter;
        iter = iter->right;
        parent = 1;
      }
    }
    iter = new_node->parent;
    if (parent) {
      iter->right = new_node;
    }
    else {
      iter->left = new_node;
    }
    balance_up_heap(new_node, list);
	}
	return 1;
}

// Parses list and fill array.
int sub_tree_fill(heap_node * node, heap_node ** heap_array, int i) {
	if (!node) {
		return 0;
	}
  if (node->left) {
    i = sub_tree_fill(node->left, heap_array, i);
  }
  heap_array[i++] = node;
  if (node->right) {
    i = sub_tree_fill(node->right, heap_array, i);
  }
  return i;
}

// Search for a node with the given data using DFS.
heap_node * heap_sub_DFS(heap_node * root, int number) {
  if (root->number == number) {
    return root;
  }
  heap_node * node = NULL;
  if(root->left) {
    node = heap_sub_DFS(root->left, number);
  }
  if (!node && root->right) {
    node = heap_sub_DFS(root->right, number);
  }
  return node;
}

// Search for a node with the given data using DFS.
heap_node * heap_DFS(heap * list, int number) {
  if (!list || !list->root) {
    return NULL;
  }
  return heap_sub_DFS(list->root, number);
}

// Search for a node with the given data using BFS.
heap_node * heap_BFS(heap * list, int number) {
  if (!list || !list->root) {
    return NULL;
  }
  // Convert to array to parse
  heap_node ** heap_array = calloc(list->size, sizeof(heap_node));
  sub_tree_fill(list->root, heap_array, 0);
  for (int i = 0; i < list->size; ++i) {
    if (heap_array[i]->number == number) {
      return heap_array[i];
    }
  }
  return NULL;
}
