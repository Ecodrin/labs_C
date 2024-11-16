#include "utility.h"



error_msg char_to_int(const char * src, int *result){
    *result = 0;
    int fl = 0;
    for(int i = 0; src[i];++i){
        if(src[i] == '-' && !fl){
            fl = 1;
        } else if(src[i] >= '0' && src[i] <= '9'){
            if(*result * 10 + (src[i] - '0') < 0){
                error_msg errorMsg ={OVERFLOW_ERROR, "Error - char_to_int: overflow int"};
                return errorMsg;
            }
            *result = *result * 10 + (src[i] - '0');
        } else{
            error_msg errorMsg ={INCORRECT_OPTIONS_ERROR, "Error - char_to_int: unrecognized character"};
            return errorMsg;
        }
    }
    if(fl){
        *result *= -1;
    }

    error_msg errorMsg = {SUCCESS, ""};
    return errorMsg;
}