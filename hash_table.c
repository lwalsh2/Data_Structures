/*
 * Hash Table Operations
 * By: Liam P. Walsh
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARRAY_SIZE 100

// Takes data and return hash.
int hash_data(int number) {
   return number % ARRAY_SIZE;
}

// Adds data to hash table.
int hash_insert(int hash_table[], int number) {
  // Verify hash table exists.
  if (!hash_table)
  {
      return -1;
  }
  // Define the hash key.
  int hash_key = hash_data(number);
  // Verify the key isn't taken
  if (hash_table[hash_key])
  {
    return 1;
  }
  // Set the key on the array to the data.
  hash_table[hash_key] = number;

  return 0;
}

// Print all used keys in the table.
void hash_print(int hash_table[])
{
  if (hash_table)
  {
    printf("Printing Hash Table: \n");
    for(int i = 0; i < ARRAY_SIZE; ++i)
    {
      if(hash_table[i])
      {
        printf("Hash: %d, Value: %d\n", i, hash_table[i]);
      }
    }
    printf("End of Hash.\n");
  }
  else
  {
    printf("No hash to print.\n");
  }
}

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
