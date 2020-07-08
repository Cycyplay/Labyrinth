/*Auteur: VAN Cyril
*Création: 25-02-2020
*Modifications: 25-02-2020 | 03-03-2020*/


#ifndef __UNIONFIND__
#define __UNIONFIND__

#include "Labyrinthe.h"

/*Cette fonction cherche une case de coordonnées 'x' et 'y' dans 'laby' 
*('x' et 'y' sont les coordonnées d'un élément dans le labyrinthe, pas dans la matrice 'laby->cases'), 
*compresse le chemin parcouru pour trouver son père et renvoie à quelle classe elle appartient */
coordonnees_t trouver_compresse(laby_t * laby, int x, int y);

/*Cette fonction fusionne les deux classes qui contiennent ('x1', 'y1') et ('x2', 'y2') du labyrinthe (hors mur externes)*/
void fusion_classe(laby_t * laby, int x1, int y1, int x2, int y2);


#endif
