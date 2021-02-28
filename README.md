Snippets of baremetal applications for arm, aarch64 

# Example Projects

To compile and start the binary with qemu run the following (arm-c-qemu used as example):
```
 mkdir build/
 cd build/
 cmake -G "MingGW Makefiles" ../arm-c-qemu
 make qemu_gdb_server
```
Now connect with gdb to localhost:1234 and step through the application


## arm-c-qemu
Example which runs on qemu vexpress-a9. It also an example for using cmake for embedded

## arm-cpp-qemu
Example using cpp on embedded

## aarch64-c-qemu
Example project for aarch64.

_Note: currently no qemu settings added_

## aarch64-c-qemu-irq
Example using interrupts. E.g timer interrupt

_Note: This is an older project using scons instead of cmake. See SConstruct to see the build targets_

# Dependencies
- cmake, make (or other generators)
- arm-none-eabi-gcc and/or aarch64-none-elf-gcc
- qemu

# Dependencies (Optional)
 - Eclipse CDT as gdb gui (use remote gdb settings)
