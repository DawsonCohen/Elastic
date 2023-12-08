cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Elastic CXX)

file(GLOB ELASTIC_SRC Elastic/src/*.cpp
    Elastic/src/Elastic/Core/*.cpp
    Elastic/src/Elastic/Debug/*.cpp
    Elastic/src/Elastic/Events/*.cpp
    Elastic/src/Elastic/ImGui/*.cpp
    Elastic/src/Elastic/Renderer/*.cpp
    Elastic/src/Elastic/Scene/*.cpp
    Elastic/src/Elastic/Utils/*.cpp)
file(GLOB ELASTIC_HEAD Elastic/src/*.h
    Elastic/src/Elastic/Core/*.h
    Elastic/src/Elastic/Debug/*.h
    Elastic/src/Elastic/Events/*.h
    Elastic/src/Elastic/ImGui/*.h
    Elastic/src/Elastic/Renderer/*.h
    Elastic/src/Elastic/Scene/*.h
    Elastic/src/Elastic/Utils/*.h)

# Elastic library
add_library(Elastic SHARED
    # Add all your source files here
    ${ELASTIC_SRC}
    ${ELASTIC_HEAD}
    )
    
set_property(TARGET Elastic PROPERTY POSITION_INDEPENDENT_CODE ON)

# Set include directories
include_directories(
    Elastic/vendor/spdlog/include
    Elastic/vendor/GLFW/include
    Elastic/vendor/Glad/include
    Elastic/vendor/imgui
    Elastic/vendor/glm
    Elastic/vendor
    Elastic/src
)

add_subdirectory(Elastic/vendor/glm)
add_subdirectory(Elastic/vendor/GLFW)
add_subdirectory(Elastic/vendor/Glad)
add_subdirectory(Elastic/vendor/imgui)

target_include_directories(Elastic PRIVATE src)

# Link libraries
target_link_libraries(Elastic PUBLIC
  pthread
  Glad
  glfw
  ImGui
  GL
)