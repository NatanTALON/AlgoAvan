#include <math.h>
#include "Point.h"

double distancePD(double a, double b, Point P) {
	double x = (double)P.x;
	double y = (double)P.y;
	
	double d = y-a*x-b;
	if(d < 0.0) {
		d = -d;
	}
	
	d = d/sqrt(1.0+a*a);
	return d;
}


void equationDroite(Point P1, Point P2, double *a, double *b) {
	*a = (P1.y - P2.y) / (double)(P1.x - P2.x);
	*b = P1.y - (*a) * P1.x;
}


double distance(int numPoint1, int numPoint2, Point *points) {
	double a = 0.0;
	double b = 0.0;
	
	equationDroite(points[numPoint1], points[numPoint2], &a, &b);
	
	int i;
	double SD = 0.0;
	for(i = numPoint1+1; i < numPoint2; i++) {
		SD += distancePD(a, b, points[i]);
	}
	
	return SD;
}
