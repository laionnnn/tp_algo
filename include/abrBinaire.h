#ifndef ABRBINAIRE_H
#define ABRBINAIRE_H

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

Noeud* creerNoeud(int id, char data);
Abr* creerAbr(Noeud* n);
int insererNoeud(Noeud* n, Abr* T);
int insererFeuilleBalise(Noeud* n, Abr* T);
int parcoursInfixe(Abr* T);
int supprimerAbr(Abr* T);
int facteurDesequilibre(Abr* T);

#endif