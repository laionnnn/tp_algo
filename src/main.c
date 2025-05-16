#include "../include/abrBalises.h"
#include "../include/abrBinaire.h"
#include "../include/pile.h"
#include "../include/interface.h"
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
	Noeud* n4 = creerNoeud(4, 0);
	
	Abr* T = creerAbr(n7);
	/*Pile* p = malloc(sizeof(Pile));
	if (!p) {
		fprintf(stderr, "Erreur malloc\n");
		exit(EXIT_FAILURE);
	}
	
	initPile(p);
	printf("okkkkkkkk\n");
	ajouterFeuillesPartout(T);
	
	
	versAbreBalise(T,p);
	printf("okkkkkkkk2\n");*/
	
	insererFeuilleBalise(n3, T);
	insererFeuilleBalise(n4, T);	
	insererFeuilleBalise(n6, T);

	supprimerFeuilleBalise(5, T);
	supprimerFeuilleBalise(7, T);
	supprimerFeuilleBalise(4, T);
	
	//parcoursInfixe(T);
	//printf("\nFacteur = %d\n",facteurDesequilibre(T));
	exportDotGraph(T, "test.dot");
	system( "dot -Tpng test.dot -o outfile.png" );
	//supprimerAbr(T);
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
				printf("Conversion d'un ABRE vers un ABRE-balisé :\nUn ABRE et un ABRE-Balisé ont été générés dans ./Conversion.\n L'ABRE-Balisé a été construit par conversion de ABRE.\n\n");
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
				Pile* p = malloc(sizeof(Pile));
				if (!p) {
					fprintf(stderr, "Erreur malloc\n");
					exit(EXIT_FAILURE);
				}
				initPile(p);
				ajouterFeuillesPartout(T1);
				versAbreBalise(T1, p);
				exportDotGraph(T1, "./Conversion/ABREBalise.dot");
				system( "dot -Tpng ./Conversion/ABREBalise.dot -o ./Conversion/ABREBalise.png" );

				libererPile(p);
				supprimerAbr(T1);
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