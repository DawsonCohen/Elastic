# Sandbox executable
cmake_minimum_required(VERSION 3.11)

set(CMAKE_CUDA_COMPILER "nvcc")
# set(CMAKE_CXX_COMPILER "/usr/bin/g++")
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SANDBOX_SRC ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB SANDBOX_HEAD ${CMAKE_SOURCE_DIR}/src/*.h)

project(Sandbox CXX)

add_subdirectory(.. build)

add_executable(Sandbox
    # Add all your source files here
    ${SANDBOX_SRC}
    ${SANDBOX_HEAD}
)

include_directories(Sandbox PRIVATE 
    ${CMAKE_SOURCE_DIR}/../Elastic/vendor/spdlog/include
    ${CMAKE_SOURCE_DIR}/../Elastic/vendor/
    ${CMAKE_SOURCE_DIR}/../Elastic/vendor/glm
    ${CMAKE_SOURCE_DIR}/../Elastic/src
)

target_include_directories(Sandbox PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(Sandbox PUBLIC pthread Elastic)

# Compiler options for different configurations
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DEL_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DEL_RELEASE -O3")
set(CMAKE_CXX_FLAGS_DIST "${CMAKE_CXX_FLAGS_DIST} -DEL_DIST -O3")