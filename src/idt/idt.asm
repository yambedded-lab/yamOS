section .asm

extern int21h_handler
extern no_interrupt_handler

global idt_load
global int21h
global no_interrupt
global enable_interrupt
global disable_interrupt

enable_interrupt: 
    sti
    ret
disable_interrupt: 
    cli
    ret

idt_load:
    push ebp
    mov ebp, esp

    mov ebx, [ebp + 8]
    lidt [ebx]
    
    pop ebp
    ret

;handler to handle interrupt 21.
int21h:
    cli
    pushad
    call int21h_handler
    popad
    sti 
    iret

no_interrupt:
    cli
    pushad
    call no_interrupt_handler
    popad
    sti
    iret
