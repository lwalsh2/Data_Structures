/*
 * B Tree Operations
 * By: Liam P. Walsh
*/

#include <stdlib.h>
#include <stdio.h>
#include "b_tree.h"

int main()
{
  printf("Creating Tree:\n");
	tree * list = create_list();
  if (!append_node(create_node(5), list)) {
		printf("Append failed.\n");
	}
  print_tree(list);
	if (!append_node(create_node(2), list)) {
		printf("Append failed.\n");
	}
  print_tree(list);
	if (!append_node(create_node(3), list)) {
		printf("Append failed.\n");
	}
  print_tree(list);
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
  print_tree(list);
  print_small_large_tree(list);
  tree_node * node = search_tree(list, 4);

  if (node) {
    printf("Found node in tree.\n");
    /*
    remove_node(list, node);
    if (!search_tree(list, 4)) {
      printf("Successfully removed node from tree.\n");
    }
    else {
      printf("Didn't remove node from tree.\n");
    }*/
  }
  else {
    printf("Didn't find node in tree.\n");
  }
  printf("Number of levels: %d\n", count_level(list->root));
	printf("Deleting Tree:\n");
	if (!empty_list(list)) {
		printf("Empty List failed.\n");
	}
	print_tree(list);
  print_small_large_tree(list);
	free(list);
  return 0;
}
