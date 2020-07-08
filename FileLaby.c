/*Auteurs: VAN Cyril - HEUDE Althéa
*Création: 11-03-2020
*Modifications: 11-03-2020 | 19-03-2020*/
#include "FileLaby.h"
#include "UnionFind.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int est_vide(File_t * f){
	if (f == NULL){
		return 1;
	}
	return 0;
}

int enleve_file(File_t * f){
	File_t * tmp, *prec;

	tmp = f;
	prec = NULL;

	if (est_vide(f) == 1){
		return 0;
	}

	while (tmp->suivant != NULL){
		prec = tmp;
		tmp = tmp->suivant;
	}

	if (prec == NULL){
		f = NULL;
		return 1;
	}

	prec->suivant = NULL;
	return 1;
}


/*Teste si un élément est déjà dans la file ou non
*Renvoie 1 si oui, sinon 0*/
File_t * est_dans_file(File_t * f, int x, int y){
	File_t * tmp;

	tmp = f;

	while(tmp != NULL){
		if (tmp->position.x == x && tmp->position.y == y){
			return tmp;
		}
		tmp = tmp->suivant;
	}
	return NULL;
}

int nb_fils(File_t * f, coordonnees_t position){
	int cpt;
	File_t * tmp;

	tmp = f;
	cpt = 0;

	while (tmp != NULL){
		if (tmp->pere.x == position.x && tmp->pere.y == position.y){
			cpt += 1;
		}
		tmp = tmp->suivant;
	}

	return cpt;
}

File_t * extraire_file(File_t * f, coordonnees_t position){
	File_t * tmp, *prec;

	tmp = f;
	prec = NULL;

	while (tmp != NULL){
		if (tmp->position.x == position.x && tmp->position.y == position.y){
			break;
		}

		prec = tmp;
		tmp = tmp->suivant;
	}

	if (tmp == NULL){
		return NULL;
	}

	if (prec == NULL){
		if (tmp->suivant == NULL){
			return tmp;
		}

		*f = *(tmp->suivant);
		tmp->suivant = NULL;
		return tmp;
	}

	prec->suivant = tmp->suivant;
	tmp->suivant = NULL;
	return tmp;
}

File_t * extraire_peres_file(File_t * f_chemin, File_t * f_suppr, coordonnees_t position, laby_t laby){
	File_t * tmp, *tmp_suppr;

	if (nb_fils(f_chemin, position) > 0){
		return est_dans_file(f_chemin, position.x, position.y);
	}

	if (position.x == laby.taille.x - 1 && position.y == laby.taille.y - 1){
		return est_dans_file(f_chemin, position.x, position.y);
	}

	tmp = extraire_file(f_chemin, position);

	if (tmp == NULL){
		return NULL;
	}

	tmp_suppr = f_suppr;

	if (tmp_suppr == NULL){
		*f_suppr = *tmp;
	}else{
		while (tmp_suppr->suivant != NULL){
			tmp_suppr = tmp_suppr->suivant;
		}

		tmp_suppr->suivant = tmp;
	}

	return extraire_peres_file(f_chemin, f_suppr, tmp->pere, laby);
}



File_t * init_file(coordonnees_t position, coordonnees_t pere){
	File_t * tmp;

	tmp = (File_t *)malloc(sizeof(File_t));
	if (tmp != NULL){
		tmp->position = position;
		tmp->pere = pere;
		tmp->suivant = NULL;
	}else{
		exit(EXIT_FAILURE);
	}

	return tmp;
}

/*Ajoute un élément avec 'position' et 'pere' à la fin de la file */
int ajoute_file(File_t * f, coordonnees_t position, coordonnees_t pere){
	File_t * tmp, *prec;

	tmp = f;
	prec = NULL;

	while(tmp != NULL){
		prec = tmp;
		tmp = tmp->suivant;
	}

	if (prec == NULL){
		*f = *(init_file(position, pere));
		if (f == NULL){
			return 0;
		}
		return 1;
	}

	prec->suivant = init_file(position, pere);
	if (prec->suivant == NULL){
		return 0;
	}
	return 1;
}


void affiche_file(File_t * f){
	File_t * tmp;
	tmp = f;

	while (tmp != NULL){
		printf("(%d, %d) ", tmp->position.x, tmp->position.y);
		tmp = tmp->suivant;
	}
	printf("\n");
}

int ajoute_case_adjacentes(laby_t laby, File_t * f_chemin, File_t * f_suppr, coordonnees_t position){
	int cpt;
	coordonnees_t repr_debut, repr_act;

	cpt = 0;

	repr_debut = trouver_compresse(&laby, 0, 0);

	/*HAUT*/
	if (position.x - 1 >= 0){
		if (est_dans_file(f_chemin, position.x - 1, position.y) == NULL && est_dans_file(f_suppr, position.x - 1, position.y) == NULL){
			repr_act = trouver_compresse(&laby, position.x - 1, position.y);

			if (repr_debut.x == repr_act.x && repr_debut.y == repr_act.y){

				if (laby.cases[position.x][position.y + 1].murSud == 0){
					coordonnees_t nouv_pos;

					nouv_pos.x = position.x - 1;
					nouv_pos.y = position.y;
					ajoute_file(f_chemin, nouv_pos, position);

					cpt += 1;
				}
			}
		}
	}
	/*DROITE*/
	if (position.y + 1 < laby.taille.y){
		if (est_dans_file(f_chemin, position.x, position.y + 1) == NULL && est_dans_file(f_suppr, position.x, position.y + 1) == NULL){
			repr_act = trouver_compresse(&laby, position.x, position.y + 1);

			if (repr_debut.x == repr_act.x && repr_debut.y == repr_act.y){

				if (laby.cases[position.x + 1][position.y + 1].murEst == 0){
					coordonnees_t nouv_pos;

					nouv_pos.x = position.x;
					nouv_pos.y = position.y + 1;
					ajoute_file(f_chemin, nouv_pos, position);

					cpt += 1;
				}
			}
		}
	}
	/*BAS*/
	if (position.x + 1 < laby.taille.x){
		if (est_dans_file(f_chemin, position.x + 1, position.y) == NULL && est_dans_file(f_suppr, position.x + 1, position.y) == NULL){
			repr_act = trouver_compresse(&laby, position.x + 1, position.y);

			if (repr_debut.x == repr_act.x && repr_debut.y == repr_act.y){

				if (laby.cases[position.x + 1][position.y + 1].murSud == 0){
					coordonnees_t nouv_pos;

					nouv_pos.x = position.x + 1;
					nouv_pos.y = position.y;
					ajoute_file(f_chemin, nouv_pos, position);

					cpt += 1;
				}
			}
		}
	}
	/*GAUCHE*/
	if (position.y - 1 >= 0){
		if (est_dans_file(f_chemin, position.x, position.y - 1) == NULL && est_dans_file(f_suppr, position.x, position.y - 1) == NULL){
			repr_act = trouver_compresse(&laby, position.x, position.y - 1);

			if (repr_debut.x == repr_act.x && repr_debut.y == repr_act.y){

				if (laby.cases[position.x + 1][position.y].murEst == 0){
					coordonnees_t nouv_pos;

					nouv_pos.x = position.x;
					nouv_pos.y = position.y - 1;
					ajoute_file(f_chemin, nouv_pos, position);

					cpt += 1;
				}
			}
		}
	}
	return cpt;
}


File_t * chemin_victorieux(laby_t laby){
	File_t * f_chemin, *f_suppr, *tmp, *prec;
	coordonnees_t position, position_tmp;
	int cpt;

	position.x = 0;
	position.y = 0;

	position_tmp.x = -1;
	position_tmp.x = -1;

	f_chemin = init_file(position, position);
	f_suppr = init_file(position_tmp, position_tmp);

	prec = NULL;
	tmp = f_chemin;

	while(tmp != NULL){
		position = tmp->position;
		
		cpt = ajoute_case_adjacentes(laby, f_chemin, f_suppr, position);


		if (position.x == laby.taille.x - 1 && position.y == laby.taille.y - 1){

			prec = tmp;
			tmp = tmp->suivant;
			continue;
		}

		if (cpt == 0){
			tmp = extraire_peres_file(f_chemin, f_suppr, position, laby);
			if (tmp == NULL){
				tmp = prec;
			}
		}

		prec = tmp;
		tmp = tmp->suivant;
	}

	return f_chemin;
}


