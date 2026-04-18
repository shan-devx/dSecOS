all: disk.img

boot.bin: boot/boot.asm
	nasm -f bin boot/boot.asm -o boot.bin

stage2.bin: boot/stage2.asm
	nasm -f bin boot/stage2.asm -o stage2.bin

kernel.o: kernel/kernel.c
	i686-elf-gcc -c kernel/main.c -o kernel.o -ffreestanding -O2 -Wall -Wextra

kernel.bin: kernel.o
	ld -m elf_i386 -T kernel/linker.ld --oformat binary -o kernel.bin kernel.o

disk.img: boot.bin stage2.bin kernel.bin
	cat boot.bin stage2.bin kernel.bin > disk.img

run: disk.img
	qemu-system-i386 -drive file=disk.img,format=raw,index=0,media=disk

clean:
	rm -f *.bin *.o disk.img
