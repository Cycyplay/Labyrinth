/*Auteur : Althéa Heude
 *Création : 25-02-2020
 *Modifications : 25-02-2020 | 03-03-2020 | 7-03-2020*/

#include "MLV.h"
#include <MLV/MLV_all.h>

/*TAILLE DE LA FENETRE*/
#define HAUTEUR 640
#define LARGEUR 860


/*Cette fonction calcule le rapport du labyrinthe pour avoir des cases carrées*/
int calcul_rapport(laby_t laby){
	int hauteur, largeur;
	int rpt;

	hauteur = laby.taille.x + 2;
	largeur = laby.taille.y + 2;

	if(hauteur >= largeur){
		rpt = HAUTEUR  / hauteur;
	}else{
		rpt = LARGEUR / largeur;
	}

	return rpt;
}

/*Affiche le labyrinthe dans une fenêtre MLV déjà ouverte*/
void affichage_laby(laby_t laby){
	int i, j;
	int rpt;

	rpt = calcul_rapport(laby);

	for(i = 0; i <= laby.taille.x; i++){
		for(j = 0; j <= laby.taille.y; j++){
			/*mur Est*/
			if(laby.cases[i][j].murEst == 1){
				MLV_draw_line((j+1)*rpt, i*rpt, (j+1)*rpt, (i+1)*rpt, MLV_COLOR_WHITE);
			}
			/*mur Sud*/
			if(laby.cases[i][j].murSud == 1){
				MLV_draw_line(j*rpt, (i+1)*rpt, (j+1)*rpt, (i+1)*rpt, MLV_COLOR_WHITE);
			}
		}
	}
}

/*Permet de simuler un effacement de la fenêtre en noir*/
void affiche_fond(){
    MLV_clear_window(MLV_COLOR_BLACK);
}


void affichage_graphique(laby_t laby){
	affiche_fond();
	affichage_laby(laby);
	MLV_actualise_window();
}


void affiche_victor(laby_t laby, File_t * f){
	int rpt;
	File_t * tmp;

	rpt = calcul_rapport(laby);
	tmp = f;

	while (tmp != NULL){
		MLV_draw_filled_rectangle((tmp->position.y + 1) * rpt + rpt/4, (tmp->position.x + 1) * rpt + rpt/4, rpt/2, rpt/2, MLV_COLOR_GREEN);
		tmp = tmp->suivant;
	}

	MLV_actualise_window();

}