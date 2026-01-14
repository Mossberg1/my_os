#!/bin/bash

set -xue

QEMU=qemu-system-riscv32

# Path to clang and compiler flags
CC=/opt/homebrew/opt/llvm/bin/clang  # Ubuntu users: use CC=clang
CFLAGS="-std=c11 -O2 -g3 -Wall -Wextra --target=riscv32-unknown-elf -fuse-ld=lld -fno-stack-protector -ffreestanding -nostdlib"

# Include paths for both kernel and libc headers
INCLUDES="-Isrc/kernel/includes -Isrc/libc/includes -I./src/kernel/arch/riscv/includes"

mkdir -p build/obj

# Build arch specific implementation.
# RISCV:
$CC $CFLAGS $INCLUDES -c -o build/obj/sbi.o src/kernel/arch/riscv/sbi.c
$CC $CFLAGS $INCLUDES -c -o build/obj/hal.o src/kernel/arch/riscv/hal.c
$CC $CFLAGS $INCLUDES -c -o build/obj/trap.o src/kernel/arch/riscv/trap.c
$CC $CFLAGS $INCLUDES -c -o build/obj/context.o src/kernel/arch/riscv/context.c

# Build kernel modules
$CC $CFLAGS $INCLUDES -c -o build/obj/console.o src/kernel/console/console.c
$CC $CFLAGS $INCLUDES -c -o build/obj/memory.o src/kernel/memory/memory.c
$CC $CFLAGS $INCLUDES -c -o build/obj/process.o src/kernel/process/process.c

# Build libk
$CC $CFLAGS $INCLUDES -c -o build/obj/kstring.o src/kernel/libk/kstring.c

# Build libc
$CC $CFLAGS $INCLUDES -c -o build/obj/stdio.o src/libc/stdio.c
$CC $CFLAGS $INCLUDES -c -o build/obj/string.o src/libc/string.c

# Build the kernel
$CC $CFLAGS $INCLUDES -Wl,-Tsrc/kernel/kernel.ld -Wl,-Map=build/kernel.map -o build/kernel.elf \
    src/kernel/kernel.c \
    build/obj/stdio.o \
    build/obj/string.o \
    build/obj/console.o \
    build/obj/kstring.o \
    build/obj/hal.o \
    build/obj/sbi.o \
    build/obj/trap.o \
    build/obj/context.o \
    build/obj/memory.o \
    build/obj/process.o

$QEMU -machine virt -bios default -nographic -serial mon:stdio --no-reboot \
    -kernel build/kernel.elf

