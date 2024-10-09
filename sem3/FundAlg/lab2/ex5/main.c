#include "overloads.h"


int main(){
    // TODO дописать str_to_k
    char * a = "hello ,. world ,. dfsfsf sdfd. dfdf ./sad";
    char s[SizeString(a)];
    while(str_to_k(&a, " ,. ", s) == NORMAL != 0){
        printf("%s\n", s);
    }

}