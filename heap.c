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
int append_node(heap_node * new, heap * list) {
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
  printf("Number of levels: %d\n", count_level(list->root));
  printf("Number Left: %d\n", count_level(list->root->left));
  printf("Number Right: %d\n", count_level(list->root->right));
	printf("Deleting heap:\n");
	if (!empty_list(list)) {
		printf("Empty List failed.\n");
	}
	print_heap(list);
	free(list);
  return 0;
}
