/*
 * Fibonacci via Array Cache
 * By: Liam P. Walsh
*/

#include <stdlib.h>
#include <stdio.h>
#define ARRAY_SIZE 45

unsigned int fibonacci(unsigned int i, unsigned int array[]) {
  // Determine if number is too big for array.
  if (i > ARRAY_SIZE) {
    return 0;
  }
  // Check if the array cached the value.
  if (array[i] > 0) {
    return array[i];
  }
  // Set the array's cache and return.
  if (i < 2) {
    array[i] = 1;
  }
  else {
    array[i] = fibonacci(i-1, array) + fibonacci(i-2, array);
  }
  return array[i];
}

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
