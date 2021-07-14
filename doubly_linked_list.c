/*
 * Doubly Linked List Operations
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
linked_node * create_node(int number) {
	// Allocate data for node, setting values to NULL/0.
	linked_node * node = calloc(1, sizeof(node));
	// Set the node's data
	node->number = number;
	return node;
}

// Allocates list with the given head, and returns address.
linked_list * create_list(linked_node * head) {
	// Allocate list.
	linked_list * list = malloc(sizeof(linked_list));
	// Set the head of the list.
	list->head = head;
	list->tail = head;
	head->prev = head;
	head->next = head;

	return list;
}

// Append node to front of list. (Replaces head node)
int append_front_node(linked_node * new, linked_list * list) {
	// Makes sure there is a list and node to append.
	if (!list || !new) {
		return 0;
	}
	// If the list is empty, sets the node as head.
	if (!list->head) {
		list->head = new;
		list->tail = new;
		new->prev = list->head;
		new->next = list->head;
	}
	// Replaces the current head of the list.
	else {
		list->head->prev = new;
		new->next = list->head;
		list->head = new;
		list->tail->next = new;
	}
	return 1;
}

// Append node to end of list. (Parses for tail)
int append_back_node(linked_node * new, linked_list * list) {
	// Makes sure there is a list and node to append.
	if (!list || !new) {
		return 0;
	}
	// If the list is empty, sets the node as head.
	if (!list->head) {
		list->head = new;
		list->tail = new;
		new->prev = list->head;
		new->next = list->head;
	}
	// Finds the end of the list, and appends to the end.
	else {
		list->tail->next = new;
		new->next = list->head;
		list->tail = new;
		list->head->prev = new;
	}
	return 1;
}

// Recursively frees nodes called by the node pointer.
void free_node(linked_node * node, linked_list * list) {
	// Recursively calls to the end of the list.
	if (node->next != list->head) {
		free_node(node->next, list);
	}
	// Frees nodes, starting from the end of the list.
	free(node);
}

// Frees nodes and sets head to NULL.
int empty_list(linked_list * list) {
	// Verify there's a list
	if (!list) {
		return 0;
	}
	// Free any nodes attached to the list.
	if (list->head) {
		free_node(list->head, list);
	}
	// Empties list by setting to NULL.
	list->head = NULL;
	list = NULL;
	return 1;
}

// Parses list and prints node data.
void print_list(linked_list * list) {
	printf("Printing List: \n");
	if (!list || !list->head) {
		printf("   No list, head empty\n");
		return;
	}
	printf("   Head Node's int = %d\n", list->head->number);
	linked_node *node = list->head->next;
	while (node != list->head) {
		printf("   Current Node's int = %d\n", node->number);
		node = node->next;
	}
}

int main()
{
  printf("Creating Linked list:\n");
	linked_list * list = create_list(create_node(3));
  print_list(list);
	if (!append_back_node(create_node(1), list)) {
		printf("Append Back failed.\n");
	}
  print_list(list);
	if (!append_back_node(create_node(2), list)) {
		printf("Append Back failed.\n");
	}
  print_list(list);
	if (!append_back_node(create_node(3), list)) {
		printf("Append Back failed.\n");
	}
  print_list(list);
	if (!append_front_node(create_node(1), list)) {
		printf("Append Front failed.\n");
	}
  print_list(list);

	printf("Deleting Linked list:\n");
	if (!empty_list(list)) {
		printf("Empty List failed.\n");
	}
	print_list(list);
	free(list);
  return 0;
}
