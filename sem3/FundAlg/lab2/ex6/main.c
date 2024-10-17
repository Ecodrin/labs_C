#include "ex6.h"


int main(){

	int x = 0, y = 0, n;
	x = 0, y = 0;
	double s;
	FILE * f = fopen("test", "r");
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

	n = overfscanf(f, "%CV", &x, 19);
	printf("n: %d x:%d\n", n, x);

	n = overfscanf(f, "%CV", &x, 25);
	printf("n: %d x:%d\n", n, x);


	char buffer1[1000] = "|||12|||13()12.24343";

	putc('\n', stdout);
	x = 0, y = 0, s = 0.0;
	n = oversscanf(buffer1, "|||%d|||%d()%lf", &x, &y, &s);
	printf("n: %d x: %d y: %d s:|%f|\n", n, x, y, s);

	x = 0, y = 0;
	x = 0, y = 0;
	z = 0;
	char buffer2[1000] = "|||12|||13()12.24343 sdf";
	n = oversscanf(buffer2, "|||%d|||%d()%lf %s", &x, &y, &s, ss);
	printf("n: %d x: %d y: %d s:|%f| ss:|%s|\n", n, x, y, s, ss);

	char buffer3[1000] = "MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMCMXCIX";
	n = oversscanf(buffer3, "%Ro", &x);
	printf("n: %d x:%d\n", n, x);

	char buffer4[1000] = "00100100000001001";
	n = oversscanf(buffer4, "%Zr", &z);
	printf("n: %d x:%d\n", n, z);

	char buffer5[100] = "-abcd";
	n = oversscanf(buffer5, "%Cv", &x, 15);
	printf("n: %d x:%d\n", n, x);

	char buffer6[100] = "s1234";
	n = oversscanf(buffer6, "%Cv", &x, 36);
	printf("n: %d x:%d\n", n, x);

	char buffer7[100] = "39HA20";
	n = oversscanf(buffer7, "%CV", &x, 19);
	printf("n: %d x:%d\n", n, x);

	char buffer8[100] = "-M847C";
	n = oversscanf(buffer8, "%CV", &x, 25);
	printf("n: %d x:%d\n", n, x);
	return 0;
}
