#include <stdio.h>
#include <stdlib.h>


typedef struct Composante{
  int index;
  int value;
  struct Composante *next;
}Composante;

typedef struct Vecteur{
  Composante *head;
  int size;
}Vecteur;


void initVecteur(Vecteur *vect, int size);
Composante *findComposante(Vecteur *vect, int index);
Composante *createComposante(int index, int value);
void addComposante(Vecteur *vect, Composante *composante);
void set1Vecteur(Vecteur *vect, int size, int value);
void setVecteur(Vecteur *vect, int size, int value);
int getValeur(Vecteur *vect, int i);
void afficherVecteur(Vecteur *vect);
void afficherComposante(Composante *composante);
void resetVecteur(Vecteur *vect);



int main(){
  Vecteur *vect;
  vect = (Vecteur *)malloc(sizeof(Vecteur));
  initVecteur(vect, 100);
  afficherVecteur(vect);
  setVecteur(vect, 7, 1000);
  setVecteur(vect, 3, 5000);
  afficherVecteur(vect);
  printf("\nvaleur vecteur d'indice %d: %d\n", 3, getValeur(vect, 3));
  resetVecteur(vect);
  afficherVecteur(vect);
  return 0;
}


void initVecteur(Vecteur *vect, int size){
  vect->head = NULL;
  vect->size = size;
}


void addComposante(Vecteur *vect, Composante *composante){
  composante->next = vect->head;
  vect->head = composante;
}


Composante *findComposante(Vecteur *vect, int index){
  Composante *current = vect->head;
  while ((current != NULL) && (current->index != index))
    current = current->next;
  return current;
}


Composante *createComposante(int index, int value){
  Composante *new_composante ;
  new_composante = (Composante*) malloc(sizeof(Composante));
  new_composante->value = value;
  new_composante->index = index;
  new_composante->next = NULL;
  return new_composante;
}


void setVecteur1(Vecteur *vect, int index, int value){
  Composante *composante = findComposante(vect, value);
  if (composante == NULL)
    addComposante(vect, createComposante(index, value));
  else
    composante->value = value;
}


int getValeur(Vecteur *vect, int i){
  if (i < vect->size)
    return findComposante(vect, i)->value;
  else
    printf("wrong value i");
    return -1;
}


void afficherComposante(Composante *composante){
  printf("\nindex: %d\nvalue: %d\n", composante->index, composante->value);
}


void afficherVecteur(Vecteur *vect){
  Composante *current = vect->head;
  while (current!=NULL){
    afficherComposante(current);
    current = current->next;
  }
}


void resetVecteur(Vecteur *vect){
  initVecteur(vect, vect->size);
}

void setVecteur(Vecteur *vect, int index, int value){
  Composante *prec;
  Composante *current = vect->head;
  prec = current;
  while ((current != NULL) && (current->index < index)){
    prec = current;
    current = current->next;
  }
  Composante *new_composante = createComposante(index, value);
  if (prec == NULL)
    vect->head = new_composante;
  else{
    new_composante->next = prec->next;
    prec->next = new_composante;
  }
}
