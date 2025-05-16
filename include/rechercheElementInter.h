#ifndef RECHERCHEELEMENTINTER_H
#define RECHERCHEELEMENTINTER_H

#include "../include/abrBalises.h"
#include "../include/abrBinaire.h"
#include "../include/pile.h"

int rechercheIntervalle(Abr* T, int a, int b, int **R, char* filename);
int rechercheIntervallePile(Abr* T, int a, int b, Pile* p, int* taillePile); 

#endif