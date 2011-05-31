project(freeaoe)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)

Find_Package(SFML REQUIRED)


add_executable(freeaoe src/file/ColorPalette.cpp src/file/FileIO.cpp src/file/SlpFrame.cpp src/file/SlpFile.cpp src/file/DrsGraphics.cpp src/file/DrsFile.cpp main.cpp)

target_link_libraries(freeaoe ${SFML_LIBRARY})

add_subdirectory(src)