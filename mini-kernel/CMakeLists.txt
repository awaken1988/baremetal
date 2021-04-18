cmake_minimum_required(VERSION 3.11.1)
#TODO: make arch packages configurable

include("../cmake_toolchains/aarch64_test.cmake")

project(main C)

set(STARTUP_ASM arch/aarch64/startup.S)

add_executable(kernel 
    main.cpp 
    std_impl.c 
    ${STARTUP_ASM}
    arch/aarch64/aarch64.cpp
    arch/aarch64/gic.cpp
    board/qemu_aarch64/board.cpp
)
target_include_directories(kernel PRIVATE include)
set_source_files_properties(${STARTUP_ASM} PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp")


#aarch64 specific
#   TODO: make this configurable from commandline
target_include_directories(kernel PRIVATE ./ )
target_include_directories(kernel PRIVATE arch/aarch64 )
target_include_directories(kernel PRIVATE board/qemu_aarch64 )



#compiler
target_compile_options(kernel PRIVATE -ggdb -mcpu=cortex-a57)


#linker
set(LINKER_SCRIPT "arch/aarch64/linker.ld")
set(MAP_FILE "${PROJECT_BINARY_DIR}/kernel.map")
set_target_properties(kernel PROPERTIES LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${LINKER_SCRIPT})
target_link_options(kernel PRIVATE "-T${CMAKE_CURRENT_SOURCE_DIR}/${LINKER_SCRIPT}")
target_link_options(kernel PRIVATE "-Wl,-Map,${MAP_FILE}")

add_qemu_gdb_server( $<TARGET_FILE:kernel>  )
add_disassembly( kernel )