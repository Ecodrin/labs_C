#include "ex4.h"

int main()
{
	StringVector *vec = create_string_vector(1);
	error_msg error = FindNumbersKarper(vec, 16, 4, "1", "BB", "56", "66");;
	if(error){
		return print_error(error);
	}

	for(int i = 0; i < vec->size; ++i){
		printf("%s\n", vec->data[i]);
	}
	destroy_string_vector(vec);

}

