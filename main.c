#include "stdio.h"
#include "stdlib.h"
#include <stdio.h>

typedef struct {
	int id;
	char data;		//unused
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

	//parcoursInfixe(T);
	//printf("\nFacteur = %d\n",facteurDesequilibre(T));
	exportDotGraph(T, "test.dot");
	supprimerAbr(T);
	return EXIT_SUCCESS;
}