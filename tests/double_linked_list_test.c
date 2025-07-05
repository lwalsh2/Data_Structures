/*
 * Double Linked List Operations
 * Circular Linked
 * By: Liam P. Walsh
*/

#include <stdlib.h>
#include <stdio.h>
#include "double_linked_list.h"

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
