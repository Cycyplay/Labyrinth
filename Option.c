/*Auteur : Althéa Heude
 *Création : 5-03-2020
 *Modifications : 5-03-2020 | 7-03-2020 | 10-03-2020*/

#include "Option.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

/*Vérifie si l'option '--mode=texte' est passée en argument
*Renvoie 1 si oui, sinon 0*/
int option_ascii(int argc, char * argv[]){
	int i;

	for(i = 0; i < argc; i++){
		if(strcmp("--mode=texte", argv[i]) == 0)
			return 1;
	}
	return 0;
}


/*Vérifie si l'option '--taille=NxM' est passée en argument
*Renvoie par adresse 'N' dans 'hauteur et 'M' dans 'largeur' puis renvoie 1
*Sinon renvoie 0*/
int option_taille(int argc, char * argv[], int * hauteur, int * largeur){
	int i, j, k;
	char chiffre[MAX];

	for(i = 0; i < argc; i++){
		if(strncmp("--taille=", argv[i], 9) == 0){
			j = 9;
			k = 0;
			while(argv[i][j] != 'x'){
				chiffre[k] = argv[i][j];
				j++;
				k++;
			}
			chiffre[k+1] = '\0';
			*hauteur = atoi(chiffre);
			k = 0;
			j++;
			while(argv[i][j] != '\0'){
				chiffre[k] = argv[i][j];
				j++;
				k++;
			}
			chiffre[k+1] = '\0';
			*largeur = atoi(chiffre);

			return 1;
		}
	}
	return 0;
}


/*Vérifie si l'option '--graine=N' est passée en argument
*Renvoie la valeur de le graine par adresse si l'option est demandé
*Sinon renvoie 0 si l'option n'est pas demandée*/
int option_graine(int argc, char * argv[], int * graine){
	int i, j, k;
	char chiffre[MAX];

	for(i = 0; i < argc; i++){
		if(strncmp("--graine=", argv[i], 9) == 0){
			j = 9;
			k = 0;
			while(argv[i][j] != '\0'){
				chiffre[k] = argv[i][j];
				j++;
				k++;
			}
			chiffre[k+1] = '\0';
			*graine = atoi(chiffre);

			return 1;
		}
	}
	return 0;
}

/*Vérifie si l'option '--attente=N' est passée en argument
*Renvoie la valeur de l'attente par adresse si l'option est demandé et 1
*Sinon renvoie 0 si l'option n'est pas demandée et -1 par adresse*/
int option_attente(int argc, char * argv[], int * attente){
	int i, j, k;
	char chiffre[MAX];

	for(i = 0; i < argc; i++){
		if(strncmp("--attente=", argv[i], 10) == 0){
			j = 10;
			k = 0;
			while(argv[i][j] != '\0'){
				chiffre[k] = argv[i][j];
				j++;
				k++;
			}
			chiffre[k+1] = '\0';
			*attente = atoi(chiffre);

			return 1;
		}
	}
	return 0;
}

/*Vérifie si l'option '--unique' est passée en argument
*Renvoie 1 si oui, sinon 0*/
int option_unique(int argc, char * argv[]){
	int i;

	for(i = 0; i < argc; i++){
		if(strcmp("--unique", argv[i]) == 0)
			return 1;
	}
	return 0;
}

/*Vérifie si l'option '--acces' est passée en argument
*Renvoie 1 si oui, sinon 0*/
int option_acces(int argc, char * argv[]){
	int i;

	for(i = 0; i < argc; i++){
		if(strcmp("--acces", argv[i]) == 0)
			return 1;
	}
	return 0;
}

/*Vérifie si l'option '--victor' est passée en argument
*Renvoie 1 si oui, sinon 0*/
int option_victor(int argc, char * argv[]){
	int i;

	for(i = 0; i < argc; i++){
		if(strcmp("--victor", argv[i]) == 0)
			return 1;
	}
	return 0;
}

void recupere_option(int argc, char * argv[], int * affichage, int * hauteur, int * largeur, int * graine, int * attente, int * unique, int * acces, int * victor){

	*affichage = option_ascii(argc, argv);

	if(option_taille(argc, argv, hauteur, largeur) == 0){
		*hauteur = 6;
		*largeur = 8;
	}

	if(option_graine(argc, argv, graine) == 0){
		srand(time(NULL));
	}else{
		srand(*graine);
	}

	if (option_attente(argc, argv, attente) == 0){
		*attente = -1;
	}

	*unique = option_unique(argc, argv);

	*acces = option_acces(argc, argv);

	*victor = option_victor(argc, argv);
}