//
//  main.c
//  AlgoProg
//
//  Created by COTTEN on 02/10/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char* fst_name;
    char* lst_name;
    char* phone_num;
} Personne;


Personne Personne_init(void);
char* lst_name_get(void);
void Personne_display(Personne pers);
void repertoire_add(Personne pers);
void repertoire_read(void);
void repertoire_search(char* lst_name);
void repertoire_modify(char* lst_name);
void repertoire_menu(void);


int main(int argc, const char * argv[]) {
//    Personne pers1 = Personne_init();
//    Personne pers2 = Personne_init();
//    Personne_display(pers);
//    repertoire_add(pers1);
//    repertoire_add(pers2);
//    repertoire_read();
//    char* lst_name = "cotten";
//    repertoire_modify(lst_name);
//    repertoire_read();
    repertoire_menu();
    return 0;
}

char* lst_name_get(){
    printf("\nlast name: ");
    char* lst_name = (char*) malloc(16 * sizeof(char));
    scanf("%s", lst_name);
    return lst_name;
}


Personne Personne_init(){
    Personne pers;
    printf("first name: ");
    pers.fst_name = (char*) malloc(16 * sizeof(char));
    scanf("%s", pers.fst_name);
    printf("\nlast name: ");
    pers.lst_name = (char*) malloc(16 * sizeof(char));
    scanf("%s", pers.lst_name);
    printf("\nphone number: ");
    pers.phone_num = (char*) malloc(16 * sizeof(char));
    scanf("%s", pers.phone_num);
    printf("\n");
    return pers;
}

void Personne_display(Personne pers){
    printf("first name: %s\n", pers.fst_name);
    printf("last name: %s\n", pers.lst_name);
    printf("phone number: %s\n", pers.phone_num);
}


void repertoire_add(Personne pers){
    FILE* file; // déclaration d’un pointeur de type FILE fichier
    file = fopen("repertoire.bin","ab");
    if (file != NULL){
        unsigned size = sizeof(Personne);
        fwrite(&pers , size, 1, file);
        fclose(file);
    }
}

void repertoire_read(){
    FILE* file; // déclaration d’un pointeur de type FILE fichier
    file = fopen("repertoire.bin","rb");
    if (file != NULL){
        unsigned long k = 1;
        unsigned size = sizeof(Personne);
        Personne pers;
        while (k > 0){
            k = fread(&pers, size, 1, file);
            if (k > 0)
                Personne_display(pers);
        }
        fclose(file);
    }
}

void repertoire_search(char* lst_name){
    FILE* file; // déclaration d’un pointeur de type FILE fichier
    file = fopen("repertoire.bin","rb");
    if (file != NULL){
        unsigned long k = 1;
        int flag = 1;
        unsigned size = sizeof(Personne);
        Personne pers;
        while ((k > 0)&&(flag)){
            k = fread(&pers, size, 1, file);
            if (strcmp(pers.lst_name, lst_name) == 0){
                printf("Phone number: %s\n", pers.phone_num);
                flag = 0;
            }
        }
        fclose(file);
        if (flag)
            printf("Not Found\n");
    }
}

void repertoire_modify(char* lst_name){
    FILE* file; // déclaration d’un pointeur de type FILE fichier
    file = fopen("repertoire.bin","rb");
    if (file != NULL){
        unsigned long k = 1;
        int flag = 1;
        unsigned size = sizeof(Personne);
        Personne pers;
        while ((k > 0)&&(flag)){
            k = fread(&pers, size, 1, file);
            if (strcmp(pers.lst_name, lst_name) == 0){
                flag = 0;
                printf("new phone number: ");
                scanf("%s", pers.phone_num);
                fseek(file, (-size), SEEK_CUR);
                fwrite(&pers, size, 1, file);
            }
        }
        fclose(file);
        if (flag)
            printf("Not Found\n");
    }
}

void repertoire_menu(){
    printf("\n\n1) read repertoire\n2) add a contact\n3) search a contact\n4) modify a contact\n5) quit\nenter your choice: ");
    int n;
    scanf("%d", &n);
    printf("\n\n");
    switch (n) {
        case 1:
            repertoire_read();
            repertoire_menu();
            break;
        case 2:
            repertoire_add(Personne_init());
            repertoire_menu();
            break;
        case 3:
            repertoire_search(lst_name_get());
            repertoire_menu();
            break;
        case 4:
            repertoire_modify(lst_name_get());
            repertoire_menu();
            break;
        case 5:
            remove ("repertoire.bin");
            break;
        default:
            repertoire_menu();
    }
}
