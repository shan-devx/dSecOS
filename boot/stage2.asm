[org 0x7e00]
[bits 16]

in al, 0x92
or al, 2
out 0x92, al

; loading kernel
mov ax, 0x1000
mov es, ax
xor bx, bx
mov ah, 2
mov al, 5 ; number of sector (i think i might need to change this later)
mov ch, 0
mov dh, 0
mov cl, 3 ; kernel is at 3rd sector
mov dl, 0x80
int 0x13
jc kernel_error

cli ; clear interrupt flag (to ignore any input)

xor ax, ax
mov ds, ax

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

times 510-($-$$) db 0
dw 0xaa55
