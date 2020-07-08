/*Auteur: VAN Cyril
*Création: 25-02-2020
*Modifications: 25-02-2000 | 02-03-2020 | 07-03-2020 | 10-03-2020*/
#ifndef __LABYRINTHE__
#define __LABYRINTHE__


/*Structure représentant les coordonnées d'une cellule du labyrinthe
*'x' pour les ordonnes et 'y' pour les abscisse*/
typedef struct coordonnees_t {
	int x;
	int y;
}coordonnees_t;


/*Structure représentant une cellule
*murEst et murSud sont des booleens
*pere correspond aux coordonnees du représentant de la classe de case_t
*rang correspond aux nombre d'élements dans la classe dont il est le représentant*/
typedef struct {
	int murEst ;
	int murSud ;
	coordonnees_t pere;
	int rang;
}case_t;


/*Structure représentant le labyrinthe de dimension 'taille'
*et contient l'ensemble des cellules du labyrinthe dans 'cases'*/
typedef struct laby{
	coordonnees_t taille ;
	case_t ** cases; /* attention murs extremes a conserver */
}laby_t;

/*Cette fonction initilalise un labyrinthe de dimensions 'hauteur' * 'largeur'
*Toutes les cellules possèdent des murs
*Renvoie le laby_t une fois construit*/
laby_t init_laby(int hauteur, int largeur);


/*Cette fonction supprime un mur aléatoirement à l'aide de rand()
*dans le laby_t 'laby' et le modifie
*Renvoie 1 en cas de bonne exécution de la fonction*/
int supprime_mur(laby_t * laby, int unique);


/*Cette fonction vérifie si les deux cases de début est fin de layrinthe sont
*dans la même classe. Compresse les chemins trouvés. 
*Renvoie 1 si les deux cases ont le même père, 0 sinon*/
int est_termine_labyrinthe(laby_t * laby);

/*Cette fonction génère le labyrinthe sans l'option acces
*'attente' est le résultat de l'option '--attente', négatif s'il l'option n'a pas été renseignée
*'unique' est un booléen renseignant si l'option '--unique' à été demandé ou non
*'affichage' renseigne sur le mode d'affichage: 0 pour MLV, 1 pour texte
*'nb_cases' représente le nombre de cases qui compose le labyrinthe
*'victor' renseigne si l'option '--victor' est demandée*/
void laby_classique(laby_t labyrinthe, int attente, int unique, int affichage, int victor);

/*Cette fonction génère le labyrinthe avec l'option acces
*'attente' est le résultat de l'option '--attente', négatif s'il l'option n'a pas été renseignée
*'unique' est un booléen renseignant si l'option '--unique' à été demandé ou non
*'affichage' renseigne sur le mode d'affichage: 0 pour MLV, 1 pour texte
*'nb_cases' représente le nombre de cases qui compose le labyrinthe
*'victor' renseigne si l'option '--victor' est demandée*/
void laby_acces(laby_t labyrinthe, int attente, int unique, int affichage, int nb_cases, int victor);

#endif