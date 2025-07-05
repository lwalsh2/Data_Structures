/*
 * Double Linked List Operations
 * Circular Linked
 * By: Liam P. Walsh
*/

#include <stdlib.h>
#include <stdio.h>

// Declares linked node struct.
typedef struct linked_node_ {
  // Data of linked list node
  int number;
  // The next node
  struct linked_node_ * prev;
	struct linked_node_ * next;
} linked_node;

// Declares linked list struct. (hold first node)
typedef struct linked_list_ {
  // The first node of the list
  linked_node * head;
	linked_node * tail;
} linked_list;

// Allocates node with the given data, and returns address.
linked_node * create_node(int number);

// Allocates list with the given head, and returns address.
linked_list * create_list(linked_node * head);

// Append node to front of list. (Replaces head node)
int append_front_node(linked_node * new_node, linked_list * list);

// Append node to end of list. (Parses for tail)
int append_back_node(linked_node * new_node, linked_list * list);

// Recursively frees nodes called by the node pointer.
void free_node(linked_node * node, linked_list * list);

// Frees nodes and sets head to NULL.
int empty_list(linked_list * list);

// Parses list and prints node data.
void print_list(linked_list * list);
