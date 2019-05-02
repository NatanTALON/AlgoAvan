#include <stdlib.h>
#include <stdio.h>
#include "Point.h"
#include "parser.h"
#include "distance.h"
#include "writer.h"
#include <time.h>


void appligbri();

Point *points = NULL;
int nb_points = 0;
int *Xopt;
int *X;
int nb1dansX = 1;
double C = 1.5;
double Copt = 0.0;


int main(int argc, char* argv[]) {
	float temps;
	clock_t t1,t2;
	t1 = clock();
	if(argc < 2) {
		printf("Erreur : veuillez spécifier le fichier à lire\n");
		return 0;
	} else if (argc == 3) {
		C = atof(argv[2]);
		//printf("C = %f\n", C);
	}

	parser(argv[1], &points, &nb_points);

	if(nb_points > 2) {
		Xopt = malloc(nb_points * sizeof(int));
    X = malloc(nb_points * sizeof(int));
		Xopt[0] = 1;
    X[0] = 1;
		int j;
		for(j = 1; j < nb_points-1; j++) {
      if (j%2 == 0) {
        Xopt[j] = 1;
        X[j] = 1;
        Copt += C + distance(j-2, j, points);
      } else {
			  Xopt[j] = 0;
        X[j] = 0;
      }
		}
		Xopt[nb_points-1] = 1;
		X[nb_points-1] = 1;
    if (X[nb_points-2] == 1) {
      Copt += C;
    } else {
      Copt += C + distance(nb_points-3, nb_points-1, points);
    }
	} else {
		printf("Erreur lors de la lecture du fichier\n");
		return 0;
	}

	appligbri(1, 0);

	//printf("\nCopt = %f\n", Copt);

	writeFile("test_python.txt", points, Xopt, nb_points);

	free(points);
	free(Xopt);
	free(X);

	t2 = clock();
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	FILE *timeFile = fopen("timesEssaiSucc1Sur2.txt","a");
	fprintf(timeFile, "%f\n", temps);
	fclose(timeFile);

	return 0;
}

int point_suivant(int i) {
	while (!X[++i]);
	return i;
}

int point_precedent(int i) {
	while (!X[--i]);
	return i;
}

void appligbri() {
  int sol_changed = 1;
  int i;
	double C_challenger;

  while (sol_changed) {
    sol_changed = 0;
    for (i = 1; i < nb_points-1; i++) {
      if(X[i] == 1) {
				C_challenger = Copt - C - distance(point_precedent(i), i, points) - distance(i, point_suivant(i), points) + distance(point_precedent(i), point_suivant(i), points);
				if(C_challenger < Copt) {
					X[i] = 0;
					Copt = C_challenger;
					sol_changed = 1;
				}
      } else {
				C_challenger = Copt + C + distance(point_precedent(i), i, points) + distance(i, point_suivant(i), points) - distance(point_precedent(i), point_suivant(i), points);
				if( C_challenger < Copt) {
        	X[i] = 1;
					Copt = C_challenger;
        	sol_changed = 1;
				}
      }
    }
  }
}
