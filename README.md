Snippets of baremetal applications for arm, aarch64 

# Example Projects

## arm-c-cmake
Example which runs on qemu vexpress-a9. It also an example for using cmake for embedded
Usage:
```
 mkdir build/
 cd build/
 cmake -G "MingGW Makefiles" ../arm-qemu
 make qemu_gdb_server
```
Now connect gdb to localhost:1234

## arm-qemu-cpp
Simple project which runs C++ on embedded

_Note: This project use SCons as build system. See SConstruct file for available build targets_

## aarch64-qemu-c
An example for a aarch64 baremetal project with some code snippets for printing and interrupts.
The example runs on qemu

_Note: This project use SCons as build system. See SConstruct file for available build targets_

# Dependencies
- cmake
- arm-none-eabi-gcc and/or aarch64-none-elf-gcc
- qemu

# Dependencies (Optional)
 - Eclipse CDT as gdb gui (use remote gdb settings)
