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