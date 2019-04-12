#include <stdio.h>
#include "Point.h"

void writeFile(char *filename, Point *points, int *usedPoints, int nb_points) {
	FILE *fp = fopen(filename, "w");
	int i;
	
	fprintf(fp, "%d\n", nb_points);
	for(i = 0; i < nb_points; i++) {
		fprintf(fp, "%d ", points[i].y);
		if(usedPoints[i]) {
			fprintf(fp, "%c\n", 'T');
		} else {
			fprintf(fp, "%c\n", 'F');
		}
	}
	
	fclose(fp);
}
