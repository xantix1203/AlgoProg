/*********************************************************************************
Example of a C mini-project, which:

- Load the EN dictionary from a file
- Check the existence of a word in the dictionary

Note that:
- Total number of words in the dictionary: 62 040
- Maximum word length: 28

NB: (a+b) mod n = (a mod n + b mod n) mod n  
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_WORD_LENGHT	28		/* Maximum word length */
#define HASH_SIZE		37987	/* Prime number */
#define BASE			128

typedef struct _element
{
	char			word[MAX_WORD_LENGHT];
	struct _element	*next;
} Element;

typedef struct _hashTable
{
	unsigned int	size;
	unsigned int	nbOccupiedEntries;
	unsigned int	nbElements;
	Element			**Elements;
} HashTable;

void menu(HashTable *hashTab);
void loadDictionaryFromFile(HashTable* hashTab, const char* dictionaryFileName);
void insertElementToHashTable(HashTable* hashTab, char* word);
void initializeHashTable(HashTable *hashTab);
bool checkExistenceWordInDictionary(HashTable* hashTab, char * word);
void printHashTableCharacteristics(HashTable* hashTab);

int main()
{
	const char* dictionaryFileName = "en_US_wordlist.txt";

	HashTable hashTab;
	initializeHashTable(&hashTab);
	loadDictionaryFromFile(&hashTab, dictionaryFileName);
	menu(&hashTab);

	return 0;
}

void menu(HashTable *hashTab)
{
	bool quit = false;
	int choice;

	while (!quit)
	{
		printf("\n");
		printf("1  Verify the existence of a word in the dictionary\n");
		printf("2  Print hash table characteristics\n");
		printf("3  Quit\n");
		printf("Choice : ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
		{
			char word[MAX_WORD_LENGHT];
			printf("\nGive the word: ");
			scanf("%s", word);
			if (checkExistenceWordInDictionary(hashTab, word))
				printf("\nThe word \" %s \" exists in the EN dictionary.", word);
			else 
				printf("\nThe word \" %s \" does not exist in the EN dictionary.", word);
			break;
		}
		case 2:
			printHashTableCharacteristics(hashTab);
			break;
		case 3:
			quit = true;
			break;
		}
	}
}

void initializeHashTable(HashTable *hashTab)
{
	hashTab->size				= HASH_SIZE;
	hashTab->nbOccupiedEntries	= 0;
	hashTab->nbElements			= 0;
	hashTab->Elements			= (Element **) malloc(hashTab->size * sizeof(Element*));

	for (unsigned int i = 0; i < hashTab->size; i++)
		hashTab->Elements[i] = NULL;
}

void loadDictionaryFromFile(HashTable* hashTab, const char* dictionaryFileName)
{
	FILE *fp;
	fp = fopen(dictionaryFileName, "r");

	if (fp != NULL)
	{
		char word[MAX_WORD_LENGHT];

		while (fscanf(fp, "%s", word) == 1)
			insertElementToHashTable(hashTab, word);
	}
	else printf("File not found.");
	fclose(fp);
}

unsigned long getHashValue(char *string)
{
	unsigned long	hashValue = 0;
	int				i = 0;
	
	while ((*string) != '\0')
	{
		hashValue += hashValue % HASH_SIZE + ((*string) * (int) pow (BASE, i) )% HASH_SIZE;
		i++;
		string++;
	}
	return hashValue % HASH_SIZE;
}

void insertElementToHashTable(HashTable* hashTab, char* word) 
{
	hashTab->nbElements++;
	unsigned long	i		= getHashValue(word);
	Element*		elem	= (Element*) malloc(sizeof(Element));

	strcpy(elem->word, word);

	if (hashTab->Elements[i] == NULL)
		hashTab->nbOccupiedEntries++;

	elem->next				= hashTab->Elements[i];
	hashTab->Elements[i]	= elem;
}

bool checkExistenceWordInDictionary(HashTable* hashTab, char * word)
{
	unsigned long	hashValue = getHashValue(word);

	Element *elem = hashTab->Elements[hashValue];
	bool		found = 0;

	while (found == 0 && elem != NULL)
	{
		found = (strcmp(word, elem->word) == 0);
		elem = elem->next;
	}

	return found;
}

void printHashTableCharacteristics(HashTable* hashTab) 
{
	/* A loadFactor = 0.75 offers a good tradeoff between time and space cost. */

	float loadFactor =  1.0*hashTab->nbOccupiedEntries/hashTab->size;
	printf("************** Hash Table Characteristics **********************\n");
	printf("Number of buckets: %u \n", hashTab->size);
	printf("Load Factor: %.2f \n", loadFactor);
	printf("Total number of elements: %u \n", hashTab->nbElements);
	printf("***************************************** **********************\n");
}
