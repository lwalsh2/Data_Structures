/*
 * Fibonacci via loop
 * By: Liam P. Walsh
 * Uses a For Loop with the formula as variables.
*/

#include <stdlib.h>
#include <stdio.h>
#include "fibonacci_loop.h"

// Uses three variables to iterate with instead of recursion.
// Follows the formula: Fib(n) = Fib(n-2) + Fib(n-1)
unsigned int fibonacci(unsigned int i) {
  // fib(n-2)
  unsigned int n_minus_2 = 0;
  // fib(n-1)
  unsigned int n_minus_1 = 1;
  // fib(n)
  unsigned int sum = n_minus_1;

  // Iterate if the given number is 2 or greater.
  // Builds the Fib equation backwards.
  for(unsigned int count = 2; count <= i; ++count)
  {
    // Fib(n) = Fib(n-2) + Fib(n-1)
    sum = n_minus_2 + n_minus_1;
    // Update Fib(n-2) with previous Fib(n-1)
    n_minus_2 = n_minus_1;
    // Update Fib(n-1) with previous Fib(n)
    n_minus_1 = sum;
  }

  // Return sum unless given value was 0.
  return i > 0 ? sum : n_minus_2;
}
