#ifndef PILE_H
#define PILE_H

#include "../include/abrBinaire.h"
#include "../include/pile.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

// Définition d'un élément de pile
typedef struct NoeudP {
    int valeur;
    struct NoeudP* suivant;
} NoeudP;

// La pile elle-même (pointeur vers le sommet)
typedef struct {
    NoeudP* sommet;
} Pile;

void initPile(Pile* p);
bool estVide(Pile* p);
void empiler(Pile* p, int val);
int depiler(Pile* p);
int sommet(Pile* p);
void libererPile(Pile* p);

#endif