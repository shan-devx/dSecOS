VBE_INFO equ 0x9000 ; just after stage 2
VBE_MODE equ 0x9000+ 0x200 ; + 512
FR_BUFF equ VBE_MODE+0x100 ; +256

[org 0x7e00]
[bits 16]

in al, 0x92
or al, 2
out 0x92, al

; loading kernel
; lba
load_kernel:
  mov si, dap
  mov ah, 0x42
  mov dl, 0x80
  int 0x13
  jc kernel_error

  add word [dap+6], 4064 ;127*512/16
  add word [dap+8], 127

  cmp dword [dap+8], 59904
  jl load_kernel

; vesa
mov dword [VBE_INFO], "VBE2"

xor ax, ax
mov es, ax
mov di, VBE_INFO ; just after stage 2

mov ax, 0x4F00
int 0x10

cmp ax, 0x004F
jne vbe_error

mov si, [VBE_INFO+14]
sub si, 2
mov ax, [VBE_INFO+16]
mov fs, ax
loop_mode: 
  add si, 2
  cmp word [fs:si], 0xFFFF
  je vbe_error

  mov cx, [fs:si] ; 1st element of supported video modes array
  xor ax, ax 
  mov es, ax
  mov di, VBE_MODE

  mov ax, 0x4F01
  int 0x10
  cmp ax, 0x004F
  jne vbe_error

  cmp word [VBE_MODE+18], 320 ;width
  jne loop_mode
  cmp word [VBE_MODE+20], 200 ;height
  jne loop_mode
  cmp byte [VBE_MODE+25], 32 ;bpp
  jne loop_mode
  test byte [VBE_MODE], 0x80 ;liner frame buffer
  jz loop_mode

mov eax ,[VBE_MODE + 40]
mov [FR_BUFF], eax

or cx, 0x4000
mov bx, cx
mov ax, 0x4F02
int 0x10

cmp ax, 0x004F
jne vbe_error


; to protected mode
cli ; clear interrupt flag (to ignore any input)

xor ax, ax
mov ds, ax
mov es, ax

lgdt [gdt_desc] ; ds:gdt_desc

mov eax, cr0
or eax, 1
mov cr0, eax

jmp 0x8:protected_mode ; cs = 8

kernel_error:
  mov si, kernel_error_msg
print:
  mov ah, 0xe
  mov al, [si]
  cmp al, 0
  je done
  int 0x10
  add si, 1
  jmp print
done:
  jmp done
kernel_error_msg:
  db "[ERROR] reading kernel", 0

vbe_error:
  mov si, vbe_error_msg
  jmp print
vbe_error_msg:
  db "[ERROR] vbe", 0

align 8 ; for speed!!
gdt:
  gdt_null:
    dq 0

  gdt_code:
    dw 0xFFFF ; limit
    dw 0 ; base address

    db 0 ; base address
    db 0b10011010 ; readable codesegment, nonconforming, highest privellage level
    db 0b11001111 ; 32-bits, 4kb page unit, 0xF segment limiter
    db 0

  gdt_data:
    dw 0xFFFF
    dw 0

    db 0
    db 0b10010010 ; writable datasegment, stack expanding down, higest privellage level
    db 0b11001111
    ;db 0b11101111 ; 32-bits, 4kb page unit, 0xF segment limiter, set big
    db 0
gdt_end:

gdt_desc:
  dw gdt_end - gdt - 1
  dd gdt

dap: ;disk address packet
  db 0x10 
  db 0

  dw 127 ; no. of sector

  dw 0 ;offset
  dw 0x1000 ;segment

  dd 3 ; start from 4rd sector
  dd 0

[bits 32]

protected_mode:
  mov ax, 0x10 ; data segment
  mov ds, ax
  mov es, ax
  mov fs, ax 
  mov gs, ax
  mov ss, ax

  mov esp, 0x90000

jmp 0x10000
