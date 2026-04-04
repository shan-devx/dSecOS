[org 0x7e00]
[bits 16]

cli ; clear interrupt flag (to ignore any input)

xor ax, ax
mov ds, ax

lgdt [gdt_desc] ; ds:gdt_desc

mov eax, cr0
or eax, 1
mov cr0, eax

jmp 0x8:protected_mode ; cs = 8

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
    db 0b11101111 ; 32-bits, 4kb page unit, 0xF segment limiter, set big
    db 0
gdt_end:

gdt_desc:
  dw gdt_end - gdt - 1
  dd gdt

[bits 32]

protected_mode:
  mov ax, 0x10 ; data segment
  mov ds, ax
  mov ss, ax

  mov esp, 0x90000

jmp $

times 510-($-$$) db 0
dw 0xaa55
