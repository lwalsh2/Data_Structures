/*
 * Fibonacci via Recursive Function.
 * By: Liam P. Walsh
*/

#include <stdlib.h>
#include <stdio.h>
#include "fibonacci_rec.h"

unsigned int fibonacci(unsigned int i) {
  if (i < 2) {
    return 1;
  }
  return fibonacci(i-1) + fibonacci(i-2);
}
