#include "kernel.h"
#include "idt/idt.h"
#include "io/io.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"

#include <stdint.h> 
#include <stddef.h>

uint16_t * video_mem = 0;
static int terminal_col=0;
static int terminal_row=0;
static struct paging_4gb_chunk* kernel_chunk =0;

/*Convert to CHAR & color to ASCII to output to video output*/
uint16_t terminal_make_char(char c, char color){
    return (color << 8) | c;
}

/* put a char with specific color at position x,y */
void terminal_putchar(int x, int y, char c, char color){
    video_mem[ (y* VGA_WIDTH) + x] = terminal_make_char(c,color);    
}

void terminal_writechar(char c, char color){
    if(c == '\n'){
        terminal_col=0;
        terminal_row+=1;
        return;
    }
    terminal_putchar(terminal_col, terminal_row, c, color);

    terminal_col+=1;

    if(terminal_col >= VGA_WIDTH){
        terminal_col =0;
        terminal_row += 1;
    }
    
}
/*Clear the terminal and initialize video memory.*/
void terminal_initialize(){
    video_mem = (uint16_t*)(0xB8000);

    for(int h =0; h < VGA_HEIGHT; h++){
        for(int w =0; w < VGA_WIDTH; w++ ){
           terminal_putchar(w,h,' ', 0);
        }
    }
}
/*Calculate the length of the char array*/
size_t strlen(const char *s){
    size_t len =0;
    while(s[len]){
        ++len;
    }

    return len;

}

void print(const char *s){
    size_t size = strlen(s);
    for(int i=0 ; i< size; i++){
        terminal_writechar(s[i] , 15);
    }
}


void kernel_main(){
    terminal_initialize();
    print("HELLO \n world...!!!\n");
    //Initilize the heap.
    kheap_init();

    //Initialize the interrupt descriptor table. 
    idt_init();

    //Setup PAGING.
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);

    //Switch to kernel paging chunk
    paging_switch(paging_4gb_chunk_get_directory(kernel_chunk));

    //Enable Paging;
    enable_paging();

    //enable interrupts after initalizing the inerrtupt descriptor table.
    enable_interrupt();
    

    outb(0x60, 0xff);
}