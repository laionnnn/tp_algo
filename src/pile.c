#include "../include/abrBinaire.h"
#include "../include/pile.h"
#include "stdio.h"
#include "stdlib.h"
#include <stdio.h>
#include <stdbool.h>



// Initialisation
void initPile(Pile* p) {
    p->sommet = NULL;
}

// Vérifie si la pile est vide
bool estVide(Pile* p) {
    return p->sommet == NULL;
}

// Empile un élément
void empiler(Pile* p, int val) {
    NoeudP* nouveau = malloc(sizeof(NoeudP));
    if (!nouveau) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    nouveau->valeur = val;
    nouveau->suivant = p->sommet;
    p->sommet = nouveau;
}

// Dépile un élément
int depiler(Pile* p) {
    if (estVide(p)) {
        //fprintf(stderr, "Erreur : pile vide\n");
        //exit(EXIT_FAILURE);
		return 0;
    }
    NoeudP* temp = p->sommet;
    int val = temp->valeur;
    p->sommet = temp->suivant;
    free(temp);
    return val;
}

// Regarde le sommet sans dépiler
int sommet(Pile* p) {
    if (estVide(p)) {
        //fprintf(stderr, "Erreur : pile vide\n");
        //exit(EXIT_FAILURE);
		return 0;
    }
    return p->sommet->valeur;
}

// Libère toute la pile
void libererPile(Pile* p) {
    while (!estVide(p)) {
        depiler(p);
    }
}