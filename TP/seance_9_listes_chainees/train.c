#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH_NAME 20
#define ACCOUNT_FILE_NAME "accounts.txt"

typedef struct Account {
  char name[50];
  float amount;
  struct Account *next;
}Account;

typedef struct{
  Account *head;
}AccountsList;


void menu(AccountsList *accounts_list);
void insert_account(AccountsList *accounts_list, Account *account);
void print_list(AccountsList *accounts_list);
void read_file(AccountsList *accounts_list);
void show_one(AccountsList *accounts_list);


int main(){
  AccountsList accounts_list;
  accounts_list.head = NULL;
  read_file(&accounts_list);
  print_list(&accounts_list);
  menu(&accounts_list);
  return 0;
}


void menu(AccountsList *accounts_list){
  int choice;
  printf("\n1/show all\n2/show one\n3/modify account\n4/add\n5/supress\n6/quit\nenter instruction: ");
  scanf("%d", &choice);
  switch (choice){
    case 1 :
      print_list(accounts_list);
      menu(accounts_list);
      break;
    case 2 :
      show_one(accounts_list);
      menu(accounts_list);
      break;
    case 3 :
      modify
      menu(accounts_list);
      break;
    case 4 :
      menu(accounts_list);
      break;
    case 5 :
      menu(accounts_list);
      break;
    case 6 :
      break;
  }
}


Account *find_account(AccountsList *accounts_list, char name[LENGTH_NAME]){
  Account *current = accounts_list->head;
  while (strcmp(current->name, name) != 0){
    current = current->next;
  }
  return current;
}


void insert_account(AccountsList *accounts_list, Account *account){
  account->next = accounts_list->head;
  accounts_list->head = account;
}


void print_account(Account *account){
    printf("\nname: %s\namount: %f\n", account->name, account->amount);
}


void print_list(AccountsList *accounts_list){
  Account *current = accounts_list->head;
  while (current != NULL){
    print_account(current);
    current = current->next;
  };
}


void read_file(AccountsList *accounts_list){
  FILE *file;
  Account *new_account;
  char name[LENGTH_NAME];
  float amount;
  file = fopen(ACCOUNT_FILE_NAME, "r");
  while (fscanf(file, "%s%f", name, &amount) == 2){
    new_account = (Account *)malloc(sizeof(Account));
    strcpy(new_account->name, name);
    new_account->amount = amount;
    insert_account(accounts_list, new_account);
  }
  fclose(file);
}


void show_one(AccountsList *accounts_list){
  char name[LENGTH_NAME];
  printf("please enter name: ");
  scanf("%s", name);
  print_account(find_account(accounts_list, name));
}
