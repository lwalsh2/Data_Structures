/*
 * Max Heap Operations
 * By: Liam P. Walsh
 * heap uses AVL method (Balances after append and remove)
*/

#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

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
