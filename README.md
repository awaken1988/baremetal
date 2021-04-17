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

## aarch64-c-qemu
Example project for aarch64.

_Note: currently no qemu settings added_

## aarch64-c-qemu-irq
Example using interrupts. E.g timer interrupt

_Note: This is an older project using scons instead of cmake. See SConstruct to see the build targets_

## aarch64-cpp-qemu
Example of using c++ on aarch64. This example uses std::cout to print to qemu's serial console

## arm-c-qemu
Example which runs on qemu vexpress-a9. It also an example for using cmake for embedded

## arm-cpp-qemu
Example using cpp on embedded
_Note: more fancy std functions like cout may fail due to missing crt runtime init_

## mini-kernel
_WIP_ Test Cpu Interrupts, MMU and other

# Reference
*	Project
    *   [armv8-bare-metal.git](https://github.com/NienfengYao/armv8-bare-metal.git)

# Dependencies
- cmake, make (or other generators)
- arm-none-eabi-gcc
- aarch64-none-elf-gcc
- qemu

# Dependencies (Optional)
 - Eclipse CDT as gdb gui (use remote gdb settings)
