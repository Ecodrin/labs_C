
#ifndef LAB4_EX2_H
#define LAB4_EX2_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "../lib/SystemErrors/errors.h"
#include "../lib/vector/intvector.h"
#include "../lib/vector/charvector.h"



error_msg get_arr(IntVector** arrays, char c, IntVector** vec);
void destroy_arrays(IntVector ** arrays);


error_msg load_arr(IntVector ** arrays, char c, String * filename);

#endif  // LAB4_EX2_H
