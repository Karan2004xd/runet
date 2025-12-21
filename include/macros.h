#ifndef __MACROS_H__
#define __MACROS_H__

#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)
#define ARRAY_INDEX(i, j, cols) ((i * cols) + j)

#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_RESET    "\x1b[0m"

#define CHECK_INT(a, R, b) \
  ((a R b) ? 1 : (printf("Expected: %d %s %d\n", (a), #R, (b)), 0))

#define CHECK_FLOAT(a, R, b) \
  ((a R b) ? 1 : (printf("Expected: %f %s %f\n", (a), #R, (b)), 0))

#define CHECK_PTR(a, R, b) \
  ((a R b) ? 1 : (printf("Expected: %p %s %p\n", (a), #R, (b)), 0))

#define CHECK_STRING(a, R, b) \
  ((strcmp(a, b) R 0) ? 1 : (printf("Expected: %s %s %s\n", (a), #R, (b)), 0))

#endif // __MACROS_H__
