/*Auteur : Althéa Heude
 *Création : 5-03-2020
 *Modifications : 5-03-2020 | 7-03-2020 | 10-03-2020*/

#ifndef __OPTION__
#define __OPTION__


/*Vérifie si une option est passée en argument ou non
*
*Elle vérifie et renvoie par adresse 1 si oui, sinon 0 pour:
*'affichage' qui récupère '--mode=texte'
*'unique' qui récupere '--unique'
*'acces' qui récupère '--acces'
*'victor' qui récupère '--victor'
*
*Elle vérifie aussi la présence des autre option renvoie par adresse 
*leur valeur passée en arguments sinon leur valeur de base
*'hauteur' récupère N de '--taille=NxM'
*'largeur' récupère M de '--taille=NxM'
*'graine' récupère N de '--graine=N'
*'attente' récupère N de '--attente=N', renvoie -1 si l'option n'est pas demandée
*/
void recupere_option(int argc, char * argv[], int * affichage, int * hauteur, int * largeur, int * graine, int * attente, int * unique, int * acces, int * victor);

#endif