
add_custom_target(gdb_server "qemu-system-arm --machine vexpress-a9 -kernel out/program.elf -s -S -semihosting")