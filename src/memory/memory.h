#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stddef.h>

/**
 * Function to set memory location from *ptr to *(ptr + size) to a value of c.
 * 
*/
void* memset(void * ptr, int c, size_t size);


#endif /*__MEMORY_H__*/