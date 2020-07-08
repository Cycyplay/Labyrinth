/*Auteurs: VAN Cyril - HEUDE Althéa
*Création: 25-02-2000
*Modifications: 25-02-2020 | 03-03-2020 | 05-03-2020 | 07-03-2020 | 10-03-2020 | 19-03-2020*/

#include "Labyrinthe.h"
#include "Option.h"
#include "FileLaby.h"
#include "MLV.h"
#include "AffichageAscii.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

int main(int argc, char * argv[]){
	laby_t labyrinthe;
	File_t * f_chemin;

	int affichage;
	int hauteur, largeur;
	int graine;
	int attente;
	int unique;
	int acces;
	int victor;

	recupere_option(argc, argv, &affichage, &hauteur, &largeur, &graine, &attente, &unique, &acces, &victor);
	
	labyrinthe = init_laby(hauteur, largeur);


	if (acces == 1){
		laby_acces(labyrinthe, attente, unique, affichage, hauteur * largeur, victor);
	}else{
		laby_classique(labyrinthe, attente, unique, affichage, victor);
	}

	if (victor == 1){

		f_chemin = chemin_victorieux(labyrinthe);

		if (affichage == 0){
			affiche_victor(labyrinthe, f_chemin);
		}else{
			printf("Le chemin le plus rapide est:\n");
			affiche_file(f_chemin);
		}

		if (affichage == 0){
			MLV_wait_keyboard_or_mouse(NULL, NULL, NULL, NULL, NULL);
			MLV_free_window();
		}
	}

	return 0;
}