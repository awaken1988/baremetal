set(TOOLCHAIN_PREFIX "aarch64-none-elf-")

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER "${TOOLCHAIN_PREFIX}gcc.exe")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PREFIX}g++.exe")
set(CMAKE_EXE_LINKER_FLAGS "--specs=nosys.specs" CACHE INTERNAL "")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
enable_language(C ASM)

function(add_qemu_gdb_server aProgramElf)
    add_custom_target(
        qemu_gdb_server
        message("TODO: start aarh64 qemu environment")
        #COMMAND "qemu-system-arm" --machine vexpress-a9 -kernel "${aProgramElf}" -s -S -semihosting)
endfunction()

function(add_disassembly aProgramElf)
    add_custom_command(
        TARGET "${aProgramElf}"
        POST_BUILD
        COMMAND "${TOOLCHAIN_PREFIX}objdump" -D "${aProgramElf}" > "${aProgramElf}.dis" 
        COMMENT "Disassemble ${aProgramElf}")
endfunction()
