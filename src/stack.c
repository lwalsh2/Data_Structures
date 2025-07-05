/*
 * Stack Operations
 * By: Liam P. Walsh
*/

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

// Allocates node with the given data, and returns address.
stack_node * create_node(int number) {
	// Allocate data for node, setting values to NULL/0.
	stack_node * node = calloc(1, sizeof(node));
	// Set the node's data
	node->number = number;
	return node;
}

// Allocates list with the given head, and returns address.
stack * create_stack(stack_node * head) {
	// Allocate list.
	stack * list = malloc(sizeof(stack));
	// Set the head of the list.
	list->top = head;
	return list;
}

// Append node to front of list. (Replaces head node)
int push_node(stack_node * new_node, stack * list) {
	// Makes sure there is a list and node to append.
	if (!list || !new_node) {
		return 0;
	}
	// If the list is empty, sets the node as head.
	if (!list->top) {
		list->top = new_node;
	}
	// Replaces the current head of the list.
	else {
		new_node->prev = list->top;
		list->top = new_node;
	}
	return 1;
}

// Frees head node of stack.
void pop_node(stack * list) {
	if (!list || !list->top) {
		return;
	}
	// Pop the head
	stack_node *temp = list->top;
	if (list->top->prev) {
		list->top = list->top->prev;
	}
	else {
		list->top = NULL;
	}
	free(temp);
}

// Frees nodes and sets head to NULL.
int empty_stack(stack * list) {
	// Verify there's a list
	if (!list) {
		return 0;
	}
	// Free any nodes attached to the list.
	while (list->top) {
		pop_node(list);
	}
	// Empties list by setting to NULL.
	list = NULL;
	return 1;
}

// Prints the top of the stack.
void peek_node(stack * list) {
	printf("Printing Top: \n");
	if (!list || !list->top) {
		printf("   No stack, head empty\n");
		return;
	}
	printf("   Top's int = %d\n", list->top->number);
}
