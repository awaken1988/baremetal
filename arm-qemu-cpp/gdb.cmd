set confirm off
file out/program.elf
target remote localhost:1234

set  disassemble-next-line on

b main