/*Auteurs: VAN Cyril - HEUDE Althéa
*Création: 11-03-2020
*Modifications: 11-03-2020 | 19-03-2020*/

#ifndef __FILELABY__
#define __FILELABY__

#include "Labyrinthe.h"


/*Cette structure représente une liste chaînée
*position est la position dans le labyrinthe de l'élément de la file
*pere est la case depuis laquelle on y a eu accès
*suivant est un pointeur vers le prochain élément de la file*/
typedef struct file_t {
	coordonnees_t position;
	coordonnees_t pere;
	struct file_t * suivant;
}File_t;



/*Permet de trouver le chemin le plus court pour finir le labyrinthe
*Ne marche uniquement que si le labyrinthe est déjà fini*/
File_t * chemin_victorieux(laby_t laby);


/*Permet d'afficher les éléments d'une file dans le terminal*/
void affiche_file(File_t * f);


#endif