
cmake_minimum_required(VERSION 2.6)

set(GENI_LIBRARY geni_lib2)

project(${GENI_LIBRARY})


find_package(ZLIB REQUIRED)

add_library(${GENI_LIBRARY} src/buffer.cpp src/genied.cpp src/language.cpp 
            src/structs.cpp)
