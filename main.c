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


// l’export de votre arbre au format .dot afin de le visualiser
int ecritureRec(Abr* T, FILE* pF)
{
	/* Conventions de nommage interne :
		- f<noeud>	: feuille (le f la distingue des parents avec même clé)
		- i<pere>	: noeud invisible permettant de distinguer fils gauche et droit (i.e. feuille externe)
	*/
	
	if ((T->g == NULL && T->d == NULL)) {	
		fprintf(pF, "\tf%d [label = %d, style=filled, fillcolor=lightblue];\n\n", T->x->id, T->x->id);
		return EXIT_SUCCESS;
	}
	else {

		fprintf(pF, "\t%d", T->x->id);

		if ((T->g) && (T->d)) {
			fprintf(pF, "->{%s%d, %s%d};\n", (T->g->g == NULL && T->g->d == NULL)? "f":"", T->g->x->id, (T->d->g == NULL && T->d->d == NULL)? "f":"", T->d->x->id);
			fputc('\n', pF);
			ecritureRec(T->g, pF);
			ecritureRec(T->d, pF);
		} // Les fils invisibles sont dans cet ordre car le graph respecte l’ordre d’écriture des arêtes avec ordering="out" 
		else if (T->g) {
			fprintf(pF, "->%s%d;\n", (T->g->g == NULL && T->g->d == NULL)? "f":"", T->g->x->id);
			fprintf(pF, "\ti%d [style=invis];\n", T->x->id);						// Déclaration du fils invisible	: i<pere> [style=invis]
			fprintf(pF, "\t%d->i%d [style=invis, weight=2];\n", T->x->id, T->x->id);// Ajout du fils invisible			: <pere>->i<pere> [style=invis, weight=2]
			ecritureRec(T->g, pF);
			fputc('\n', pF);
		}
		else if (T->d) {
			fprintf(pF, "->i%d [style=invis, weight=2];\n", T->x->id);				// Ajout du fils invisible			: <pere>->i<pere> [style=invis, weight=2]
			fprintf(pF, "\ti%d [style=invis];\n", T->x->id);						// Déclaration du fils invisible	: i<pere> [style=invis]
			fprintf(pF, "\t%d->%s%d;\n", T->x->id, (T->d->g == NULL && T->d->d == NULL)? "f":"", T->d->x->id);// Nb : On réecrit le père car il a été utilisé pour le fils invisible
			ecritureRec(T->d, pF);
			fputc('\n', pF);
		}

	}
	return EXIT_SUCCESS;
}

int exportDotGraph(Abr* T, char* name) {
	FILE* pF;
	Abr* LecteurAbr = T;
	if ((pF = fopen(name, "w")) != NULL)  {

		fprintf(pF, "digraph %d {\n\tgraph [ordering=\"out\"];\n\tnode [width=0.5];\n", LecteurAbr->x->id);

		ecritureRec(T, pF);
		
		fputc('}', pF);
		fclose(pF);
	}
	return EXIT_SUCCESS;
}


int main()
{
	/*
	Arbre du sujet du TP, ne fonctionne pas bien
	Noeud* n7 = creerNoeud(7, 0);
	Noeud* n10 = creerNoeud(10, 0);
	Noeud* n19 = creerNoeud(19, 0);
	Noeud* n25 = creerNoeud(25, 0);
	Noeud* n30 = creerNoeud(30, 0);
	Noeud* n37 = creerNoeud(37, 0);
	Noeud* n47 = creerNoeud(47, 0);
	Noeud* n59 = creerNoeud(59, 0);
	Noeud* n62 = creerNoeud(62, 0);
	Noeud* n70 = creerNoeud(70, 0);
	Noeud* n80 = creerNoeud(80, 0);
	Noeud* n89 = creerNoeud(89, 0);
	Noeud* n97 = creerNoeud(97, 0);	

	Abr* T = creerAbr(n47);

	insererNoeud(n25, T);
	insererNoeud(n80, T);
	
	insererNoeud(n10, T);
	insererNoeud(n37, T);
	insererNoeud(n62, T);
	insererNoeud(n89, T);
	
	insererFeuilleBalise(n7, T);
	insererFeuilleBalise(n19, T);
	insererFeuilleBalise(n30, T);
	insererFeuilleBalise(n59, T);
	insererFeuilleBalise(n70, T);
	insererFeuilleBalise(n97, T);
	*/
	Noeud* n7 = creerNoeud(7, 0);
	Noeud* n3 = creerNoeud(3, 0);
	Noeud* n9 = creerNoeud(9, 0);
	Noeud* n1 = creerNoeud(1, 0);
	Noeud* n5 = creerNoeud(5, 0);
	Noeud* n6 = creerNoeud(6, 0);

	Abr* T = creerAbr(n7);
	insererNoeud(n3, T);
	insererNoeud(n9, T);
	insererFeuilleBalise(n1, T);
	insererFeuilleBalise(n5, T);	
	insererFeuilleBalise(n6, T);	
	//parcoursInfixe(T);
	//printf("\nFacteur = %d\n",facteurDesequilibre(T));
	exportDotGraph(T, "test.dot");
	system( "dot -Tpng test.dot -o outfile.png" );
	//supprimerAbr(T);
	return EXIT_SUCCESS;
}