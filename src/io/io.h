#ifndef __IO_H__
#define __IO_H__
#include <stdint.h> 

uint8_t insb(uint16_t port);
uint16_t insw(uint16_t port);

void outb(uint16_t port, uint8_t value);
void outw(uint16_t port, uint16_t value);

#endif /* __IO_H__ */