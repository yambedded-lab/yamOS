#ifndef __IDT_H__
#define __IDT_H__

#include <stdint.h>
/*
https://wiki.osdev.org/Interrupt_Descriptor_Table


*/

struct idt_desc{
    uint16_t offset_1;  // Offset bits 0 - 15.
    uint16_t selector;  // Selector thats in out GDT.
    uint8_t zero;       // Unused set to zero. 
    uint8_t type_attr;  // Descriptor type and attributes.
    uint16_t offset_2;  // Offset bits 16-31.

} __attribute__((packed));

struct  idtr_desc
{
    uint16_t limit;     // Size of descriptor table -1.
    uint32_t base;      // Base address of the start if the interrupt descriptor table. 
} __attribute__((packed));

void idt_init();

void enable_interrupt();
void disable_interrupt();

#endif /*__IDT_H__*/