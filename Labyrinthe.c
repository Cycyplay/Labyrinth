/*Auteur: VAN Cyril
*Création: 25-02-2020
*Modifications: 25-02-2000 | 02-03-2020 | 05-03-2020 | 07-03-2020 | 10-03-2020*/
#include "Labyrinthe.h"

#include "MLV.h"
#include "AffichageAscii.h"
#include "UnionFind.h"

#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include <unistd.h>


/*Fonction qui initialise un case_t avec 'x' et 'y' ses coordonnées et la renvoie*/
case_t init_case(int x, int y, int hauteur, int largeur){
	case_t tmp;
	coordonnees_t coord_tmp;


	coord_tmp.x = x - 1;
	coord_tmp.y = y - 1;

	tmp.pere = coord_tmp;

	if (tmp.pere.x < 0){
		tmp.murEst = 0;
	}else{
		tmp.murEst = 1;
	}

	if(tmp.pere.y < 0){
		tmp.murSud = 0;
	}else{
		tmp.murSud = 1;
	}

	if(tmp.pere.x == 0 && tmp.pere.y == -1){
		tmp.murEst = 0;
	}

	if(tmp.pere.x == hauteur - 1 && tmp.pere.y == largeur - 1){
		tmp.murEst = 0;
	}
	
	tmp.rang = 1;

	return tmp;
}

/*Fonction qui initialise la matrice qui contient le labyrinthe en fonction de 'hauteur' et 'largeur'
*Renvoie le tableau de tableaux créé*/
case_t **init_table_cases(int hauteur, int largeur){
	int i, j;
	case_t **cases_tmp;

	cases_tmp = (case_t **)malloc(sizeof(case_t *) * (hauteur + 1));
	if (cases_tmp != NULL){
		for(i = 0; i <= hauteur; i++){
			cases_tmp[i] = (case_t *)malloc(sizeof(case_t) * (largeur +1));
			if (cases_tmp[i] == NULL){
				printf("Erreur lors de l'allocaion de mémoire pour le labyrinthe.\n");
				exit(EXIT_FAILURE);
			}
			for (j = 0; j <= largeur; j++){
				cases_tmp[i][j] = init_case(i, j, hauteur, largeur);
			}
		}
	}else{
		printf("Erreur lors de l'allocaion de mémoire pour le labyrinthe.\n");
		exit(EXIT_FAILURE);
	}

	return cases_tmp;
}

laby_t init_laby(int hauteur, int largeur){
	laby_t laby_tmp;
	coordonnees_t coord_tmp;

	laby_tmp.cases = init_table_cases(hauteur, largeur);

	/*Initialisation de la taille du labyrinthe avec la structure coordonnees_t*/
	coord_tmp.x = hauteur;
	coord_tmp.y = largeur;

	laby_tmp.taille = coord_tmp;

	return laby_tmp;
}

/*Fonction qui vérifie si, en fonction de 'mur', le 'boite->murEst' ou le 'boite->murSud' est présent
*ou non dans 'boite'. Si 'mur' vaut 0, on vérifie 'boite->murEst', sinon 'boite->murSud'
*Si le 'boite->murEst' ou 'boite->murSud' est présent, on l'enlève et renvoie 1 sinon renvoie 0*/
int verif_mur(case_t *boite, int mur, int x, int y, int hauteur, int largeur){
	if (mur == 0){
		if (y != largeur){
			if (boite->murEst == 1){
				boite->murEst = 0;
				return 1;
			}else{
				return 0;
			}
		}else{
			return 0;
		}

	}else{
		if (x != hauteur){
			if (boite->murSud == 1){
				boite->murSud = 0;
				return 1;
			}else{
				return 0;
			}
		}else{
			return 0;
		}
	}
}

int ajoute_mur(case_t *boite, int mur){
	if (mur == 0){
		boite->murEst = 1;
	}else{
		boite->murSud = 1;
	}
	return 1;
}

int supprime_mur(laby_t * laby, int unique){
	int x, y, mur;
	int tmp;
	coordonnees_t pere1, pere2;

	do{
		x = rand()%(laby->taille.x) + 1;
		y = rand()%(laby->taille.y) + 1;

		mur = rand()%2;
		
		tmp = verif_mur(&(laby->cases[x][y]), mur, x, y, laby->taille.x, laby->taille.y);

		if (tmp == 1){
			if (mur == 0){
				/*murEst*/
				if (unique == 1){
					pere1 = trouver_compresse(laby, x - 1, y - 1);
					pere2 = trouver_compresse(laby, x - 1, y);

					if (pere1.x == pere2.x && pere1.y == pere2.y){
						tmp = 0;
						ajoute_mur(&(laby->cases[x][y]), 0);
						continue;
					}
				}
				fusion_classe(laby, x, y, x, y + 1);
					
			}else{
				/*murSud*/
				if (unique == 1){
					pere1 = trouver_compresse(laby, x - 1, y - 1);
					pere2 = trouver_compresse(laby, x, y - 1);

					if (pere1.x == pere2.x && pere1.y == pere2.y){
						ajoute_mur(&(laby->cases[x][y]), 1);
						tmp = 0;
						continue;
					}
				}
				fusion_classe(laby, x, y, x + 1, y);
				
			}

			return 1;
		}
		
	}while (tmp == 0);

	return 0;
}

int est_termine_labyrinthe(laby_t * laby){
	coordonnees_t pere_debut, pere_fin;
	int x_debut, y_debut, x_fin, y_fin;

	x_debut = 0;
	y_debut = 0;

	x_fin = laby->taille.x - 1;
	y_fin = laby->taille.y - 1;

	pere_debut = trouver_compresse(laby, x_debut, y_debut);
	pere_fin = trouver_compresse(laby, x_fin, y_fin);
	

	if (pere_debut.x == pere_fin.x && pere_debut.y == pere_fin.y){
		return 1;
	}

	return 0;
}

void laby_classique(laby_t labyrinthe, int attente, int unique, int affichage, int victor){
	char tmp;

	if (affichage == 0){
		MLV_create_window("", "", 860, 640);
	}
	while(est_termine_labyrinthe(&labyrinthe) != 1){
		if (attente > 0){
			if (affichage == 0){
				affichage_graphique(labyrinthe);
				MLV_wait_milliseconds(attente);
			}else{
				ascii_ameliore(labyrinthe);
				usleep(attente*1000);
			}
		}else if (attente < 0){
			if (affichage == 0){
				affichage_graphique(labyrinthe);
				MLV_wait_keyboard_or_mouse(NULL, NULL, NULL, NULL, NULL);
			}else{
				ascii_ameliore(labyrinthe);
				scanf("%c", &tmp);
			}
		}
		supprime_mur(&labyrinthe, unique);
	}

	if (affichage == 0){
		affichage_graphique(labyrinthe);
		if (victor == 0){
			MLV_wait_keyboard_or_mouse(NULL, NULL, NULL, NULL, NULL);
			MLV_free_window();
		}
	}else{
		ascii_ameliore(labyrinthe);
	}
}

void laby_acces(laby_t labyrinthe, int attente, int unique, int affichage, int nb_cases, int victor){
	char tmp;
	coordonnees_t pere_entree;

	pere_entree = trouver_compresse(&labyrinthe, 0, 0);

	if (affichage == 0){
		MLV_create_window("", "", 860, 640);
	}

	while(labyrinthe.cases[pere_entree.x + 1][pere_entree.y + 1].rang != nb_cases){
		if (attente > 0){
			if (affichage == 0){
				affichage_graphique(labyrinthe);
				MLV_wait_milliseconds(attente);
			}else{
				ascii_ameliore(labyrinthe);
				usleep(attente*1000);
			}
		}else if (attente < 0){
			if (affichage == 0){
				affichage_graphique(labyrinthe);
				MLV_wait_keyboard_or_mouse(NULL, NULL, NULL, NULL, NULL);
			}else{
				ascii_ameliore(labyrinthe);
				scanf("%c", &tmp);
			}
		}
		supprime_mur(&labyrinthe, unique);
		pere_entree = trouver_compresse(&labyrinthe, 0, 0);
	}
	if (affichage == 0){
		affichage_graphique(labyrinthe);
		if (victor == 0){
			MLV_wait_keyboard_or_mouse(NULL, NULL, NULL, NULL, NULL);
			MLV_free_window();
		}
	}else{
		ascii_ameliore(labyrinthe);
	}
}