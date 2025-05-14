#ifndef ABRBALISES_H
#define ABRBALISES_H

#include "../include/abrBinaire.h"
#include "../include/pile.h"
#include "stdio.h"
#include "stdlib.h"

void fixerCle(Abr* abr, int a);
void ajouterFeuillesPartout(Abr* abr);
void versAbreBalise(Abr* abr, Pile* p);

#endif