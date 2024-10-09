#include "overloads.h"



///%[flags][width][.precision][length]specifier
int overfprintf(FILE * restrict stream, const char * format, ...){
	if(!stream){
		// Файл был не открыт
		return -1;
	}
    int count = 0;

}