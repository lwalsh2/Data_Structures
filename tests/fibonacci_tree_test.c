/*
 * Fibonacci via Tree Cache
 * By: Liam P. Walsh
 * Uses Binary AVL tree structure for cache.
*/

#include <stdlib.h>
#include <stdio.h>
#include "fibonacci_tree.h"

int main(void)
{
  tree * list = create_list();
  printf("Fib %u: %d\n", 1, fibonacci(list, 1));
  printf("Fib %u: %d\n", 2, fibonacci(list, 2));
  printf("Fib %u: %d\n", 5, fibonacci(list, 5));
  printf("Fib %u: %d\n", 15, fibonacci(list, 15));
  printf("Fib %u: %d\n", 9, fibonacci(list, 9));

  // Show the cache, and clear it.
  print_tree(list);
  empty_list(list);
  print_tree(list);
  return 0;
}
