void kernel_main(){
  char *vga = (char *) 0xb8000;
  vga[0] = 'H';
  vga[1] = 0x0f;
  vga[2] = 'i';
  vga[3] = 0x0f;
  while (1);
}
