#ifndef __MACROS_H__
#define __MACROS_H__

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_RESET    "\x1b[0m"

#endif // __MACROS_H__
