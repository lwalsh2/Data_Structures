/*
 * Fibonacci via Array Cache
 * By: Liam P. Walsh
*/

#include <stdlib.h>
#include <stdio.h>


// Array cache
unsigned int array[100] = {0};

unsigned int fibonacci(unsigned int i) {
  // Determine if number is too big for array.
  if (i > 99) {
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
    array[i] = fibonacci(i-1) + fibonacci(i-2);
  }
  return array[i];
}

int main(void)
{
  printf("Fib %u: %u\n", 5, fibonacci(5));
  printf("Fib %u: %u\n", 7, fibonacci(7));
  printf("Fib %u: %u\n", 5, fibonacci(5));
  printf("Fib %u: %u\n", 99, fibonacci(99));
  printf("Fib %u: %u\n", 97, fibonacci(97));
  return 0;
}
