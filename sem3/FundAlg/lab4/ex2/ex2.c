#include "ex2.h"

error_msg get_arr(IntVector** arrays, char c, IntVector** vec) {
	if (c < 'A' || c > 'Z') {
		return INCORRECT_OPTIONS_ERROR;
	}
	int index = c - 'A';
	if (arrays[index]) {
		*vec = arrays[index];
	} else {
		error_msg errorMsg = create_int_vector(vec, 1);
		arrays[index] = *vec;
		if (errorMsg) {
			return errorMsg;
		}
	}
	return SUCCESS;
}

void destroy_arrays(IntVector** arrays) {
	for (int i = 0; i < 26; ++i) {
		if (arrays[i]) {
			destroy_int_vector(arrays[i]);
		}
	}
}


error_msg load_arr(IntVector** arrays, char c, String* filename) {
	IntVector* vector;
	error_msg errorMsg = get_arr(arrays, c, &vector);
	if (errorMsg) {
		return errorMsg;
	}

	FILE* stream = fopen(filename->arr, "r");
	if (!stream) {
		return INPUT_FILE_ERROR;
	}

	int d;
	String tmp;
	errorMsg = create_string(&tmp, "");
	if(errorMsg){
		fclose(stream);
		return errorMsg;
	}
	while (!feof(stream)) {
		read_string(stream, &tmp);

		errorMsg = string_to_int(&tmp, &d);
		if(errorMsg){
			fclose(stream);
			destroy_string(&tmp);
			return errorMsg;
		}

		errorMsg = push_end_intvector(vector, d);
		if (errorMsg) {
			fclose(stream);
			destroy_string(&tmp);
			return errorMsg;
		}
	}



	destroy_string(&tmp);
	fclose(stream);
	return SUCCESS;
}

error_msg read_command(FILE * stream, String * command){
	clear_string(command);
	char c;
	while ((c = getc(stream)) != EOF && c != ';' && (c == ' ' || c == '\t' || c == '\n'));

	error_msg errorMsg;
	while ((c = getc(stream)) != EOF && c != ';'){
		errorMsg = push_end_string(command, c);
		if(errorMsg){
			return errorMsg;
		}
	}
	return SUCCESS;
}