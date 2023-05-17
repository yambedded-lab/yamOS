#! /bin/sh
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

make all

#$HOME/opt/cross/bin/$TARGET-gcc --version



#gdb 
#add-symbol-file ../build/kernelfull.o 0x100000
#break _start
#target remote | qemu-system-x86_64 -S -gdb stdio -hda ./os.bin 