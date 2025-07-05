/*
 * Queue Operations
 * By: Liam P. Walsh
*/

#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

int main()
{
  printf("Creating queue:\n");
	queue * list = create_queue(create_node(3));
  peek_node(list);
	if (!push_node(create_node(1), list)) {
		printf("Push failed.\n");
	}
  peek_node(list);
	if (!push_node(create_node(2), list)) {
		printf("Push failed.\n");
	}
  peek_node(list);
	pull_node(list);
  peek_node(list);
	if (!push_node(create_node(1), list)) {
		printf("Push failed.\n");
	}
  peek_node(list);

	printf("Deleting queue:\n");
	if (!empty_queue(list)) {
		printf("Empty queue failed.\n");
	}
	peek_node(list);
	free(list);
  return 0;
}
