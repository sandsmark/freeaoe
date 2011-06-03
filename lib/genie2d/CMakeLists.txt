
cmake_minimum_required(VERSION 2.6)

project(Genie2D)


find_package(ZLIB REQUIRED)

add_library(Genie2D src/buffer.cpp src/genied.cpp src/language.cpp 
            src/structs.cpp)
