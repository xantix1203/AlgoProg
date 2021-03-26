#include "pFile.h"

File Initialiser() 
{
	File filevide;
	filevide.tete = NULL; 
	return filevide;
}

int est_vide(File* pF) 
{
	return (pF->tete == NULL);
}

void enfiler(File *pF, int id_cell) 
{
	cell* pelem = (cell*) malloc(sizeof(cell)); 

	pelem->id = id_cell;
	pelem->suivant = NULL; 
	 
	if (pF->tete == NULL) 
	{
		pF->tete = pF->queue = pelem; 
	}
	else 
	{ 
		pF->queue->suivant = pelem; 
		pF->queue = pelem;
	}	
}

int defiler(File *pF) 
{	
	int id = pF->tete->id;

	cell* ptemp = pF->tete;
	pF->tete = pF->tete->suivant;

	if (pF->tete == NULL) 
		pF->queue = NULL;
	
	free(ptemp);
	return id;
}

void detruire (File *pF)
{
	cell* pelem = pF->tete;

	while (pF->tete != NULL) 
	{
		pelem = pF->tete;
		pF->tete = pelem->suivant;
		free(pelem);
	}
}