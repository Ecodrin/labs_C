#include "../SystemErrors/errors.h"




int main(int argc, char ** argv){
    Error error;

    error = INPUT_FILE_ERROR;
    return print_error(error);

}