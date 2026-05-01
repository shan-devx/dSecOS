CC      = i686-elf-gcc
LD      = i686-elf-ld
CFLAGS  = -ffreestanding -O2 -w -Iinclude -Idoomgeneric -I/home/shan/opt/cross/lib/gcc/i686-elf/14.1.0/include -fno-builtin 
LDFLAGS = -m elf_i386 -T kernel/linker.ld --oformat binary -nostdlib /home/shan/opt/cross/lib/gcc/i686-elf/14.1.0/libgcc.a 

C_SRCS  := $(wildcard kernel/*.c)
ASM_SRCS := $(wildcard kernel/*.asm)
LIBC_SRCS := $(wildcard libc/*.c)
DOOM_SRCS := $(wildcard doomgeneric/*.c)
OBJS    := $(C_SRCS:.c=.o) $(ASM_SRCS:.asm=.o) $(LIBC_SRCS:.c=.o) $(DOOM_SRCS:.c=.o) 

all: disk.img

boot.bin: boot/boot.asm
	nasm -f bin $< -o $@

stage2.bin: boot/stage2.asm
	nasm -f bin $< -o $@

kernel/%.o: kernel/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

kernel/%.o: kernel/%.asm
	nasm -f elf32 $< -o $@

libc/%.o: libc/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

doomgeneric/%.o: doomgeneric/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

kernel.bin: $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

disk.img: boot.bin stage2.bin kernel.bin
	cat $^ > $@
	truncate -s +1M $@

run: disk.img
	qemu-system-i386 -drive file=disk.img,format=raw,index=0,media=disk

clean:
	rm -f boot.bin stage2.bin kernel.bin kernel/*.o disk.img libc/*.o doomgeneric/*.o
