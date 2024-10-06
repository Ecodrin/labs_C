#ifndef LAB2_EX4_H
#define LAB2_EX4_H

#include <stdarg.h>

#include "../SystemErrors/errors.h"
#include "../vector/charvector.h"

typedef struct Point {
	double x;
	double y;
} Point;

int IsConvexPolygon(int n, ...);

double ValueOfPolynomial(double x, int n, ...);

error_msg FindNumbersKarper(int base, int n, ...);

#endif
