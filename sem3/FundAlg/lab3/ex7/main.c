#include "ex7.h"



int main(){
    String filename;
    error_msg errorMsg = create_string(&filename, "");
    if(errorMsg){
        return print_error(errorMsg);
    }

    printf("Write name of input file: ");
    read_string(stdin, &filename);
    FILE * in = fopen(filename.arr, "r");
    if(!in){
		destroy_string(&filename);
        return print_error(INPUT_FILE_ERROR);
    }
	Node * head = NULL;
	errorMsg = read_livers_from_file(in, &head);
	if(errorMsg){
		fclose(in);
		destroy_string(&filename);
		return print_error(errorMsg);
	}
	print_LinkedList(stdout, head, "\n");

	Liver liv, liv2;
	errorMsg = create_liver(&liv);
	read_liver(stdin, &liv);
	errorMsg = create_liver(&liv2);
	read_liver(stdin, &liv2);
	errorMsg = change_liver(&head, &liv, &liv2);
	if(errorMsg){
		destroy_LinkedList(head);
		destroy_string(&filename);
		fclose(in);
		return print_error(errorMsg);
	}
	print_LinkedList(stdout, head, "\n");

	printf("\n\n\n\n\n\n");
	print_liver(stdout, &liv);




	destroy_LinkedList(head);
	destroy_liver(&liv);
	destroy_string(&filename);
	fclose(in);

	return 0;
}