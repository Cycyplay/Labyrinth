/*Auteur : Althéa Heude
 *Création : 25-02-2020
 *Modifications : 25-02-2020 | 03-03-2020 | 7-03-2020*/

#ifndef __MLV__
#define __MLV__

#include "Labyrinthe.h"
#include "FileLaby.h"

/*affiche le labyrinthe d'après la structure laby_t*/
void affichage_graphique(laby_t laby);

/*met en evidence le chemin le plus court pour sortir du labyrinthe*/
void affiche_victor(laby_t laby, File_t * f);

#endif