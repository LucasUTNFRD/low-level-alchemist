cmake_minimum_required(VERSION 3.23)
project(my_project)

set(CMAKE_CXX_STANDARD 17)

# Add your source files here
set(SOURCE_FILES main.c hashmap.c test.c)

add_executable(my_project ${SOURCE_FILES})
