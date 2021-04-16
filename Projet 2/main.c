#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define POWER_FILE "Data/power.csv"
#define EQUIPMENT_FILE "house_config.txt"
#define MONTHLY_DATA "Projet 2/Data/Monthlydata_43.455_5.471_SA_2016_2016.csv"
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
}HashTable;

typedef struct _equipment{
  char word[MAX_WORD_LENGHT];
  unsigned int number;
  unsigned int hours_per_week;
  struct _equipment *next;
}Equipment;

typedef struct{
  unsigned int house_surface;
  unsigned int exploitable_surface;
  Equipment *head;
}HouseConfig;

typedef struct {
  unsigned int mean_consumption;
  unsigned int installation_cost;
  unsigned int r_o_n_duration; /* duration of return on investment*/
}Result;


void menu(HashTable* hash_power, HouseConfig* house_config);
void menu_house_config(HouseConfig* house_config);

void initialize_hash_table(HashTable* hash_tab);
void load_hash_table(HashTable* hash_tab);
void insert_element_to_hash_table(HashTable* hash_tab, Element* element);
unsigned long get_hash_value(char *string);
void print_hash_table_characteristics(HashTable* hash_tab);

Equipment* init_equipment(void);
void get_word(char* word);
void add_equipment(HouseConfig* house_config, Equipment* equipment);
void supress_element(char* word, HouseConfig *house_config);
void supress_equipment(HouseConfig *house_config);
void load_house_config(HouseConfig* house_config);
void disp_equipment(Equipment *equipment);
void disp_house_config(HouseConfig* house_config);
void save_house_config(HouseConfig* HouseConfig);

void compute(HashTable* hash_power, HouseConfig* house_config);
unsigned int calc_mean_consumption(HashTable* hash_power, HouseConfig* house_config);



int main(){
	HashTable hash_power;
	initialize_hash_table(&hash_power);
  load_hash_table(&hash_power);
  print_hash_table_characteristics(&hash_power);
  HouseConfig house_config;
  menu(&hash_power, &house_config);
	return 0;
}


void menu(HashTable* hash_power, HouseConfig* house_config){
  int choice;
  printf("\n***************************** Menu *****************************\n");
  printf("1/configure house\n2/compute\n");
  printf("****************************************************************\nchoice: ");
  scanf("%d", &choice);
  printf("\n\n");
  switch (choice){
    case 1 :
      menu_house_config(house_config);
      menu(hash_power, house_config);
      break;
    case 2 :
      compute(hash_power, house_config);
      menu(hash_power, house_config);
      break;
    case 3 :
      break;
  }
}


void menu_house_config(HouseConfig* house_config){
  int choice;
  printf("\n********************** House Configurator **********************\n");
  printf("1/load house \n2/add equipment\n3/supress equipment\n4/show equipments\n5/save config\n6/main menu\n");
  printf("****************************************************************\nchoice: ");
  scanf("%d", &choice);
  printf("\n\n");
  switch (choice){
    case 1 :
      load_house_config(house_config);
      menu_house_config(house_config);
      break;
    case 2 :
      add_equipment(house_config, init_equipment());
      printf(">>> Equipment was sucessfully added to the house");
      menu_house_config(house_config);
      break;
    case 3 :
      supress_equipment(house_config);
      menu_house_config(house_config);
      break;
    case 4 :
      disp_house_config(house_config);
      menu_house_config(house_config);
      break;
    case 5 :
      save_house_config(house_config);
      menu_house_config(house_config);
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


void insert_element_to_hash_table(HashTable* hash_tab, Element* element){
	hash_tab->nb_elements++;
	unsigned long	i		= get_hash_value(element->word);
	if (hash_tab->Elements[i] == NULL)
		hash_tab->nb_occupied_entries++;
	element->next = hash_tab->Elements[i];
	hash_tab->Elements[i]	= element;
}


void initialize_hash_table(HashTable *hash_tab){
	hash_tab->size	= HASH_SIZE;
	hash_tab->nb_occupied_entries = 0;
	hash_tab->nb_elements = 0;
	hash_tab->Elements = (Element **) malloc(hash_tab->size * sizeof(Element*));
	for (unsigned int i = 0; i < hash_tab->size; i++)
		hash_tab->Elements[i] = NULL;
}


void load_hash_table(HashTable *hash_tab){
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


void print_hash_table_characteristics(HashTable* hash_tab){
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
  unsigned int hours_per_week;
  printf("\nNumber of hours of use per week: ");
  scanf("%u", &hours_per_week);
  printf("\n");
  Equipment *equipment = (Equipment *) malloc(sizeof(Equipment));
  equipment->number = number;
  strcpy(equipment->word, word);
  equipment->hours_per_week = hours_per_week;
  return equipment;
}


void add_equipment(HouseConfig* house_config, Equipment* equipment){
  equipment->next = house_config->head;
  house_config->head = equipment;
}


void get_word(char* word){
  printf("Enter the name of the equipment to supress: ");
  scanf("%s", word);
}


void supress_element(char* word, HouseConfig *house_config){
  Equipment *current = house_config->head;
  Equipment *prec = NULL;
  while (current != NULL && strcmp(current->word, word) != 0){
    prec = current;
    current = current->next;
  }
  if (current == NULL)
    printf(">>> wrong equipment's name\n");
  else{
    if (prec == NULL)
      house_config->head = current->next;
    else
      prec->next = current->next;
    printf(">>> %s was successfully removed from the house\n", word);
  }
}

void supress_equipment(HouseConfig *house_config){
  char word[MAX_WORD_LENGHT];
  get_word(word);
  supress_element(word, house_config);
}


void load_house_config(HouseConfig* house_config){
  FILE* file;
  file = fopen(EQUIPMENT_FILE, "r");
  if (file != NULL){
    unsigned int number;
    char word[MAX_WORD_LENGHT];
    unsigned int hours_per_week;
    while (fscanf(file, "%s %u %u", word, &number, &hours_per_week) > 0){
      if (strcmp(word, "house_surface") == 0)
        house_config->house_surface = number;
      else if (strcmp(word, "exploitable_surface") == 0)
        house_config->exploitable_surface = number;
      else{
        Equipment *equipment = (Equipment *) malloc(sizeof(Equipment));
        equipment->number = number;
        strcpy(equipment->word, word);
        equipment->hours_per_week = hours_per_week;
        add_equipment(house_config, equipment);
      }
    }
    printf(">>> house loaded\n");
  }
  else
    printf(">>> empty house_config.txt file\n");
  fclose(file);
}

void save_house_config(HouseConfig* house_config){
  FILE* file;
  file = fopen(EQUIPMENT_FILE, "w");
  fprintf(file, "house_surface %u\n", house_config->house_surface);
  fprintf(file, "exploitable_surface %u\n", house_config->exploitable_surface);
  Equipment *current;
  current = house_config->head;
  while (current != NULL){
    fprintf(file, "%s %u %u\n", current->word, current->number, current->hours_per_week);
    current = current->next;
  }
  printf(">>> house configuration saved in \"house_config.txt\"\n");
}

void disp_equipment(Equipment *equipment){
  printf("equipment: %s, number of units: %u, hours of use per week: %u\n", equipment->word, equipment->number, equipment->hours_per_week);
}

void disp_house_config(HouseConfig* house_config){
  Equipment *current = house_config->head;
  printf("****************** House's configuration **************************\n");
  printf("House's surface: %u\n", house_config->house_surface);
  printf("House's exploitable surface: %u\n", house_config->exploitable_surface);
  printf(">>> Equipments:\n");
  if (current == NULL)
    printf("No equipment to show\n");
  else{
    while ((current != NULL)){
      disp_equipment(current);
      current = current->next;
    }
  }
  printf("****************************************************************\n");
}




void compute(HashTable* hash_power, HouseConfig* house_config){
  Result* result = (Result*) malloc(sizeof(Result));
  result->mean_consumption = calc_mean_consumption(hash_power, house_config);
  printf("mean consumption: %u\n", result->mean_consumption);
  FILE* file;
  file = fopen("Data/data.txt", "r");
  if (file != NULL){
    char type[MAX_WORD_LENGHT];
    unsigned int solar_panel_cost;
    fscanf(file, "%s %u", type, &solar_panel_cost);
    unsigned int peak_power;
    fscanf(file, "%s %u", type, &peak_power);
  }
  fclose(file);
}


unsigned int calc_mean_consumption(HashTable* hash_power, HouseConfig* house_config){
  Equipment* current = house_config->head;
  unsigned int result = 0;
  unsigned int intermediate;
  int power;
  while (current != NULL){
    power = hash_power->Elements[get_hash_value(current->word)]->power;
    intermediate = power*(current->number)*(current->hours_per_week)*52;
    if (strcmp(current->word, "chauffage") == 0)
      result += (intermediate)*(house_config->house_surface);
    else
      result += intermediate;
    current = current->next;
  }
  return result;
}
