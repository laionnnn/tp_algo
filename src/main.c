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
	
	Noeud* n7 = creerNoeud(7, 0);
	Noeud* n3 = creerNoeud(3, 0);
	Noeud* n9 = creerNoeud(9, 0);
	Noeud* n1 = creerNoeud(1, 0);
	Noeud* n5 = creerNoeud(5, 0);
	Noeud* n6 = creerNoeud(6, 0);
	Noeud* n4 = creerNoeud(4, 0);
	
	Abr* T = creerAbr(n7);
	insererNoeud(n3, T);
	insererNoeud(n9, T);
	insererNoeud(n1, T);
	insererNoeud(n5, T);
	insererNoeud(n6, T);	

	versAbreBalise(T);
	
	//parcoursInfixe(T);
	//printf("\nFacteur = %d\n",facteurDesequilibre(T));
	exportDotGraph(T, "test.dot");
	//system( "dot -Tpng test.dot -o outfile.png" );
	//supprimerAbr(T);

	//insererFeuilleBalise(n6, T);
	
	int* R;
	rechercheIntervalle(T,2,7,&R, "test.dot");
	free(R);
	system( "dot -Tpng test.dot -o outfile.png" );

	#else
	short select;
	while (1) { // Boucle principale
		printf("\n\n █████  ██████  ██████  ███████       ██████   █████  ██      ██ ███████ ███████ \n██   ██ ██   ██ ██   ██ ██            ██   ██ ██   ██ ██      ██ ██      ██      \n███████ ██████  ██████  █████   █████ ██████  ███████ ██      ██ ███████ █████   \n██   ██ ██   ██ ██   ██ ██            ██   ██ ██   ██ ██      ██      ██ ██      \n██   ██ ██████  ██   ██ ███████       ██████  ██   ██ ███████ ██ ███████ ███████ \nAuthors: T. Ouerfili, L. Frénéa\nCopyright 2025 T. Ouerfili, L. Frénéa\n\n");
		printf("Bienvenue dans le programme du TP4 - Arbres binaires de recherche équilibrés et balisés\n");
		
		while (select < 1 || select > 9) { // Entrée d'un l'input valide
			printf("Veuillez sélectionner une option :\n\t[1]- Création d\'un ABRE-balisé\n\t[2]- Conversion d'un ABRE vers un ABRE-balisé\n\t[3]- Recherche d'éléments d'intervalle\n\t[9]- Quitter\n\n\n");
			scanf("%hd", &select);
		}
		
		switch (select) {
			case 1: //Création d'un ABRE-balisé
				select = 0; // On déselectionne
				int noeud;
				int insSup;
				printf("Création/Affichage d'un ABRE-balisé :\nL'arbre créé peut-être visualisé au fur et à mesure en ouvrant le fichier ./Creation/ArbreCree.png qui sera généré\nN'insérez pas de noeuds avec le même nom !\nPour revenir au menu, insérez un noeud -1\n\n");
				system("mkdir -p ./Creation");
				printf("Racine à insérer ?\n>>> ");
				scanf("%d", &noeud);
				Abr* T = creerAbr(creerNoeud(noeud, 0));
				while(1) {
					printf("Noeud ?\n>>> ");
					scanf("%d", &noeud);
					if (noeud == -1) break;
					printf("Insertion [1] ou Suppression [0]\n>>> ");
					scanf("%d", &insSup);
					if (insSup) insererFeuilleBalise(creerNoeud(noeud, 0), T);
					else supprimerFeuilleBalise(noeud, T);
					exportDotGraph(T, "./Creation/ArbreCree.dot");
					system( "dot -Tpng ./Creation/ArbreCree.dot -o ./Creation/ArbreCree.png" );
				}
				supprimerAbr(T);
				break;
			case 2: //Conversion d'un ABRE vers un ABRE-balisé
				select = 0; // On déselectionne
				printf("Conversion d'un ABRE vers un ABRE-balisé :\nUn ABRE et un ABRE-Balisé ont été générés dans ./Conversion.\nL'ABRE-Balisé a été construit par conversion de ABRE.\n\n");
				system("mkdir -p ./Conversion");

				/*ABRE*/
				Abr* T1 = creerAbr(creerNoeud(47, 0));
				
				insererNoeud(creerNoeud(25, 0),T1);
				insererNoeud(creerNoeud(80, 0),T1);
				
				insererNoeud(creerNoeud(10, 0),T1);
				insererNoeud(creerNoeud(37, 0),T1);
				insererNoeud(creerNoeud(62, 0),T1);
				insererNoeud(creerNoeud(89, 0),T1);
				
				insererNoeud(creerNoeud(7, 0),T1);
				insererNoeud(creerNoeud(19, 0),T1);
				insererNoeud(creerNoeud(30, 0),T1);
				insererNoeud(creerNoeud(59, 0),T1);
				insererNoeud(creerNoeud(70, 0),T1);
				insererNoeud(creerNoeud(97, 0),T1);
				
				exportDotGraph(T1, "./Conversion/ABRE.dot");
				system( "dot -Tpng ./Conversion/ABRE.dot -o ./Conversion/ABRE.png" );
				
				/*ABRE-Balisé*/
				versAbreBalise(T1);
				exportDotGraph(T1, "./Conversion/ABREBalise.dot");
				system( "dot -Tpng ./Conversion/ABREBalise.dot -o ./Conversion/ABREBalise.png" );

				supprimerAbr(T1);
				break;
			case 3: //Recherche d'éléments d'intervalle
				select = 0; // On déselectionne
				int a;
				int b;
				printf("Recherche d'éléments d'intervalle :\nEn accord avec l'énoncé de la partie B, un arbre avec les éléments de l'intervalle R surlignés va être généré dans ./Intervalle.\nVeuillez spécifier l'intervalle :\n\n");
				system("mkdir -p ./Intervalle");
				do {
					printf("[a ?\n");
					scanf("%d", &a);
					printf("%d\n", a);
					printf("b] ?\n");
					scanf("%d", &b);
					printf("%d\n", b);
				} while ((a < 7 || a > 97) || (b < 7 || b > 97) || (a > b));

				printf("Bien reçu !\n");
				Abr* TR = creerAbr(creerNoeud(47, 0));
				
				insererNoeud(creerNoeud(25, 0),TR);
				insererNoeud(creerNoeud(80, 0),TR);
				
				insererNoeud(creerNoeud(10, 0),TR);
				insererNoeud(creerNoeud(37, 0),TR);
				insererNoeud(creerNoeud(62, 0),TR);
				insererNoeud(creerNoeud(89, 0),TR);
				
				insererNoeud(creerNoeud(7, 0),TR);
				insererNoeud(creerNoeud(19, 0),TR);
				insererNoeud(creerNoeud(30, 0),TR);
				insererNoeud(creerNoeud(59, 0),TR);
				insererNoeud(creerNoeud(70, 0),TR);
				insererNoeud(creerNoeud(97, 0),TR);
				versAbreBalise(TR);
				exportDotGraph(TR, "./Intervalle/ABREBIntervalle.dot");
				int* R;
				rechercheIntervalle(TR, a, b, &R, "./Intervalle/ABREBIntervalle.dot");
				free(R);
				system( "dot -Tpng ./Intervalle/ABREBIntervalle.dot -o ./Intervalle/ABREBIntervalle.png" );
				supprimerAbr(TR);
				break;
			case 9: // Quitter
				exit(EXIT_SUCCESS);
			default:
				select = 0; // On déselectionne
				printf("Option indisponible...");
				break;
		}
	}
	#endif
	return EXIT_SUCCESS;

}