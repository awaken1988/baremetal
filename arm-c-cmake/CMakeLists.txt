cmake_minimum_required(VERSION 3.11.1)
include("../cmake_toolchains/arm_nosys.cmake")

project(main C)

add_executable(my main.c startup.s)

#linker
set(LINKER_SCRIPT "linker.ld")
set(MAP_FILE "${PROJECT_BINARY_DIR}/my.map")
set_target_properties(my PROPERTIES LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${LINKER_SCRIPT})
target_link_options(my PRIVATE "-T${CMAKE_CURRENT_SOURCE_DIR}/linker.ld")
target_link_options(my PRIVATE "-Wl,-Map,${MAP_FILE}")

add_qemu_gdb_server( $<TARGET_FILE:my>  )
add_disassembly( my )