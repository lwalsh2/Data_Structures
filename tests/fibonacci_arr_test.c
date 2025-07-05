/*
 * Fibonacci via Array Cache
 * By: Liam P. Walsh
*/

#include <stdlib.h>
#include <stdio.h>
#include "fibonacci_arr.h"

int main(void)
{
  // Array cache
  unsigned int array[ARRAY_SIZE] = {0};
  printf("Fib %u: %u\n", 5, fibonacci(5, array));
  printf("Fib %u: %u\n", 7, fibonacci(7, array));
  printf("Fib %u: %u\n", 5, fibonacci(5, array));
  printf("Fib %u: %u\n", 43, fibonacci(43, array));
  printf("Fib %u: %u\n", 40, fibonacci(44, array));
  return 0;
}
