cmake_minimum_required(VERSION 3.11.1)
include("../cmake_toolchains/aarch64_test.cmake")

project(main C)
set(MY_EXEC "program")

add_executable(${MY_EXEC} src/main.cpp src/std_impl.c startup.s)

#compiler
target_compile_options(${MY_EXEC} PRIVATE -ggdb -mcpu=cortex-a57)


#linker
set(LINKER_SCRIPT "linker.ld")
set(MAP_FILE "${PROJECT_BINARY_DIR}/${MY_EXEC}.map")
set_target_properties(${MY_EXEC} PROPERTIES LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${LINKER_SCRIPT})
target_link_options(${MY_EXEC} PRIVATE "-T${CMAKE_CURRENT_SOURCE_DIR}/linker.ld")
target_link_options(${MY_EXEC} PRIVATE "-Wl,-Map,${MAP_FILE}")

add_qemu_gdb_server( $<TARGET_FILE:${MY_EXEC}>  )
add_disassembly( ${MY_EXEC} )