#include "overloads.h"



int overfprintf(FILE * restrict stream, const char * format, ...){
	error_msg errorMsg;
	if(!stream){
		// Файл был не открыт
		return -1;
	}
    int count = 0;
	char s[SizeString(format)];
	do {
		errorMsg = str_to_k(&format, " ", s);
		if(errorMsg) return -1;
		//Проверяем что пробел не флаг
		if(string_cmp(s, "%")){
			char auxiliary_string[SizeString(format)];
			errorMsg = str_to_k(&format, " ", auxiliary_string);
			if(errorMsg) return -1;
			errorMsg = my_strcat(s, " ");
			if(errorMsg) return -1;
			errorMsg = my_strcat(s, auxiliary_string);
			if(errorMsg) return -1;
		}


		// Обработка форматов


	} while (SizeString(format) > 0);

	return count;
}