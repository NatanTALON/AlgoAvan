#include <stdlib.h>
#include <stdio.h>
#include "Point.h"


int parser(char *filename, Point* *points, int *nb_points) {
	FILE *fp;
	int x,y;
	
	fp = fopen(filename,"r");
	if(fp == NULL) {
		printf("Erreur : impossible de lire le fichier\n");
		return 1;
	}
	fscanf(fp, "%d", nb_points);
	if(*nb_points < 2) {
		printf("Erreur: le format de fichier est invalide.\nLa première ligne doit indiquer le nombre de points dans le fichier\n");
		return 1;
	}
	
	*points = (Point*)malloc((*nb_points)*sizeof(Point));
	
	int i = 0;
	while(i < *nb_points) {
		if(fscanf(fp, "%d", &x) == EOF || fscanf(fp, "%d", &y) == EOF) {
			printf("Erreur : le format de fichier est invalide.\nTous les points ne sont pas correctement renseignés\n");
			return 1;
		}
		(*points)[i].x = x;
		(*points)[i].y = y;
		printf("{%d, %d}\n", (*points)[i].x, (*points)[i].y);
		i++;
	}
	
	fclose(fp);
	return 0;
}
