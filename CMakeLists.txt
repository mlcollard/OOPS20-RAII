# @file CMakeLists.txt
# 
# CMake files for RAII example

cmake_minimum_required(VERSION 3.10)

# project info
project(RAII)

# C++17 standard
set(CMAKE_CXX_STANDARD 17)

# Resource application
add_executable(Resource Resource.cpp)

# Run valgrind memtest if installed
find_program(VALGRIND NAMES valgrind)
if(VALGRIND)
add_custom_target(memtest
    COMMENT "Run valgrind memtest"
    COMMAND ${VALGRIND} -v --tool=memcheck --leak-check=full ./Resource
    DEPENDS Resource
    USES_TERMINAL
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
endif()
