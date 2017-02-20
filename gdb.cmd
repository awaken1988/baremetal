set confirm off
file out/program.elf
target remote | qemu-system-aarch64 -M virt -cpu cortex-a57 -kernel out/program.elf -gdb stdio -S -semihosting
layout regs
