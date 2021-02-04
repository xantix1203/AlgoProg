#include <stdio.h>
#define NAME_LENGTH 10
#define FILE_NAME

typedef struct {
  char name[NAME_LENGTH];
  int inhabitants;
  struct City *next;
}City;

typedef struct {
  City head;
}Cities_list;

void menu(Cities_list *cities_list);
void read_file(Cities_list *cities_list);


int main(){
  FILE *file;
  file = fopen("FILE_NAME", "r")
  return 0;
}

void menu(Cities_list *cities_list){

}

void read_file(Cities_list *cities_list){
  FILE *file;
  City *city;
  char
  file = fopen(FILE_NAME, "r");
  while(fscanf(file, "%s%d", city->name, city->inhabitants) == 2)
}
