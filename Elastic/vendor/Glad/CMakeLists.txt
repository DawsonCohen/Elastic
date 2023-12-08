cmake_minimum_required(VERSION 3.10)
project(Glad)

set(CMAKE_C_STANDARD 99)

# Source files
set( FILES
    include/glad/glad.h
    include/KHR/khrplatform.h
    src/glad.c
)

# Glad library
add_library(Glad STATIC ${FILES})

target_include_directories(Glad PRIVATE include)

# Compiler options for different configurations
target_compile_options(Glad PRIVATE
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Release>:-O3>
)

# PIC for Linux
if(UNIX AND NOT APPLE)
    set_target_properties(Glad PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()