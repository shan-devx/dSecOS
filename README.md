# dSecOS
A custom OS devloped in C from scratch

## Recommended VM specs
RAM: 50M
Emulator: qemu-system-i386

## How to run
```bash
qemu-system-i386 -m 50M -drive file=disk.img,format=raw
```

### Building from Source
```bash
git clone https://github.com/shan-devx/dSecOS.git
cd dSecOS
make run clean
```

#### Prerequisits
- i686-elf-gcc
- i686-elf-ld
