/*
 * Single Linked List Operations
 * By: Liam P. Walsh
*/

#include <stdlib.h>
#include <stdio.h>
#include "single_linked_list.h"

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
	return list;
}

// Append node to front of list. (Replaces head node)
int append_front_node(linked_node * new_node, linked_list * list) {
	// Makes sure there is a list and node to append.
	if (!list || !new_node) {
		return 0;
	}
	// If the list is empty, sets the node as head.
	if (!list->head) {
		list->head = new_node;
	}
	// Replaces the current head of the list.
	else {
		new_node->node = list->head;
		list->head = new_node;
	}
	return 1;
}

// Append node to end of list. (Parses for tail)
int append_back_node(linked_node * new_node, linked_list * list) {
	// Makes sure there is a list and node to append.
	if (!list || !new_node) {
		return 0;
	}
	// If the list is empty, sets the node as head.
	if (!list->head) {
		list->head = new_node;
	}
	// Finds the end of the list, and appends to the end.
	else {
		linked_node *node = list->head;
		while (node) {
			if (!node->node) {
				node->node = new_node;
				break;
			}
			node = node->node;
		}
	}
	return 1;
}

// Recursively frees nodes called by the node pointer.
void free_node(linked_node * node) {
	// Recursively calls to the end of the list.
	if (node->node) {
		free_node(node->node);
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
		free_node(list->head);
	}
	// Empties list by setting to NULL.
	list->head = NULL;
	return 1;
}

// Find and replace all instances of given key within given list.
int search_and_destroy_node(linked_list * list, int key) {
	// Verify there's a list and a node to parse.
	if (!list || !list->head) {
		return 0;
	}
	// Sets the current node to parse, and a temporary node to free.
	linked_node *node = list->head;
	linked_node *temp = NULL;
	while (node->node) {
		if (node->node->number == key) {
			temp = node->node;
			node->node = node->node->node;
			free(temp);
		}
		node = node->node;
	}
	// Loop checks all but the head.
	if (list->head->number == key) {
		temp = list->head;
		list->head = list->head->node;
		free(temp);
	}
	return 1;
}

// Parses list and prints node data.
void print_list(linked_list * list) {
	printf("Printing List: \n");
	if (!list || !list->head) {
		printf("   No list, head empty\n");
		return;
	}
	linked_node *node = list->head;
	while (node) {
		printf("   Current Node's int = %d\n", node->number);
		node = node->node;
	}
}
