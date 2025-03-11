#pragma once

#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <time.h>

#include "../libs/CustomErrors/errors.h"

error_msg processing_catalog(const char* catalog_name);
error_msg processing_file(const char* file_name, char* result);