#include "../include/abrBalises.h"
#include "../include/abrBinaire.h"
#include "../include/pile.h"
#include "stdio.h"
#include "stdlib.h"


int rechercheIntervallePile(Abr* T, int a, int b, Pile* p, int* taillePile){

    if(T == NULL){

        return EXIT_SUCCESS;
    }
    
    if(T->d == NULL && T->g == NULL){

        if(a<=T->x->id && T->x->id<=b){
            empiler(p,T->x->id);
            (*taillePile)++;

        }
        return EXIT_SUCCESS;
    }

    rechercheIntervallePile(T->g,a,b,p,taillePile);
    rechercheIntervallePile(T->d,a,b,p,taillePile);

    return EXIT_SUCCESS;

}

int rechercheIntervalle(Abr* T, int a, int b, int **R){

    Pile* p = malloc(sizeof(Pile));
	if (!p) {
		fprintf(stderr, "Erreur malloc\n");
		exit(EXIT_FAILURE);
	}
	
	initPile(p);
    int* taillePile = malloc(sizeof(int));
	if (!taillePile) {
		fprintf(stderr, "Erreur malloc\n");
		exit(EXIT_FAILURE);
	}

    *taillePile = 0;

    rechercheIntervallePile(T, a, b, p, taillePile);

    *R = malloc(sizeof(int)*(*taillePile));
	if (!*R) {
		fprintf(stderr, "Erreur malloc\n");
		exit(EXIT_FAILURE);
	}


    FILE* doc;
    doc = fopen("test.dot", "rb+");
    fseek(doc, 0, SEEK_END);
    long tailleDoc = ftell(doc);
    ftruncate(fileno(doc), tailleDoc - 1);
    fseek(doc, -1, SEEK_CUR);


    for(int i = 0; i<(*taillePile);i++){
        (*R)[i] = sommet(p);
        depiler(p);

        //on change les couleurs dans l'affichage

        fprintf(doc, "\tf%d [label = %d, style=filled, fillcolor=green];\n\n", (*R)[i], (*R)[i]);
        fprintf(doc, "\t%d [label = %d, style=filled, fillcolor=green];\n\n", (*R)[i], (*R)[i]);


        #ifdef DEBUG
        printf("R[%d] : %d\n",i,(*R)[i]);
        #endif

        
    }

    fprintf(doc, "\n}\n");
    fclose(doc);

    libererPile(p);
    free(taillePile);

    return EXIT_SUCCESS;

}


