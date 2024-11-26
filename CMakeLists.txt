cmake_minimum_required(VERSION 3.22.1)
project(cs50_personal C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_COMPILER "clang")

include_directories(/usr/lib)

add_executable(cs50_personal linked.c
        linked.c)

# target_link_libraries(cs50_personal /usr/lib/libcs50.so m)
target_link_libraries(cs50_personal m)
