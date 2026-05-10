# dSecOS
A custom OS devloped in C from scratch
<img width="817" height="749" alt="dSecOS_devlog7" src="https://github.com/user-attachments/assets/cfaf5d5a-d4b0-4433-a31c-bb4c045d6e8b" />

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
