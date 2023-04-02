set(TOOLCHAIN_PREFIX "riscv64-elf-")

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER "${TOOLCHAIN_PREFIX}gcc")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PREFIX}g++")
set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -nostartfiles" CACHE INTERNAL "")
set(CMAKE_C_FLAGS "-march=rv32i -mabi=ilp32" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS "-march=rv32i -mabi=ilp32" CACHE INTERNAL "")
set(CMAKE_ASM_FLAGS "-march=rv32i -mabi=ilp32" CACHE INTERNAL "")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
set(CMAKE_C_COMPILER_WORKS 1)
enable_language(C CXX ASM)

function(add_qemu_gdb_server aProgramElf)
    add_custom_target(
        qemu_gdb_server
        COMMAND "qemu-system-aarch64" -M virt -cpu cortex-a57 -kernel "${aProgramElf}" -s -S -semihosting)
endfunction()

function(add_disassembly aProgramElf)
    add_custom_command(
        TARGET "${aProgramElf}"
        POST_BUILD
        COMMAND "${TOOLCHAIN_PREFIX}objdump" -D "${aProgramElf}" > "${aProgramElf}.dis" 
        COMMENT "Disassemble ${aProgramElf}")
endfunction()
