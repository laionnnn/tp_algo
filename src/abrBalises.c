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

void versAbreBalise(Abr* abr, Pile* p){
	

	if(abr->x->id == 0){

		fixerCle(abr, sommet(p));
		printf("vleur : %d\n", sommet(p));
		depiler(p);
	}
	else{
		empiler(p, abr->x->id);
		versAbreBalise(abr->g,p);
		versAbreBalise(abr->d,p);
	}
	
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
			T->x = (n->id <= ancienneCle->id) ? creerNoeud(n->id, 0) : creerNoeud(ancienneCle->id, 0); 
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

int supprimerFeuilleBalise(int id, Abr* T)
{
	// TODO Mettre les hauteurs à jour
	int h = 0;
	Abr* parcours = NULL;
	if (T == NULL) return EXIT_SUCCESS;
	else {
		if (T->g == NULL && T->d == NULL) {
			if (T->x->id == id) {
			// Si on a atteint la feuille AVEC LE BON ID :
				// On stocke son père
				Abr* pere = T->pere;

				// Son père devient l'autre feuille
				free(T->pere->x);

				// Si le père n'est pas la racine :
					// Le père de son père pointe vers l'autre feuille (= mettre à jour les fils)
				//if (T->pere->pere != NULL) = T->pere->pere... Pas nécessaire avec notre structure ?
				if (T->pere->g->x->id == T->x->id) { // Si on supprime le fils gauche on récupère le fils droit
					T->pere->x = T->pere->d->x;
					free(T->pere->d);
				} else if (T->pere->d->x->id == T->x->id) {
					T->pere->x = T->pere->g->x;
					free(T->pere->g);
				}
				
				// On libère les feuilles
				T->pere->g = NULL;
				T->pere->d = NULL;
				free(T->x);
				free(T);
				T = NULL; // N'est pas suffisant seul car modifie juste la variable locale : on doit faire les NULL au dessus
				
				// La mise à jour de la hauteur après insertion
				/*parcours = T->g;
				while (parcours->pere) {
					h++;
					parcours = parcours->pere;
					if (parcours->hauteur < h) parcours->hauteur = h;
				}*/
			}
			else return EXIT_SUCCESS;
		}
		else {
			if (id <= T->x->id) supprimerFeuilleBalise(id, T->g);
			else supprimerFeuilleBalise(id, T->d);
		}
	}
	return EXIT_SUCCESS;
}