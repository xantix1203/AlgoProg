#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define POWER_FILE "power.txt"
#define MAX_WORD_LENGHT	28		/* Maximum word length */
#define HASH_SIZE 7	/* Prime number */
#define BASE 128



typedef struct _element{
  char word[MAX_WORD_LENGHT];
  unsigned int power;
  struct _element *next;
}Element;

typedef struct _hash_table {
  unsigned int size;
  unsigned int nb_occupied_entries;
  unsigned int nb_elements;
  Element** Elements;
} hash_table;



void initialize_hash_table(hash_table* hash_tab);
void load_hash_table(hash_table *hash_tab);
void insert_element_to_hash_table(hash_table* hash_tab, Element* element);
unsigned long get_hash_value(char *string);
void printhash_tableCharacteristics(hash_table* hash_tab) ;



int main()
{
	hash_table hash_power;
	initialize_hash_table(&hash_power);
  load_hash_table(&hash_power);
  printhash_tableCharacteristics(&hash_power);
	return 0;
}


unsigned long get_hash_value(char *string){
	unsigned long	hash_value = 0;
	int	i = 0;
	while ((*string) != '\0')
	{
		hash_value += hash_value % HASH_SIZE + ((*string) * (int) pow (BASE, i) )% HASH_SIZE;
		i++;
		string++;
	}
	return hash_value % HASH_SIZE;
}


void insert_element_to_hash_table(hash_table* hash_tab, Element* element){
	hash_tab->nb_elements++;
	unsigned long	i		= get_hash_value(element->word);
	if (hash_tab->Elements[i] == NULL)
		hash_tab->nb_occupied_entries++;
	element->next = hash_tab->Elements[i];
	hash_tab->Elements[i]	= element;
}


void initialize_hash_table(hash_table *hash_tab){
	hash_tab->size	= HASH_SIZE;
	hash_tab->nb_occupied_entries = 0;
	hash_tab->nb_elements = 0;
	hash_tab->Elements = (Element **) malloc(hash_tab->size * sizeof(Element*));
	for (unsigned int i = 0; i < hash_tab->size; i++)
		hash_tab->Elements[i] = NULL;
}


void load_hash_table(hash_table *hash_tab){
  FILE* file;
  file = fopen(POWER_FILE, "r");
  if (file!=NULL){
    Element* element	= (Element*) malloc(sizeof(Element));
    unsigned int power;
    while (fscanf(file, "%s %u", element->word, &power) > 0){
      element->power = power;
      insert_element_to_hash_table(hash_tab, element);
    }
  }
  else
    printf("empty file\n");
}

void printhash_tableCharacteristics(hash_table* hash_tab)
{
	/* A loadFactor = 0.75 offers a good tradeoff between time and space cost. */

	float loadFactor =  1.0*hash_tab->nb_occupied_entries/hash_tab->size;
	printf("************** Hash Table Characteristics **********************\n");
	printf("Number of buckets: %u \n", hash_tab->size);
	printf("Load Factor: %.2f \n", loadFactor);
	printf("Total number of elements: %u \n", hash_tab->nb_elements);
	printf("****************************************************************\n");
}
