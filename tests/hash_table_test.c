/*
 * Hash Table Operations
 * By: Liam P. Walsh
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash_table.h"

int main() {
  // Define the hash table, and set values to 0.
  int hash_table[ARRAY_SIZE] = {0};

  // Add to hash table
  hash_insert(hash_table, 5);
  hash_insert(hash_table, 123);
  hash_insert(hash_table, 28);
  hash_insert(hash_table, 486);

  // Print hash table
  hash_print(hash_table);

  return 0;
}
