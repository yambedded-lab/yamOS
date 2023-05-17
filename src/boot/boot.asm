ORG 0
BITS 16
;boot parameter block writes 33 bytes of data on some BIOS. so to avoid corruption of our data:
_start:
    jmp short start
    nop
  times 33 db 0


handle_zero:
    mov ah, 0eh 
    mov al, 'A'
    int 0x10
    iret 

start:
    jmp 0x7c0:start2
start2:
    cli             ; Clear Interrupts
    mov ax, 0x7c0
    mov ds, ax      ; Set Data Segment 
    mov es, ax      ; Set Extra Segment
    mov ax, 0x00
    mov ss, ax      ; Set Stack Segment
    mov sp, 0x7c00  ; Set Stack Pointer. 
    sti             ; Eables the Interrupt. 

    ; overwrite handler for interrupt zero.
    mov word[ss:00], handle_zero    ; offset for the interrupt.
    mov word[ss:02], 0x7C0          ; segment

    int 0           ; interrupt 0-> calls the ISR. 
    
    ;point si to first character in message. 
    mov si, message
    call print
    jmp $

print:
    mov bx, 0

.loop:
    lodsb
    cmp al, 0
    je .done
    call print_char
    jmp .loop

.done:
    ret

print_char:
    mov ah, 0eh
    int 0x10
    ret

message: db 'Hello From YamOS!', 0

times 510-($ - $$) db 0
dw 0xAA55