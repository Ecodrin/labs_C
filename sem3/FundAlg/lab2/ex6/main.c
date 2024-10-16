#include "ex6.h"

int main(){

	int x = 0, y = 0, n;
	x = 0, y = 0;
	double s;
	FILE * f = stdin;
	n = overfscanf(f, "|||%d|||%d()%lf", &x, &y, &s);
	printf("n: %d x: %d y: %d s:|%f|\n", n, x, y, s);

	x = 0, y = 0;
	x = 0, y = 0;
	char ss[100];
	ss[0] = '\0';
	n = overfscanf(f, "|||%d|||%d()%lf %s", &x, &y, &s, ss);
	printf("n: %d x: %d y: %d s:|%f| ss:|%s|\n", n, x, y, s, ss);

	n = overfscanf(f, "%Ro", &x);
	printf("n: %d x:%d\n", n, x);

	unsigned int z = 0;
	n = overfscanf(f, "%Zr", &z);
	printf("n: %d x:%d\n", n, z);


	n = overfscanf(f, "%Cv", &x, 15);
	printf("n: %d x:%d\n", n, x);

	n = overfscanf(f, "%Cv", &x, 36);
	printf("n: %d x:%d\n", n, x);

	return 0;
}
