CC      = i686-elf-gcc
LD      = i686-elf-ld
CFLAGS  = -ffreestanding -O2 -Wall -Wextra -Iinclude
LDFLAGS = -m elf_i386 -T kernel/linker.ld --oformat binary

C_SRCS  := $(wildcard kernel/*.c)
ASM_SRCS := $(wildcard kernel/*.asm)
OBJS    := $(C_SRCS:.c=.o) $(ASM_SRCS:.asm=.o)

all: disk.img

boot.bin: boot/boot.asm
	nasm -f bin $< -o $@

stage2.bin: boot/stage2.asm
	nasm -f bin $< -o $@

kernel/%.o: kernel/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

kernel/%.o: kernel/%.asm
	nasm -f elf32 $< -o $@

kernel.bin: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

disk.img: boot.bin stage2.bin kernel.bin
	cat $^ > $@

run: disk.img
	qemu-system-i386 -drive file=disk.img,format=raw,index=0,media=disk

clean:
	rm -f boot.bin stage2.bin kernel.bin kernel/*.o disk.img
