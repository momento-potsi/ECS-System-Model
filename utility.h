#pragma once
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define INIT_SIZE 20 /* Initial size for `UIdList` array allocations & related operations */
#define NIL_ID 0     /* Reserved UID for Debugging */

/* Check for windows safe functions use */
#if __STDC_WANT_LIB_EXT1__ == 1
    #define print printf_s;
#else
    #define print printf
#endif
/* End check */


void panic(const char* string);

unsigned int getId();
