#include "ex9.h"



int get_boundaries(int argc, char ** argv, int * a, int * b){
    if(argc != 3)
        return 1;
    for(int i = 0; i < 2;++i){
        char * procceding_option = argv[i + 1];
        int number = 0, fl = 0;
        for (int j = 0; procceding_option[j]; ++j) {
			if (procceding_option[j] >= '0' && procceding_option[j] <= '9') {
			    number *= 10;
				number += procceding_option[j] - '0';
            }    
            else if(procceding_option[j] == '-') fl = 1; 
			else {
				return 1;
            }
		}
        if(fl) number *= -1;
        if(i == 0) *a = number;
        else *b = number;
    }
    return 0;
}

void print_mas(int * mas, int size){
    for(int i = 0; i < size; ++i){
        printf("%d ", mas[i]);
    }
    putc('\n', stdout);
}

void swap(int * a, int * b){
    int t = *a;
    *a = *b;
    *b = t;
}

int permutation_max_min(int * mas, int size){
    if(size == 0) return 0;
    int max_el = mas[0], index_max_el = 0;
    int min_el = mas[0], index_min_el = 0;
    for(int i = 0; i < size; ++i){
        if(mas[i] > max_el){
            max_el = mas[i];
            index_max_el = i;
        }
        if(mas[i] < min_el){
            min_el = mas[i];
            index_min_el = i;
        }
    }
    swap(&mas[index_max_el], &mas[index_min_el]);
    return 0;
}


int first_ex(int a, int b, int * mas, int size){
    for(int i = 0;i < size;++i){
        mas[i] = rand() % (b - a + 1) + a;
    }
    print_mas(mas, size);
    if(permutation_max_min(mas, size)){
        return 2;
    }
    print_mas(mas, size);

    return 0;
}


int second_ex(){
    IntVector * a;
    IntVector * b;
    IntVector * c;
    a = create_int_vector(rand() % (10000 - 10 + 1) + 10);  
    int error;
    for(int i = 0; i < a->capacity; ++i){
        error = push_end_intvector(a, rand() % 2001 - 1000);
        if(error)
            return error;
    }
    b = create_int_vector(rand() % (10000 - 10 + 1) + 10);
    for(int i = 0; i < b->capacity; ++i){
        error = push_end_intvector(b, rand() % 2001 - 1000);
        if(error)
            return error;
    }
    print_intvector(a);
    print_intvector(b);
    c = create_int_vector(1);


    for(int i = 0; i < size_intvector(a); ++i){
        int val = -2000;
        for(int j = 0; j < size_intvector(b); ++j){
            if(abs(get_intvector(a, i) - val) > abs(get_intvector(a, i) - get_intvector(b, j))){
                val = get_intvector(b, j);
            }
        }
        // printf("%d %d\n", get_intvector(a, i), val);
        push_end_intvector(c, get_intvector(a, i) + val);
    }
    print_intvector(c);
    destroy_int_vector(a);
    destroy_int_vector(b);
    destroy_int_vector(c);
    return 0;
}