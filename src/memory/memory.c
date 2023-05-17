#include "memory.h"



void* memset(void * ptr, int value, size_t size){
    // cast void * to char *
    // iterate over char * and set value to (char)value.  

    char * p = (char *) ptr;
    for(int i=0; i<size; ++i){
        p[i] = (char)(value);
    }

    return ptr;
}