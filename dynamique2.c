#include <stdlib.h>
#include <stdio.h>
#include "Point.h"
#include "parser.h"
#include "distance.h"


double dyn();

Point *points = NULL;
int nb_points = 0;
double C = 1.5;


int main(int argc, char* argv[]) {
	if(argc < 2) {
		printf("Erreur : veuillez spécifier le fichier à lire\n");
		return 0;
	} else if (argc == 3) {
		C = atof(argv[2]);
		//printf("C = %f\n", C);
	}

	parser(argv[1], &points, &nb_points);

	if(nb_points < 3) {
		printf("Erreur lors de la lecture du fichier\nIl doit contenir au moins 3 points\n");
		return 0;
	}
	// appel à dyn pour calculer par approche dynamique la solution optimale
	printf("\nCopt = %f\n", dyn());

	free(points);

	return 0;
}


/**
 *	Fonction qui calcule le coup optimal de la solution à l'aide d'une approche dynamique.
 *	Cette fonction rempli aussi le tableau des points choisis pour créer la solution optimale.
 */
double dyn() {
	//double approx[nb_points][nb_points];
	double **approx;	//déclaration dynamique pour ne pas être limitée par la taille de la pile en mémoire
	int index_diag;
	int taille_diag;
	int i, j, k;
	double min_actuel;
	double challenger;
	double resultat;

	approx = malloc(nb_points * sizeof(double*));


	for(index_diag = 0; index_diag < nb_points-1; index_diag++) {	//initialisation de la première diagonale à C
		approx[index_diag] = malloc(nb_points * sizeof(double));
		approx[index_diag][index_diag+1] = C;
	}

	for (taille_diag = nb_points-2; taille_diag > 0; taille_diag--) { // on commence à la deuxième diagonale et chaque diagonale a une taille réduite de 1 par rapport à la précédente
		for(index_diag = 0; index_diag < taille_diag; index_diag++) {
			i = index_diag;
			j = index_diag+nb_points-taille_diag;

			// recherche du minimum : Min(k)(C+SD_ij, approx[i][k]+approx[k][j])
			min_actuel = C + distance(i,j,points);
			for(k = i+1; k < j; k++) {
				challenger = approx[i][k]+approx[k][j];
				if(challenger < min_actuel) {
					min_actuel = challenger;
				}
			}
			// mise à jour du tableau
			approx[i][j] = min_actuel;
		}
	}

	resultat = approx[0][nb_points-1];

	for(index_diag = 0; index_diag < nb_points-1; index_diag++) {	//libération de l'espace mémoire
		free(approx[index_diag]);
	}
	free(approx);

	return resultat;
}
