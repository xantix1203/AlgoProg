//
//  main.c
//  AlgoProg
//
//  Created by COTTEN on 02/10/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Account {
    char name[50];
    float amount;
}Account;

typedef struct noeud{
    Account account;
    struct noeud *next;
}T_noeud;


T_noeud* liste_chainee(void);
void insert(T_noeud* head, T_noeud* new);
void disp_liste_chainee(T_noeud* head);

int main(int argc, const char * argv[]) {
    T_noeud* head = liste_chainee();
    disp_liste_chainee(head);
    return 0;
}

void insert(T_noeud* head, T_noeud* new)
{
    T_noeud* courant = head;
    while (courant->next != NULL)
    {
        courant = courant->next;
    }
    courant->next = new;
    new->next = NULL;
}

T_noeud* liste_chainee(){
    FILE* accounts;
    accounts = fopen("accounts.txt", "r");
    T_noeud* head = NULL;
    head = (T_noeud*) malloc(sizeof(T_noeud));
//    fscanf(accounts, "%s%f", head->account.name, &head->account.amount);
    char name[50];
    double amount;
    if (accounts != NULL){
        while (fscanf(accounts, "%s %lf", name, &amount) == 2)
        {
            T_noeud* courant = (T_noeud*) malloc(sizeof(T_noeud));
            strcpy(courant->account.name, name);
            courant->account.amount = amount;
            insert(head, courant);
            printf("%s", courant->account.name);
        }
    }
    return head;
}

void disp_liste_chainee(T_noeud* head)
{
    T_noeud* courant = head;
    while (courant != NULL)
    {
        printf("%s : %f\n", courant->account.name, (courant->account).amount);
        courant = courant->next;
    }
}
