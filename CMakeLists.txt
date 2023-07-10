cmake_minimum_required(VERSION 3.7.2)
cmake_policy(SET CMP0079 NEW)

set(EXE_NAME "example" CACHE STRING "The name of executable file.")
project(${EXE_NAME} LANGUAGES CXX)

set(src_dir "${CMAKE_SOURCE_DIR}/src")
set(include_dir "${CMAKE_SOURCE_DIR}/include")

file(GLOB_RECURSE src_files "./src/main.cpp" "./src/*.cpp" "./src/*.c")

add_executable(${EXE_NAME} ${src_files})

add_subdirectory("${CMAKE_SOURCE_DIR}/lib")
