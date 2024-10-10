#ifndef LAB2_OVERLOADS_H
#define LAB2_OVERLOADS_H

#include <stdarg.h>
#include <stdio.h>

#include "../SystemErrors/errors.h"
#include "../vector/stringvector.h"

int overfprintf(FILE * restrict stream, const char * format, ...);

int oversprintf(char *str, const char *format, ...);




#endif