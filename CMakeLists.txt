cmake_minimum_required(VERSION 2.6)

project(freeaoe)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost 1.42 COMPONENTS iostreams REQUIRED) #only iostream needed

find_package(SFML REQUIRED)
find_package(OpenGL REQUIRED)
find_package(ZLIB REQUIRED)

include_directories(src/ ${Boost_INCLUDE_DIRS})# lib/genied2/src/) #lib/SFML_2.0/include/)

#add_subdirectory(lib/genied2)
#add_subdirectory(lib/SFML_2.0)


set(FILE_SRC src/file/SubFile.cpp 
)

set(GLOBAL_SRC src/global/Config.cpp 
               src/global/FileException.cpp
               src/global/Logger.cpp)
             
set(RESOURCE_SRC #src/resource/Graphic.cpp
                 src/resource/ResourceManager.cpp
                 #src/resource/Resource.cpp)
                 )

set(FILE_SRC src/file/ColorPalette.cpp
             src/file/DatFile.cpp 
             src/file/FileIO.cpp
             src/file/SlpFrame.cpp
             src/file/SlpFile.cpp
             src/file/DrsFile.cpp
             src/file/BinaFile.cpp)

set(DATA_SRC src/data/DataManager.cpp 
             src/data/GenieTerrain.cpp
             src/data/GenieGraphic.cpp 
             src/data/GenieUnit.cpp )

set(MECHANICS_SRC src/mechanics/Map.cpp
                  src/mechanics/MapRenderer.cpp) 

set(RENDER_SRC src/render/RenderGraphic.cpp )

add_executable(freeaoe src/Engine.cpp main.cpp 
               ${FILE_SRC}
               ${RESOURCE_SRC}
               ${GLOBAL_SRC}
               ${DATA_SRC}
               ${MECHANICS_SRC}
               ${RENDER_SRC})

target_link_libraries(freeaoe ${SFML_LIBRARY} ${Boost_LIBRARIES} )#sfml-graphics sfml-window sfml-system )

add_subdirectory(src)
