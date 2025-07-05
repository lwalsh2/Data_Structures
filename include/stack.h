/*
 * Stack Operations
 * By: Liam P. Walsh
*/

#include <stdlib.h>
#include <stdio.h>

// Declares stack node struct.
typedef struct stack_node_ {
  // Data of stack node
  int number;
  // The last node added to stack
  struct stack_node_ * prev;
} stack_node;

// Declares stack struct. (holds last node)
typedef struct stack_ {
  // The first node of the list
  stack_node * top;
} stack;

// Allocates node with the given data, and returns address.
stack_node * create_node(int number);

// Allocates list with the given head, and returns address.
stack * create_stack(stack_node * head);

// Append node to front of list. (Replaces head node)
int push_node(stack_node * new_node, stack * list);

// Frees head node of stack.
void pop_node(stack * list);

// Frees nodes and sets head to NULL.
int empty_stack(stack * list);

// Prints the top of the stack.
void peek_node(stack * list);
