#include "ex2.h"

error_msg MaxVectors(Vector *** result, int n, int count_vectors, int count_norms, ...) {
    va_list factor;
    va_start(factor, count_norms);
    Vector vectors[count_vectors];
    for(int i = 0; i < count_vectors;++i){
        vectors[i] = va_arg(factor, Vector);
    }
    double vector_len;
    double max_vector_len;
    for(int i = 0;i < count_norms;++i){
        norm_func norm = va_arg(factor, norm_func);
        max_vector_len = -1.0;
        for(int j = 0; j < count_vectors;++j){
            if(norm == norm1){
                vector_len = norm(&vectors[j]);
            } else if(norm == norm2){
                int p = va_arg(factor, int);
                vector_len = norm(&vectors[j], p);
            } else if(norm == norm2){
                int p = va_arg(factor)
            }
        }
    }
}

double norm1(Vector *x) {
	double max_x = fabs(x->coords[0]);
	for (int i = 0; i < x->n; ++i) {
		if (fabs(x->coords[i]) > max_x) {
			max_x = fabs(x->coords[i]);
		}
	}
	return max_x;
}

double norm2(Vector *x, int p) {
	double sum = 0.0;
	for (int i = 0; i < x->n; i++) {
		sum += pow(fabs(x->coords[i]), p);
	}
	return pow(sum, 1.0 / p);
}

double norm3(Vector *x, double **matrix) {
	double sum = 0.0;
	for (int i = 0; i < x->n; i++) {
		for (int j = 0; j < x->n; j++) {
			sum += matrix[i][j] * x->coords[j] * x->coords[i];
		}
	}
	return sqrt(sum);
}