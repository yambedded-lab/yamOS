#/bin/sh
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

make all
$HOME/opt/cross/bin/$TARGET-gcc --version
