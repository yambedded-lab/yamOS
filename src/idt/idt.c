#include "idt.h"
#include "config.h"
#include "memory/memory.h"
#include "kernel.h"

struct idt_desc idt_descriptors[YAMOS_TOTAL_INTERRUPTS];
struct idtr_desc idtr_descriptor;

/**
 * ASM function defined in idt.asm file. 
 * To load idt table into memory.
*/
extern void idt_load(struct idtr_desc * ptr);

/**
 * ISR for interrupt.
*/
void idt_zero(){
    print("Divide by zero error\n");

}

/**
 * Initialize particular interrupt.
*/
void idt_set(int interrupt_no,void * address){
    struct idt_desc* desc = &idt_descriptors[interrupt_no];
    desc->offset_1 = (uint32_t)address & 0x0000ffff;
    desc->selector = KERNEL_CODE_SELECTOR;
    desc->zero = 0x00;
    desc->type_attr = 0xEE; 
    desc->offset_2 = (uint32_t)address >> 16;
}

/**
 * Initialize the interrupt descriptors.
*/
void idt_init(){
    /*Set idt_descriptors to value 0 */
    memset(idt_descriptors, 0 , sizeof(idt_descriptors) );
    /*Set idtr_descriptor */
    idtr_descriptor.limit = sizeof(idt_descriptors) -1;
    idtr_descriptor.base = (uint32_t)idt_descriptors;

    // Set pointer to interrupt number 0. 
    //idt_zero function will be called on divide by zero error. 
    idt_set(0, idt_zero);

    //load the interrupt descriptor table.
    idt_load( &idtr_descriptor);
}