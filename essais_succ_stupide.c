#include <stdlib.h>
#include <stdio.h>
#include "Point.h"
#include "parser.h"
#include "distance.h"
#include "writer.h"
#include <time.h>


void appligbri(int i, int dernierPointAccepte);

Point *points = NULL;
int nb_points = 0;
int *Xopt;
int *X;
int nb1dansX = 1;
double C = 1.5;
double Copt;
double Cact = 0.0;


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
		Xopt[0] = 1;
		int j;
		for(j = 1; j < nb_points-1; j++) {
			Xopt[j] = 0;
		}
		Xopt[nb_points-1] = 1;
		X = malloc(nb_points * sizeof(int));
		X[0] = 1;
		X[nb_points-1] = 1;
		Copt = C + distance(0, nb_points-1, points);
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
	FILE *timeFile = fopen("timesEssaisSuccStupide.txt","a");
	fprintf(timeFile, "%f\n", temps);
	fclose(timeFile);

	return 0;
}


void appligbri(int i, int dernierPointAccepte) {
	if(i < nb_points) {
		X[i] = 1;
		nb1dansX++;
		Cact += distance(dernierPointAccepte, i, points);

		if(i == nb_points-1 && Cact + C*(nb1dansX-1) < Copt) {
      		Copt = Cact + C*(nb1dansX-1);
			int j;
			for(j = 0; j < nb_points; j++) {
        		//printf("%d, ", X[j]);
				Xopt[j] = X[j];
			}
		} else {
			appligbri(i+1, i);
		}

		X[i] = 0;
		nb1dansX--;
		Cact -= distance(dernierPointAccepte, i, points);
		appligbri(i+1, dernierPointAccepte);
	}
}
