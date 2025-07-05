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
heap_node * create_node(int number);

// Allocates heap with the given max, and returns address.
heap * create_list();

// Recursively frees nodes called by the node pointer.
void free_node(heap_node * node, heap * list);

// Frees nodes and sets head to NULL.
int empty_list(heap * list);

// Parses list and prints node data.
void print_sub_heap(heap_node * node);

// Parses list and prints node data.
void print_heap(heap * list);

// Counts the furthest level of child nodes.
int count_level(heap_node * root);

// Counts the furthest level of child nodes.
int count_full_left(heap_node * root);

// Counts the furthest level of child nodes.
int count_full_right(heap_node * root);

// Swaps as needed until max heap is valid.
void balance_up_heap(heap_node * node, heap * list);

// Append node to front of list. (Replaces head node)
int append_node(heap_node * new_node, heap * list);

// Parses list and fill array.
int sub_tree_fill(heap_node * node, heap_node ** heap_array, int i);

// Search for a node with the given data using DFS.
heap_node * heap_sub_DFS(heap_node * root, int number);

// Search for a node with the given data using DFS.
heap_node * heap_DFS(heap * list, int number);

// Search for a node with the given data using BFS.
heap_node * heap_BFS(heap * list, int number);
