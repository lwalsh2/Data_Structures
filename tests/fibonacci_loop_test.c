/*
 * Fibonacci via loop
 * By: Liam P. Walsh
 * Uses a For Loop with the formula as variables.
*/

#include <stdlib.h>
#include <stdio.h>
#include "fibonacci_loop.h"

int main(int argc, char *argv[]) {
  printf("Fib %u: %u\n", 1, fibonacci(0));
  printf("Fib %u: %u\n", 1, fibonacci(1));
  printf("Fib %u: %u\n", 2, fibonacci(2));
  printf("Fib %u: %u\n", 5, fibonacci(5));
  printf("Fib %u: %u\n", 15, fibonacci(15));
  printf("Fib %u: %u\n", 9, fibonacci(9));
  return 0;
}
