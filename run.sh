#!/bin/bash

set -xue

QEMU=qemu-system-riscv32

# Path to clang and compiler flags
CC=/opt/homebrew/opt/llvm/bin/clang  # Ubuntu users: use CC=clang
CFLAGS="-std=c11 -O2 -g3 -Wall -Wextra --target=riscv32-unknown-elf -fuse-ld=lld -fno-stack-protector -ffreestanding -nostdlib"

# Include paths for both kernel and libc headers
INCLUDES="-Isrc/kernel/includes -Isrc/libc/includes"

mkdir -p build/obj

# Build libc
$CC $CFLAGS $INCLUDES -c -o build/obj/stdio.o src/libc/stdio.c
$CC $CFLAGS $INCLUDES -c -o build/obj/string.o src/libc/string.c

# Build the kernel
$CC $CFLAGS $INCLUDES -Wl,-Tsrc/kernel/kernel.ld -Wl,-Map=build/kernel.map -o build/kernel.elf \
    src/kernel/kernel.c build/obj/stdio.o build/obj/string.o

$QEMU -machine virt -bios default -nographic -serial mon:stdio --no-reboot \
    -kernel build/kernel.elf