#include "overloads.h"

int overfprintf(FILE *restrict stream, const char *format, ...) {
	int count = 0;
	const char *p = format;
	va_list factor;
	va_start(factor, format);
	while (*p) {
		if (*p == '%') {
			p++;
			if (*p == '%') {
				count++;
			} else if (*p == 'R' && *(p + 1) == 'o') {
				break;
			} else if (*p == 'Z' && *(p + 1) == 'r') {
				break;
			} else if (*p == 'C' && *(p + 1) == 'v') {
				break;
			} else if (*p == 'C' && *(p + 1) == 'V') {
				break;
			} else if (*p == 't' && *(p + 1) == 'o') {
				break;
			} else if (*p == 'T' && *(p + 1) == 'O') {
				break;
			} else if (*p == 'm' && *(p + 1) == 'i') {
				break;
			} else if (*p == 'm' && *(p + 1) == 'u') {
				break;
			} else if (*p == 'm' && *(p + 1) == 'd') {
				break;
			} else {
				char tmp[SizeString(format)];
				if(str_to_k(&p, "%", tmp)) {
					va_end(factor);
					return -1;
				}
				char tmp_str[SizeString(format)];
				tmp_str[0] = '\0';
				my_strcat(tmp_str, "%");
				my_strcat(tmp_str, tmp);
				int n = vfprintf(stream, tmp_str, factor);
				if(n < 0){
					va_end(factor);
					return -1;
				}
				count += n;
				--p;
			}
		} else {
			fputc(*p, stream);
			count++;
			p++;
		}
	}
	va_end(factor);
	return count;
}

int oversprintf(char *str, const char *format, ...){

}
