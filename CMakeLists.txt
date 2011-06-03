cmake_minimum_required(VERSION 2.6)

project(freeaoe)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)

Find_Package(SFML REQUIRED)

include_directories(src/ lib/genied2/src/)

add_subdirectory(lib/genied2)

add_executable(freeaoe src/file/SubFile.cpp src/global/Config.cpp src/resource/Graphic.cpp src/resource/ResourceManager.cpp src/resource/Resource.cpp src/global/FileException.cpp src/file/ColorPalette.cpp src/file/FileIO.cpp src/file/SlpFrame.cpp src/file/SlpFile.cpp src/file/DrsFile.cpp main.cpp)

target_link_libraries(freeaoe geni_lib2 ${SFML_LIBRARY} )

add_subdirectory(src)
