/*
 * Fibonacci via Recursive Function.
 * By: Liam P. Walsh
*/

#include <stdlib.h>
#include <stdio.h>
#include "fibonacci_rec.h"

int main(void)
{
  printf("Fib %d: %u\n", 5, fibonacci(1));
  printf("Fib %d: %u\n", 5, fibonacci(2));
  printf("Fib %d: %u\n", 5, fibonacci(5));
  printf("Fib %d: %u\n", 5, fibonacci(7));
  printf("Fib %d: %u\n", 5, fibonacci(15));
  return 0;
}
