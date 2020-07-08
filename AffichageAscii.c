/*Auteur : Althéa Heude
 *Création : 25-02-2020
 *Modifications : 25-02-2020 | 03-03-2020 | 07-03-2020*/

#include "AffichageAscii.h"
#include <stdio.h>

char* intersections[2][2][2][2] = 
   { {{{" ","╶"},{"╴","─"}},{{"╵","└"},{"┘","┴"}}},
     {{{"╷","┌"},{"┐","┬"}},{{"│","├"},{"┤","┼"}}} };

void ascii_base(laby_t laby){
	int i, j;

	for (i = 0; i <= laby.taille.x; i++){
		for(j = 0; j <= laby.taille.y; j++){				
			/*si il y a un mur est*/
			if (laby.cases[i][j].murEst == 1){
				printf("  |");
			}else{
				printf("   ");
			}
		}
		printf("\n");
		
		for (j = 0; j <= laby.taille.y; j++){

			/*si il y a un mur sud*/
			if (laby.cases[i][j].murSud == 1){
				if(j == laby.taille.y){
					printf("+--+");
				}else{
					printf("+--");
				}				
			}else{
				if(j == 0){
					printf("  ");
				}
				else if(j == laby.taille.y){
					printf("+  +");
				}
				else{
					printf("+  ");
				}
			}
		}
		printf("\n");
	}
}

void ascii_ameliore(laby_t laby){
	int i, j;

	for (i = 0; i <= laby.taille.x; i++){
		for (j = 0; j <= laby.taille.y; j++){
			if (i == 0){
				if (j == laby.taille.y){
					printf("%s", intersections[1][0][1][0]);
				}else if (j == 0){
					printf("%s", intersections[0][0][0][1]);

				}else{
					if (laby.cases[i + 1][j].murEst == 1){
						printf("%s", intersections[1][0][1][1]);
					}else{
						printf("%s", intersections[0][0][1][1]);
					}

				}
			}else if (i == laby.taille.x){
				if (j == 0){
					printf("%s", intersections[0][1][0][1]);
				}else if (j == laby.taille.y){
					printf("%s", intersections[0][0][1][0]);

				}else{
					if (laby.cases[i][j].murEst == 1){
						printf("%s", intersections[0][1][1][1]);
					}else{
						printf("%s", intersections[0][0][1][1]);
					}
				}
			}else{
				if (j == 0){
					if (i == 1){
						if (laby.cases[i][j + 1].murSud == 1){
							printf("%s", intersections[1][0][0][1]);
						}else{
							printf("%s", intersections[1][0][0][0]);
						}
					}else if (laby.cases[i][j + 1].murSud == 1){
						printf("%s", intersections[1][1][0][1]);
					}else{
						printf("%s", intersections[1][1][0][0]);
					}
				}else if (j == laby.taille.y){
					if (i == laby.taille.x - 1){
						if (laby.cases[i][j].murSud == 1){
							printf("%s", intersections[0][1][1][0]);
						}else{
							printf("%s", intersections[0][1][0][0]);
						}
					}else if (laby.cases[i][j].murSud == 1){
						printf("%s", intersections[1][1][1][0]);
					}else{
						printf("%s", intersections[1][1][0][0]);
						
					}
				}else{
					if (laby.cases[i][j].murEst == 1){
						if(laby.cases[i][j].murSud == 1){
							if (laby.cases[i][j + 1].murSud == 1){
								if (laby.cases[i + 1][j].murEst == 1){
									printf("%s", intersections[1][1][1][1]);
								}else{
									printf("%s", intersections[0][1][1][1]);
								}
							}else{
								if (laby.cases[i + 1][j].murEst == 1){
									printf("%s", intersections[1][1][1][0]);
								}else{
									printf("%s", intersections[0][1][1][0]);
								}
							}
						}else{
							if (laby.cases[i][j + 1].murSud == 1){
								if (laby.cases[i + 1][j].murEst == 1){
									printf("%s", intersections[1][1][0][1]);
								}else{
									printf("%s", intersections[0][1][0][1]);
								}
							}else{
								if (laby.cases[i + 1][j].murEst == 1){
									printf("%s", intersections[1][1][0][0]);
								}else{
									printf("%s", intersections[0][1][0][0]);
								}
							}
						}
					}else{
						if(laby.cases[i][j].murSud == 1){
							if (laby.cases[i][j + 1].murSud == 1){
								if (laby.cases[i + 1][j].murEst == 1){
									printf("%s", intersections[1][0][1][1]);
								}else{
									printf("%s", intersections[0][0][1][1]);
								}
							}else{
								if (laby.cases[i + 1][j].murEst == 1){
									printf("%s", intersections[1][0][1][0]);
								}else{
									printf("%s", intersections[0][0][1][0]);
								}
							}
						}else{
							if (laby.cases[i][j + 1].murSud == 1){
								if (laby.cases[i + 1][j].murEst == 1){
									printf("%s", intersections[1][0][0][1]);
								}else{
									printf("%s", intersections[0][0][0][1]);
								}
							}else{
								if (laby.cases[i + 1][j].murEst == 1){
									printf("%s", intersections[1][0][0][0]);
								}else{
									printf("%s", intersections[0][0][0][0]);
								}
							}
						}
					}
				}
			}
		}
		printf("\n");
	}
	printf("\n");
}