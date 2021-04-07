#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define POWER_FILE "power.txt"
#define EQUIPMENT_FILE "house_config.txt"
#define MAX_WORD_LENGHT	28		/* Maximum word length */
#define HASH_SIZE 7	/* Prime number */
#define BASE 128



typedef struct _element{
  char word[MAX_WORD_LENGHT];
  unsigned int power;
  struct _element *next;
}Element;

typedef struct _hash_table{
  unsigned int size;
  unsigned int nb_occupied_entries;
  unsigned int nb_elements;
  Element** Elements;
} hash_table;

typedef struct _equipment{
  char word[MAX_WORD_LENGHT];
  unsigned int number;
  struct _equipment *next;
}Equipment;

typedef struct{
  Equipment *head;
}EquipmentsList;


void menu(hash_table* hash_power, EquipmentsList* equipments_list);

void initialize_hash_table(hash_table* hash_tab);
void load_hash_table(hash_table* hash_tab);
void insert_element_to_hash_table(hash_table* hash_tab, Element* element);
unsigned long get_hash_value(char *string);
void print_hash_table_characteristics(hash_table* hash_tab);

Equipment* init_equipment(void);
void get_word(char* word);
void add_equipment(EquipmentsList* equipments_list, Equipment* equipment);
void supress_element(char* word, EquipmentsList *equipments_list);
void supress_equipment(EquipmentsList *equipments_list);
void load_house_config(EquipmentsList* equipments_list);
void disp_equipment(Equipment *equipment);
void disp_equipments_list(EquipmentsList* equipments_list);
void save_house_config(EquipmentsList* equipments_list);


int main(){
	hash_table hash_power;
	initialize_hash_table(&hash_power);
  load_hash_table(&hash_power);
  print_hash_table_characteristics(&hash_power);
  EquipmentsList equipments_list;
  equipments_list.head = NULL;
  menu(&hash_power, &equipments_list);
	return 0;
}


void menu(hash_table* hash_power, EquipmentsList* equipments_list){
  int choice;
  printf("\n***************************** menu *****************************\n");
  printf("1/load house \n2/add equipment\n3/supress equipment\n4/show equipments\n5/save config\n");
  printf("****************************************************************\nchoice: ");
  scanf("%d", &choice);
  printf("\n\n");
  switch (choice){
    case 1 :
      load_house_config(equipments_list);
      menu(hash_power, equipments_list);
      break;
    case 2 :
      add_equipment(equipments_list, init_equipment());
      printf(">>> Equipment was sucessfully added to the house");
      menu(hash_power, equipments_list);
      break;
    case 3 :
      supress_equipment(equipments_list);
      menu(hash_power, equipments_list);
      break;
    case 4 :
      disp_equipments_list(equipments_list);
      menu(hash_power, equipments_list);
      break;
    case 5 :
      save_house_config(equipments_list);
      break;
    case 6 :
      break;
  }
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
    unsigned int power;
    char word[MAX_WORD_LENGHT];
    while (fscanf(file, "%s %u", word, &power) > 0){
      Element* element	= (Element *) malloc(sizeof(Element));
      strcpy(element->word, word);
      element->power = power;
      insert_element_to_hash_table(hash_tab, element);
    }
  }
  else
    printf("\nNo power.txt file\n");
  fclose(file);
}


void print_hash_table_characteristics(hash_table* hash_tab){
	/* A loadFactor = 0.75 offers a good tradeoff between time and space cost. */

	float loadFactor =  1.0*hash_tab->nb_occupied_entries/hash_tab->size;
	printf("************** Hash Table Characteristics **********************\n");
	printf("Number of buckets: %u \n", hash_tab->size);
	printf("Load Factor: %.2f \n", loadFactor);
	printf("Total number of elements: %u \n", hash_tab->nb_elements);
	printf("****************************************************************\n");
}


Equipment* init_equipment(){
  char word[MAX_WORD_LENGHT];
  printf("Enter the equipment's name: ");
  scanf("%s", word);
  unsigned int number;
  printf("\nNumber of units in the house: ");
  scanf("%u", &number);
  printf("\n");
  Equipment *equipment = (Equipment *) malloc(sizeof(Equipment));
  equipment->number = number;
  strcpy(equipment->word, word);
  return equipment;
}


void add_equipment(EquipmentsList* equipments_list, Equipment* equipment){
  equipment->next = equipments_list->head;
  equipments_list->head = equipment;
}


void get_word(char* word){
  printf("Enter the name of the equipment to supress: ");
  scanf("%s", word);
}


void supress_element(char* word, EquipmentsList *equipments_list){
  Equipment *current = equipments_list->head;
  Equipment *prec = NULL;
  while (current != NULL && strcmp(current->word, word) != 0){
    prec = current;
    current = current->next;
  }
  if (current == NULL)
    printf(">>> wrong equipment's name\n");
  else{
    if (prec == NULL)
      equipments_list->head = current->next;
    else
      prec->next = current->next;
    printf(">>> %s was successfully removed from the house\n", word);
  }
}

void supress_equipment(EquipmentsList *equipments_list){
  char word[MAX_WORD_LENGHT];
  get_word(word);
  supress_element(word, equipments_list);
}


void load_house_config(EquipmentsList* equipments_list){
  FILE* file;
  file = fopen(EQUIPMENT_FILE, "r");
  if (file != NULL){
    unsigned int number;
    char word[MAX_WORD_LENGHT];
    while (fscanf(file, "%s %u", word, &number) > 0){
      Equipment *equipment = (Equipment *) malloc(sizeof(Equipment));
      equipment->number = number;
      strcpy(equipment->word, word);
      add_equipment(equipments_list, equipment);
    }
    printf(">>> house loaded\n");
  }
  else
    printf(">>>empty house_config.txt file\n");
  fclose(file);
}

void save_house_config(EquipmentsList* equipments_list){
  FILE* file;
  file = fopen(EQUIPMENT_FILE, "w");
  Equipment *current;
  current = equipments_list->head;
  while (current != NULL){
    fprintf(file, "%s %u\n", current->word, current->number);
    current = current->next;
  }
  printf(">>> house configuration saved in \"house_config.txt\"\n");
}

void disp_equipment(Equipment *equipment){
  printf("equipment: %s, number of units: %u\n", equipment->word, equipment->number);
}

void disp_equipments_list(EquipmentsList* equipments_list){
  Equipment *current = equipments_list->head;
  printf("****************** House's equipments **************************\n");
  if (current == NULL)
    printf("Empty configuration\n");
  else{
    while ((current != NULL)){
      disp_equipment(current);
      current = current->next;
    }
  }
  printf("****************************************************************\n");
}
