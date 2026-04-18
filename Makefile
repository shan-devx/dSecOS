all: disk.img

boot.bin: boot/boot.asm
	nasm -f bin boot/boot.asm -o boot.bin

stage2.bin: boot/stage2.asm
	nasm -f bin boot/stage2.asm -o stage2.bin

kernel.o: kernel/main.c
	i686-elf-gcc -c kernel/main.c -o kernel.o -ffreestanding -O2 -Wall -Wextra

idt.o: kernel/idt.c
	i686-elf-gcc -c kernel/idt.c -o idt.o -ffreestanding -O2 -Wall -Wextra

load_idt.o: kernel/load_idt.asm
	nasm -f elf32 kernel/load_idt.asm -o load_idt.o

kernel.bin: kernel.o idt.o load_idt.o
	ld -m elf_i386 -T kernel/linker.ld --oformat binary -o kernel.bin kernel.o idt.o load_idt.o

disk.img: boot.bin stage2.bin kernel.bin
	cat boot.bin stage2.bin kernel.bin > disk.img

run: disk.img
	qemu-system-i386 -drive file=disk.img,format=raw,index=0,media=disk

clean:
	rm -f *.bin *.o disk.img
