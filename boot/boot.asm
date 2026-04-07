[org 0x7c00]
[bits 16]

mov bx, 0x7e00 ; stage 2 location

mov ah, 2 ; chs read mode
mov al, 1 ; 1 sector

mov ch, 0
mov dh, 0
mov cl, 2 ; 2nd sector
mov dl, 0x80 ; hdd

int 0x13

jc read_error
jmp 0x0000:0x7e00

read_error:
  mov si, error_msg
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

error_msg:
  db "[ERROR] reading 2nd stage bootloader", 0

times 510-($-$$) db 0
dw 0xaa55 ; signature 
