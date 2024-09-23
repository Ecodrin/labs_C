#include "ex8.h"



int main(int argc, char ** argv){
    if(argc != 3){
        printf("Incorrect count args\n");
        return 1;
    }

    int error = to_numeral_system(argv);
    switch (error)
    {
    case 1:
        printf("Input file didn't open\n");
        return 1;
    case 2:
        printf("Output file fifn't open\n");
        return 1;
    case 3:
        printf("Memory allocation error\n");
		return 1;
    case 4:
        printf("An unrecognized character\n");
        return 1;
    default:
        break;
    }
    return 0;
}