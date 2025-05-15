#include "../include/abrBalises.h"
#include "../include/abrBinaire.h"
#include "../include/pile.h"
#include "../include/interface.h"
#include "../include/rechercheElementInter.h"
#include "stdio.h"
#include "stdlib.h"
#include <stdio.h>
#include <stdbool.h>






int main()
{
	#ifdef DEBUG
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
	insererNoeud(n1, T);
	insererNoeud(n5, T);	

	
	
	
	versAbreBalise(T);
	printf("okkkkkkkk2\n");
	insererFeuilleBalise(n6, T);

	int* R;
	rechercheIntervalle(T,2,6,&R);
	free(R);
	
	//parcoursInfixe(T);
	//printf("\nFacteur = %d\n",facteurDesequilibre(T));
	exportDotGraph(T, "test.dot");
	system( "dot -Tpng test.dot -o outfile.png" );
	//supprimerAbr(T);
	#else
	short select;
	while (select < 1 || select > 9) {
		printf("\n\n █████  ██████  ██████  ███████       ██████   █████  ██      ██ ███████ ███████ \n██   ██ ██   ██ ██   ██ ██            ██   ██ ██   ██ ██      ██ ██      ██      \n███████ ██████  ██████  █████   █████ ██████  ███████ ██      ██ ███████ █████   \n██   ██ ██   ██ ██   ██ ██            ██   ██ ██   ██ ██      ██      ██ ██      \n██   ██ ██████  ██   ██ ███████       ██████  ██   ██ ███████ ██ ███████ ███████ \n\nAuthors: T. Ouerfili, L. Frénéa\nCopyright 2025 T. Ouerfili, L. Frénéa\n\n");
		printf("Bienvenue dans le programme du TP4 - Arbres binaires de recherche équilibrés et balisés\nVeuillez sélectionner une option :\n\t[1]- Création d\'un ABRE-balisé\n\t[2]- Conversion d'un ABRE vers un ABRE-balisé\n\t[3]- Insertion/Suppression dans un ABRE-balisé\n\t[9]- Quitter\n\n\n");
		scanf("%hd", &select);
		
		switch (select) {
			case 1:
				break;
			default:
				printf("Option indisponible...");
				break;
		}
	}
	#endif
	return EXIT_SUCCESS;

}