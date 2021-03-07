set confirm off
file ../build/program
target remote localhost:1234

set  disassemble-next-line on

b main