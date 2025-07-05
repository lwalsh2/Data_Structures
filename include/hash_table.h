/*
 * Hash Table Operations
 * By: Liam P. Walsh
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARRAY_SIZE 100

// Takes data and return hash.
int hash_data(int number);

// Adds data to hash table.
int hash_insert(int hash_table[], int number);

// Print all used keys in the table.
void hash_print(int hash_table[]);
