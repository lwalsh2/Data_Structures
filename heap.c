/*
 * Max Heap Operations
 * By: Liam P. Walsh
 * heap uses AVL method (Balances after append and remove)
*/

#include <stdlib.h>
#include <stdio.h>

// Declares heap node struct.
typedef struct heap_node_ {
  // Data of heap node
  int number;
  // Pointers to nodes
  struct heap_node_ * right;
	struct heap_node_ * left;
  struct heap_node_ * parent;
} heap_node;

// Declares heap struct. (hold root)
typedef struct heap_ {
  // The root node of the heap
  heap_node * root;
  int size;
} heap;

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
int count_full_left(heap_node * root) {
  // Makes sure there is a  node.
	if (!root) {
		return 0;
	}
	// Finds the end of the list, and returns count.
	return 1 + count_full_left(root->left);
}

// Counts the furthest level of child nodes.
int count_full_right(heap_node * root) {
  // Makes sure there is a  node.
	if (!root) {
		return 0;
	}
	// Finds the end of the list, and returns count.
  return 1 + count_full_right(root->right);
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
int append_node(heap_node * new, heap * list) {
  // Makes sure there is a list and node to append.
	if (!list || !new) {
		return 0;
	}
  list->size += 1;
	// If the list is empty, sets the node as root.
	if (!list->root) {
		list->root = new;
	}
	// Finds the end of the list, and appends to the end.
	else {
    heap_node * iter = list->root;
    int parent = 0; // 0 - L, 1 - R
    while (iter) {
      if (count_full_left(iter) <= count_full_right(iter)+1 && count_full_left(iter->left) != count_full_right(iter->left)) {
				new->parent = iter;
        iter = iter->left;
        parent = 0;
      }
      else if (count_full_left(iter) <= count_full_right(iter) && count_full_left(iter->left) == count_full_right(iter->left)) {
				new->parent = iter;
        iter = iter->left;
        parent = 0;
      }
      else {
				new->parent = iter;
        iter = iter->right;
        parent = 1;
      }
    }
    iter = new->parent;
    if (parent) {
      iter->right = new;
    }
    else {
      iter->left = new;
    }
    balance_up_heap(new, list);
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

int main()
{
  printf("Creating Heap:\n");
	heap * list = create_list();
	if (!append_node(create_node(2), list)) {
		printf("Append failed.\n");
	}
	if (!append_node(create_node(5), list)) {
		printf("Append failed.\n");
	}
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
  print_heap(list);

  // Search Algorithms
  if (heap_DFS(list, 8)) {
		printf("DFS found 8.\n");
	}
  else {
    printf("DFS didn't find 8.\n");
  }
  if (heap_BFS(list, 8)) {
		printf("BFS found 8.\n");
	}
  else {
    printf("BFS didn't find 8.\n");
  }

  if (!append_node(create_node(1), list)) {
		printf("Append failed.\n");
	}

	printf("Deleting heap:\n");
	if (!empty_list(list)) {
		printf("Empty List failed.\n");
	}
	print_heap(list);
	free(list);
  return 0;
}
