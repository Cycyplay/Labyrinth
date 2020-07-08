/*Auteur: VAN Cyril
*Création: 25-02-2020
*Modifications: 25-02-2020 | 02-03-2020 | 03-03-2020*/
#include "UnionFind.h"


coordonnees_t trouver_compresse(laby_t * laby, int x, int y){
	int x_case, y_case;
	coordonnees_t pere_case;

	x_case = x + 1;
	y_case = y + 1;

	pere_case = laby->cases[x_case][y_case].pere;

	if (pere_case.x == x && pere_case.y == y){
		return pere_case;
	}else{
		pere_case = trouver_compresse(laby, laby->cases[x_case][y_case].pere.x, laby->cases[x_case][y_case].pere.y);

		laby->cases[x_case][y_case].pere = pere_case;
	}
	
	return pere_case;
}	


void fusion_classe(laby_t * laby, int x1, int y1, int x2, int y2){
	coordonnees_t pere1, pere2;
	int rang_pere1, rang_pere2;

	pere1 = trouver_compresse(laby, x1 - 1, y1 -1);
	pere2 = trouver_compresse(laby, x2 -1, y2 -1);

	if (pere1.x == pere2.x && pere1.y == pere2.y){
		return;
	}

	rang_pere1 = laby->cases[pere1.x + 1][pere1.y + 1].rang;
	rang_pere2 = laby->cases[pere2.x + 1][pere2.y + 1].rang;

	if (rang_pere1 >= rang_pere2){
		laby->cases[pere2.x + 1][pere2.y +1].pere = pere1;
		laby->cases[pere1.x +1][pere1.y +1].rang += laby->cases[pere2.x + 1][pere2.y +1].rang;
	}else{
		laby->cases[pere1.x + 1][pere1.y +1].pere = pere2;
		laby->cases[pere2.x +1][pere2.y +1].rang += laby->cases[pere1.x + 1][pere1.y +1].rang;
	}
}
