#include <stdlib.h>
#include <stdio.h>
#include "Point.h"
#include "case_s.h"
#include "parser.h"
#include "distance.h"
#include "writer.h"


double dyn();

Point *points = NULL;
int nb_points = 0;
int *Xopt;
double C = 1.5;


int main(int argc, char* argv[]) {
	if(argc < 2) {
		printf("Erreur : veuillez spécifier le fichier à lire\n");
		return 0;
	} else if (argc == 3) {
		C = atof(argv[2]);
		printf("C = %f\n", C);
	}

	parser(argv[1], &points, &nb_points);

	if(nb_points > 2) {
		Xopt = malloc(nb_points * sizeof(int));
		Xopt[0] = 1;
		Xopt[nb_points-1] = 1;
		int j;
		for(j = 1; j < nb_points-1; j++) {
			Xopt[j] = 0;
		}
	} else {
		printf("Erreur lors de la lecture du fichier\nIl doit contenir au moins 3 points\n");
		return 0;
	}
	// appel à dyn pour calculer par approche dynamique la solution optimale
	printf("\nCout optimal = %f\n", dyn());

	writeFile("test_python.txt", points, Xopt, nb_points);

	free(points);
	free(Xopt);

	return 0;
}


/**
 *	Fonction qui calcule le coup optimal de la solution à l'aide d'une approche dynamique.
 *	Cette fonction rempli aussi le tableau des points choisis pour créer la solution optimale.
 */
double dyn() {
	case_s approx[nb_points][nb_points];
	int index_diag;
	int taille_diag;
	int i, j, k;
  int num_point_ajout;
	double min_actuel;
	double challenger;
  int pile_chemin[nb_points*nb_points];
  int sommet = -1;
  int cut;

	printf("\nRemplissage du tableau des couts...\n");
	for(index_diag = 0; index_diag < nb_points-1; index_diag++) {	//initialisation de la première diagonale à C
		(approx[index_diag][index_diag+1]).valeur = C;
    (approx[index_diag][index_diag+1]).cut = -1;
	}

	for (taille_diag = nb_points-2; taille_diag > 0; taille_diag--) { // on commence à la deuxième diagonale et chaque diagonale a une taille réduite de 1 par rapport à la précédente
		for(index_diag = 0; index_diag < taille_diag; index_diag++) {
			i = index_diag;
			j = index_diag+nb_points-taille_diag;
			num_point_ajout =  -1;

			// recherche du minimum : Min(k)(C+SD_ij, approx[i][k]+approx[k][j])
			min_actuel = C + distance(i,j,points);
			for(k = i+1; k < j; k++) {
				challenger = (approx[i][k]).valeur + (approx[k][j]).valeur;
				if(challenger < min_actuel) {
					min_actuel = challenger;
          num_point_ajout = k;
				}
			}
			// mise à jour du tableau
			(approx[i][j]).valeur = min_actuel;
			// ajout du point pris si il existe
			if(num_point_ajout != -1) {
        (approx[i][j]).cut = num_point_ajout;
			} else {
        (approx[i][j]).cut = -1;
      }
		}
	}

  // remplissage de Xopt : on remonte la chaine des points pris depuis la case 0,n-1
	printf("\nRemplissage de Xopt ...\n");
  i = 0;
  j = nb_points-1;
	pile_chemin[++sommet] = (approx[i][j]).cut;;
//	printf("\ncut a : %d\n", (approx[i][cut]).cut);
//	printf("\ncut a : %d\n", (approx[cut][j]).cut);
  while(sommet >= 0 && sommet < nb_points*nb_points) {
  		printf("Sommet = %d\n", sommet);
		cut = pile_chemin[sommet--];
		if(cut != -1) {
			Xopt[cut] = 1;
			pile_chemin[++sommet] = (approx[i][cut]).cut;
			pile_chemin[++sommet] = (approx[cut][j]).cut;
		}
  }

	return (approx[0][nb_points-1]).valeur;
}
