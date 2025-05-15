#include "../include/abrBinaire.h"
#include "../include/pile.h"
#include "stdio.h"
#include "stdlib.h"
#include <stdio.h>
#include <stdbool.h>


//question 1

void fixerCle(Abr* abr, int a){


	abr->x->id = a;
	abr->x->data = a;


}

void ajouterFeuillesPartout(Abr* abr){
	
	if(abr->g != NULL){

		ajouterFeuillesPartout(abr->g);
	}
	if(abr->d != NULL){
		ajouterFeuillesPartout(abr->d);

	}
		
	if(abr->g == NULL){
		abr->g = creerAbr(creerNoeud(0,0));
	}
	if(abr->d == NULL){
		abr->d = creerAbr(creerNoeud(0,0));
	}

}



void algoVersAbreBalise(Abr* abr, Pile* p){
	

	if(abr->x->id == 0){

		fixerCle(abr, sommet(p));
		printf("ok\n");
		depiler(p);
	}
	else{
		empiler(p, abr->x->id);
		algoVersAbreBalise(abr->g,p);
		algoVersAbreBalise(abr->d,p);
	}
	
}

void versAbreBalise(Abr* T){

	Pile* p = malloc(sizeof(Pile));
	if (!p) {
		fprintf(stderr, "Erreur malloc\n");
		exit(EXIT_FAILURE);
	}
	
	initPile(p);
	ajouterFeuillesPartout(T);
	algoVersAbreBalise(T,p);

}

//FIN PARTIE TP4 LEON


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


