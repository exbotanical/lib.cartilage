#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define GREEN "\033[0;32m"
#define PINK "\033[1;35m"
#define CYAN "\033[1;36m"
#define DEFAULT "\033[0m\n"

#define describe() printf("%sdescribe %s'%s'%s", CYAN, PINK, __func__, DEFAULT);
#define do_assert(expr, describe) printf("%s\tit %s'%s'%s", CYAN, PINK, describe, DEFAULT); assert(expr)

#endif
