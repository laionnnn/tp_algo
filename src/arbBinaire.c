#include "../include/abrBinaire.h"
#include "stdio.h"
#include "stdlib.h"
#include <stdio.h>
#include <stdbool.h>

// l’insertion d’une nouvelle clé dans l’arbre

Noeud* creerNoeud(int id, char data) 
{
	Noeud* n = (Noeud*)malloc(sizeof(Noeud));
	n->id = id;
	n->data = data;
	return n;
}

Abr* creerAbr(Noeud* n)
{
	Abr* T = (Abr*)malloc(sizeof(Abr));
	T->x = n;
	T->hauteur = 0;
	T->pere = NULL;
	T->g = NULL;
	T->d = NULL;
	return T;
}

int insererNoeud(Noeud* n, Abr* T)
{
	int h = 0;
	Abr* parcours = NULL;
	if (T == NULL) T = creerAbr(n);
	else {
		if (n->id <= T->x->id) {
			if (T->g == NULL) {
				T->g = creerAbr(n);
				T->g->pere = T;
				// la mise à jour de la hauteur après insertion
				parcours = T->g;
				while (parcours->pere) {
					h++;
					parcours = parcours->pere;
					if (parcours->hauteur < h) parcours->hauteur = h;
				}
			}
			else insererNoeud(n, T->g);
		}
		else {
			if (T->d == NULL) {
				T->d = creerAbr(n);
				T->d->pere = T;
				parcours = T->d;
				while (parcours->pere) {
					h++;
					parcours = parcours->pere;
					if (parcours->hauteur < h) parcours->hauteur = h;
				}
			}
			else insererNoeud(n, T->d);
		}
	}
	return EXIT_SUCCESS;
}

int insererFeuilleBalise(Noeud* n, Abr* T)
{
	int h = 0;
	Abr* parcours = NULL;
	if (T == NULL) T = creerAbr(n);
	else {
		if (T->g == NULL && T->d == NULL) {
			Noeud* ancienneCle = T->x;
			T->x = (n->id <= ancienneCle->id) ? creerNoeud(ancienneCle->id, 0) : creerNoeud(n->id, 0); 
			// Le pere contient la plus petite des 2 feuilles;
			// On crée un nouveau noeud SANS DATA : seules les feuilles en contiennent

			// Création des deux feuilles enfants
			T->g = creerAbr((n->id <= ancienneCle->id) ? n : ancienneCle);
			T->d = creerAbr((n->id <= ancienneCle->id) ? ancienneCle : n);

			T->g->pere = T;
			T->d->pere = T;

			// La mise à jour de la hauteur après insertion
			parcours = T->g;
			while (parcours->pere) {
				h++;
				parcours = parcours->pere;
				if (parcours->hauteur < h) parcours->hauteur = h;
			}
		}
		else {
		if (n->id <= T->x->id) insererFeuilleBalise(n, T->g);
		else insererFeuilleBalise(n, T->d);
		}
	}
	return EXIT_SUCCESS;
}

// l’affichage du contenu de l’arbre selon les divers parcours abordés en cours

int parcoursInfixe(Abr* T) 
{
	if (T) 
	{
		parcoursInfixe(T->g);
		printf(" %d ", T->x->id);
		parcoursInfixe(T->d);
	}
	return EXIT_SUCCESS;
}

// la suppression de l’arbre

int supprimerAbr(Abr* T)
{
	free(T->x);
	if ((T->g == NULL && T->d == NULL)) {	
		free(T);
		T = NULL;
	}
	else {
		if (T->g) {
			supprimerAbr(T->g);
		}
		if (T->d) {
			supprimerAbr(T->d);
		}
		free(T);
		T = NULL;
	}
	return EXIT_SUCCESS;
}

// la récupération du facteur de déséquilibre d’un arbre
int facteurDesequilibre(Abr* T)
{
	return abs(T->g->hauteur - T->d->hauteur);
}