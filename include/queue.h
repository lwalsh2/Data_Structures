/*
 * Queue Operations
 * By: Liam P. Walsh
*/

#include <stdlib.h>
#include <stdio.h>

// Declares queue node struct.
typedef struct queue_node_ {
  // Data of queue node
  int number;
  // The next node added to queue
  struct queue_node_ * next;
} queue_node;

// Declares queue struct. (holds last node)
typedef struct queue_ {
  // The first and last node of the list
  queue_node * front;
  queue_node * back;
} queue;

// Allocates node with the given data, and returns address.
queue_node * create_node(int number);

// Allocates list with the given head, and returns address.
queue * create_queue(queue_node * head);

// Append node to front of list. (Replaces head node)
int push_node(queue_node * new_node, queue * list);

// Frees head node of queue.
void pull_node(queue * list);

// Frees nodes and sets head to NULL.
int empty_queue(queue * list);

// Prints the front of the queue.
void peek_node(queue * list);
