cmake_minimum_required(VERSION 3.10)
project(HornSchunk)

set(CMAKE_C_STANDARD 11)

include_directories(headers)

add_executable(HornSchunk
    src/main.c
    src/myBmpGris.c
)