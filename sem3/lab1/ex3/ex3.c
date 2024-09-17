#include "ex3.h"

int GetOpts(int argc, char** argv, kOpts* option, double* numbers) {
	if (argc != 6 && argc != 4) {
		return 1;
	}
	int count_numbers;
	if (argv[1][0] == '/' || argv[1][0] == '-') {
		switch (argv[1][1]) {
			case 'q':
				*option = OPT_Q;
				count_numbers = 4;
				break;
			case 'm':
				*option = OPT_M;
				count_numbers = 2;
				break;
			case 't':
				*option = OPT_T;
				count_numbers = 4;
				break;
			default:
				return 1;
		}
		CharToDouble(argv, numbers, count_numbers);
	}
	return 0;
}

void CharToDouble(char ** argv, double * numbers, int count_numbers){
	int k = -1;
	int fl = 0;
	for (int i = 0; i < count_numbers; ++i) {
		fl = 0;
		for (int j = 0; argv[i + 2][j] != '\0'; ++j) {
			if (argv[i + 2][j] == '-') fl = 1;
			if (argv[i + 2][j] >= '0' && argv[i + 2][j] <= '9') {
				numbers[i] *= 10;
				numbers[i] += (argv[i + 2][j] - '0');
				if (k != -1) k += 1;
			} else if (argv[i + 2][j] == '.')
				k = 0;
		}
		for (int k_null = 0; k_null < k; ++k_null) numbers[i] /= 10.0;
		k = -1;
		if (fl) numbers[i] *= -1;
		// putchar('\n');
		// printf("%f\n", numbers[i]);
	}
}

int compare_values(double a, double b, double eps) {
	if (fabs(b - a) < eps) return 0;
	if (b - a > eps) return 2;
	return 1;
}

void solving_quadratic_equations(double a, double b, double c, double eps) {
	double discriminant, x1, x2;
	discriminant = b * b - 4 * a * c;
	if (discriminant > eps) {
		x1 = (-b + sqrt(discriminant)) / (2 * a);
		x2 = (-b - sqrt(discriminant)) / (2 * a);
		printf("Уравнение %f*x^2 + %f*x + %f == 0 имеет решения: %f %f\n", a, b, c, x1, x2);
	} else if (fabs(discriminant) < eps) {
		x1 = -b / (2 * a);
		printf("Уравнение %f*x^2 + %f*x + %f == 0 имеет решениe: %f\n", a, b, c, x1);
	} else {
		printf("Уравнение %f*x^2 + %f*x + %f == 0 не имеет решений\n", a, b, c);
	}
}

void HandlerOptQ(double* numbers) {
	double eps = numbers[0];
	double a = numbers[1], b = numbers[2], c = numbers[3];
	if (compare_values(a, b, eps) != 0 && compare_values(b, c, eps) != 0) {
		solving_quadratic_equations(a, b, c, eps);
		solving_quadratic_equations(a, c, b, eps);
		solving_quadratic_equations(b, a, c, eps);
		solving_quadratic_equations(c, b, a, eps);
		solving_quadratic_equations(b, c, a, eps);
		solving_quadratic_equations(c, a, b, eps);
	} else if (compare_values(a, b, eps) == 0 && compare_values(b, c, eps) != 0) {
		solving_quadratic_equations(a, b, c, eps);
		solving_quadratic_equations(a, c, b, eps);
		solving_quadratic_equations(c, b, a, eps);
	} else if (compare_values(a, b, eps) != 0 && compare_values(b, c, eps) == 0) {
		solving_quadratic_equations(a, b, c, eps);
		solving_quadratic_equations(b, a, c, eps);
		solving_quadratic_equations(c, b, a, eps);
	} else {
		solving_quadratic_equations(a, b, c, eps);
	}
}

void HandlerOptM(double* numbers) {
	int a = numbers[0];
	int b = numbers[1];
	if (a % b == 0)
		printf("Число %d кратно числу %d\n", a, b);

	else
		printf("Число %d не кратно числу %d\n", a, b);
}

void HandlerOptT(double* numbers) {
	double eps = numbers[0], maxc = numbers[1], minc = numbers[2];
	for (int i = 1; i <= 3; ++i) {
		if (compare_values(numbers[i], maxc, eps) == 1) maxc = numbers[i];
		if (compare_values(numbers[i], minc, eps) == 2) minc = numbers[i];
	}
	double b = numbers[1] + numbers[2] + numbers[3] - minc - maxc;
	if (compare_values(minc + b, maxc, eps) == 1)
		printf("Треугольник со сторонами %f %f %f  может существовать\n", minc, maxc, b);
	else
		printf("Треугольник со сторонами %f %f %f  не может существовать\n", minc, maxc, b);
}