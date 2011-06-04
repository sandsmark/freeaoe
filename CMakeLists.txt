cmake_minimum_required(VERSION 2.6)

project(freeaoe)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)

Find_Package(SFML REQUIRED)

include_directories(src/ lib/genied2/src/)

add_subdirectory(lib/genied2)


set(FILE_SRC src/file/SubFile.cpp 
)

set(GLOBAL_SRC src/global/Config.cpp 
               src/global/FileException.cpp
               src/global/Logger.cpp
               src/global/FrameRegulator.cpp)
             
set(RESOURCE_SRC src/resource/Graphic.cpp
                 src/resource/ResourceManager.cpp
                 src/resource/Resource.cpp)

set(FILE_SRC src/file/ColorPalette.cpp
             src/file/FileIO.cpp
             src/file/SlpFrame.cpp
             src/file/SlpFile.cpp
             src/file/DrsFile.cpp)

set(DATA_SRC src/data/GenieTerrain.cpp)

set(MECHANICS_SRC src/mechanics/Map.cpp
                  src/mechanics/MapRenderer.cpp) 

add_executable(freeaoe src/Engine.cpp main.cpp 
               ${FILE_SRC}
               ${RESOURCE_SRC}
               ${GLOBAL_SRC}
               ${DATA_SRC}
               ${MECHANICS_SRC})

target_link_libraries(freeaoe geni_lib2 ${SFML_LIBRARY} )

add_subdirectory(src)
