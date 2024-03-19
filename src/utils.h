#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include "../lib/C-Personal-Utils/types.h"

// THANKS jdh for this awesome trick
#define ERROR_EXIT(...) fprintf(stderr, __VA_ARGS__); exit(1)
#define ERROR_RETURN(R, ...) fprintf(stderr, __VA_ARGS__); return R

#endif
