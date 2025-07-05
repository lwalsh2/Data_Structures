/*
 * Stack Operations
 * By: Liam P. Walsh
*/

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

int main()
{
  printf("Creating Stack:\n");
	stack * list = create_stack(create_node(3));
  peek_node(list);
	if (!push_node(create_node(1), list)) {
		printf("Push failed.\n");
	}
  peek_node(list);
	if (!push_node(create_node(2), list)) {
		printf("Push failed.\n");
	}
  peek_node(list);
	pop_node(list);
  peek_node(list);
	if (!push_node(create_node(1), list)) {
		printf("Push failed.\n");
	}
  peek_node(list);

	printf("Deleting Stack:\n");
	if (!empty_stack(list)) {
		printf("Empty Stack failed.\n");
	}
	peek_node(list);
	free(list);
  return 0;
}
