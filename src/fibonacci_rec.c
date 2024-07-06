/*
 * Fibonacci via Recursive Function.
 * By: Liam P. Walsh
*/

#include <stdlib.h>
#include <stdio.h>

unsigned int fibonacci(unsigned int i) {
  if (i < 2) {
    return 1;
  }
  return fibonacci(i-1) + fibonacci(i-2);
}

int main(void)
{
  printf("Fib %d: %u\n", 5, fibonacci(1));
  printf("Fib %d: %u\n", 5, fibonacci(2));
  printf("Fib %d: %u\n", 5, fibonacci(5));
  printf("Fib %d: %u\n", 5, fibonacci(7));
  printf("Fib %d: %u\n", 5, fibonacci(15));
  return 0;
}
