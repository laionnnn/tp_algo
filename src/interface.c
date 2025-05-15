#include "../include/abrBalises.h"
#include "../include/abrBinaire.h"
#include "../include/pile.h"
#include "stdio.h"
#include "stdlib.h"





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