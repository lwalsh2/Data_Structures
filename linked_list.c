#include <stdlib.h>
#include <stdio.h>

// Declare linked node struct
typedef struct linked_node_ {
  // Data of linked list node
  int number;
  // The next node
  struct linked_node_ * node;
} linked_node;

// Declare linked list struct (hold first node)
typedef struct linked_list_ {
  // The first node of the list
  linked_node * head;
} linked_list;

linked_node * create_node(int number) {
	linked_node * node = calloc(1, sizeof(node));
	node->number = number;
	return node;
}

linked_list * create_list(linked_node * head) {
	linked_list * list = malloc(sizeof(linked_list));
	list->head = head;
	return list;
}

int append_front_node(linked_node * new, linked_list * list) {
	if (!list || !new) {
		return 0;
	}
	if (!list->head) {
		list->head = new;
	}
	else {
		new->node = list->head;
		list->head = new;
	}
	return 1;
}

int append_back_node(linked_node * new, linked_list * list) {
	if (!list || !new) {
		return 0;
	}
	if (!list->head) {
		list->head = new;
	}
	else {
		linked_node *node = list->head;
		while (node) {
			if (!node->node) {
				node->node = new;
				break;
			}
		}
	}
	return 0;
}

void free_node(linked_node * node) {
	if (!node) {
		return;
	}
	if (node->node) {
		free_node(node->node);
	}
	free(node);
}

int empty_list(linked_list * list) {
	if (!list) {
		return 0;
	}
	if (list->head) {
		free_node(list->head);
	}
	list->head = NULL;
	return 1;
}

int search_and_destroy_node(linked_list * list, int key) {
	if (!list || !list->head) {
		return 0;
	}
	linked_node *node = list->head;
	linked_node *temp = NULL;
	while (node->node) {
		if (node->node->number == key) {
			temp = node->node;
			node->node = node->node->node;
			free(temp);
			return 1;
		}
		node = node->node;
	}
	if (list->head->number == key) {
		temp = list->head;
		list->head = list->head->node;
		free(temp);
	}
	return 1;
}


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

int main()
{
  printf("Creating Linked list:\n");
  linked_list * list = calloc(1, sizeof(linked_list));
	list->head = create_node(1);
  print_list(list);
	append_back_node(create_node(2), list);
  print_list(list);
	append_front_node(create_node(3), list);
  print_list(list);

	printf("Removing middle node:\n");
	search_and_destroy_node(list, 1);
	print_list(list);

	printf("Deleting Linked list:\n");
	empty_list(list);
	print_list(list);
	free(list);
  return 0;
}
