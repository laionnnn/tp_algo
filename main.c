#include "stdio.h"
#include "stdlib.h"
#include <stdio.h>
#include <stdbool.h>


typedef struct {
	int id;
	int data;		//unused
} Noeud;

typedef struct _Abr{
	Noeud* x;
	int hauteur;
	struct _Abr* pere;
	struct _Abr* g;
	struct _Abr* d;
} Abr;

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
	if ((T->g == T->d) && (T->g == NULL)) {	
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


// l’export de votre arbre au format .dot afin de le visualiser (si besoin !)
int ecritureRec(Abr* T, FILE* pF)
{
	if ((T->g == T->d) && (T->g == NULL)) {	
		//fprintf(pF, "[color=lightblue]"); ne marche pas ici
		return EXIT_SUCCESS;
	}
	else {
		fprintf(pF, "\t%d", T->x->id);
		if ((T->g) && (T->d)) {
			fprintf(pF, "->{%d, %d};\n", T->g->x->id, T->d->x->id);
			fputc('\n', pF);
			if (T->g->g == T->g->d && T->g->g == NULL) fprintf(pF, "%d %s;\n", T->g->x->id, "[style=filled, fillcolor=lightblue]");
			if (T->d->g == T->d->d && T->d->g == NULL) fprintf(pF, "%d %s;\n", T->d->x->id, "[style=filled, fillcolor=lightblue]");
			ecritureRec(T->g, pF);
			ecritureRec(T->d, pF);
		}
		else if (T->g) {
			fprintf(pF, "->%d;\n", T->g->x->id);
			fprintf(pF, "\ti%d [style=invis];\n", T->x->id);
			fprintf(pF, "\t%d", T->x->id);
			fprintf(pF, "->i%d [style=invis, weight=2];\n", T->x->id);
			if (T->g->g == T->g->d && T->g->g == NULL) fprintf(pF, "%d %s;\n", T->g->x->id, "[style=filled, fillcolor=lightblue]");
			fputc('\n', pF);
			ecritureRec(T->g, pF);
		}
		else if (T->d) {
			fprintf(pF, "->i%d [style=invis, weight=2];\n", T->x->id);
			fprintf(pF, "\ti%d [style=invis];\n", T->x->id);
			fprintf(pF, "\t%d", T->x->id);
			fprintf(pF, "->%d;\n", T->d->x->id);
			if (T->d->g == T->d->d && T->d->g == NULL) fprintf(pF, "%d %s;\n", T->d->x->id, "[style=filled, fillcolor=lightblue]");
			fputc('\n', pF);
			ecritureRec(T->d, pF);
		}

	}
	return EXIT_SUCCESS;
}

int exportDotGraph(Abr* T, char* name) {
	FILE* pF;
	Abr* LecteurAbr = T;
	if ((pF = fopen(name, "w")) != NULL)  {

		fprintf(pF, "digraph %d {\n\tgraph [ordering=\"out\"];\n\n", LecteurAbr->x->id);

		ecritureRec(T, pF);
		
		fputc('}', pF);
		fclose(pF);
	}
	return EXIT_SUCCESS;
}

//PARTIE TP4 LEON

//gestion pile

// Définition d'un élément de pile
typedef struct NoeudP {
    int valeur;
    struct NoeudP* suivant;
} NoeudP;

// La pile elle-même (pointeur vers le sommet)
typedef struct {
    NoeudP* sommet;
} Pile;

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
        fprintf(stderr, "Erreur : pile vide\n");
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
        fprintf(stderr, "Erreur : pile vide\n");
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


int main()
{
	Noeud* n1 = creerNoeud(1, 0);
	Noeud* n2 = creerNoeud(2, 0);
	Noeud* n3 = creerNoeud(3, 0);
	Noeud* n4 = creerNoeud(4, 0);
	Noeud* n5 = creerNoeud(5, 0);
	Noeud* n10 = creerNoeud(10, 0);
	Noeud* n7 = creerNoeud(7, 0);
	Noeud* n11 = creerNoeud(11, 0);
	Noeud* n6 = creerNoeud(6, 0);
	
	Abr* T = creerAbr(n4);
	
	insererNoeud(n1, T);
	insererNoeud(n2, T);
	insererNoeud(n3, T);
	insererNoeud(n5, T);
	insererNoeud(n10, T);
	insererNoeud(n7, T);
	insererNoeud(n11, T);
	insererNoeud(n6, T);

	Pile* p = malloc(sizeof(Pile));
	if (!p) {
		fprintf(stderr, "Erreur malloc\n");
		exit(EXIT_FAILURE);
	}

	initPile(p);
	printf("okkkkkkkk\n");
	ajouterFeuillesPartout(T);
	

	
	versAbreBalise(T,p);
	printf("okkkkkkkk2\n");
	

	//parcoursInfixe(T);
	//printf("\nFacteur = %d\n",facteurDesequilibre(T));
	exportDotGraph(T, "test.dot");
	supprimerAbr(T);
	return EXIT_SUCCESS;

	//test leon


}