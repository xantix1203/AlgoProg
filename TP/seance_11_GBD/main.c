#include <stdio.h>
#define DICTFILENAME "accounts.txt"

typedef struct{
  unsigned int size;
  unsigned int nb_ccupied_entries;
  unsigned int nb_elements;
  Element **elements;
} HashTable;

void initialise_hash_table(HashTable *hash_table);

int main(){
  HashTable hash_table;
  initialise_hash_table(&hash_table);
  return 0;
}

void initialise_hash_table(HashTable *hash_table){
  hash_table
}
