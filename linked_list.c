#include <stdlib.h>

// Declare linked list struct
typedef struct linked_list_ {
    // Data of linked list node
    int number;
    // The next node
    struct linked_list_* node;
} linked_list;

int main()
{
    // Declare list nodes
    linked_list head;
    linked_list body;
    linked_list tail;

    // Define data for each node
    head.number = 1;
    body.number = 2;
    tail.number = 3;

    // Define the next node
    head.node = &body;
    body.node = &tail;
    tail.node = NULL;

    // Iterate through linked list
    linked_list *node = &head;
    while (node) {
      printf("Current Node's int = %d\n", node->number);
      node = node->node;
    }

    return 0;
}
