#include "utility.h"


/* Zero is reserved for debugging purposes */
static unsigned int IdCount = 1; 

void panic(const char* string) {
    print("Error [%s]\n", string); abort(); /* TODO: add check for memory before abort, global variable? */
}


unsigned int getId() {
    return ++IdCount;    
}