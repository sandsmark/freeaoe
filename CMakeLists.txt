cmake_minimum_required(VERSION 2.6)

project(freeaoe)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)

#set(Boost_USE_STATIC_LIBS        ON)
#set(Boost_USE_MULTITHREADED      ON)
#set(Boost_USE_STATIC_RUNTIME    OFF)

#find_package(Boost 1.42 COMPONENTS iostreams REQUIRED) #only iostream needed

find_package(SFML COMPONENTS SYSTEM WINDOW GRAPHICS REQUIRED)
find_package(OpenGL REQUIRED)
find_package(ZLIB REQUIRED)

include_directories(src/) # ${Boost_INCLUDE_DIRS})# 

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
            # src/file/DatFile.cpp 
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
                  src/mechanics/StateManager.cpp 
                  src/mechanics/GameState.cpp 
                 
                  src/mechanics/Unit.cpp
                  src/mechanics/MapRenderer.cpp 
                   )

set(RENDER_SRC src/render/RenderUnit.cpp 
               src/render/RenderGame.cpp 
               src/render/RenderGraphic.cpp )

set(SERVER_SRC src/server/GameServer.cpp)

set(UNSORTED_SRC src/communication/commands/CommandMove.cpp src/communication/UnitData.cpp src/client/GameClient.cpp src/communication/tunnels/LocalTunnelToServer.cpp src/communication/tunnels/LocalTunnelToClient.cpp src/communication/commands/CommandSpawn.cpp
                 src/communication/TunnelToClient.cpp src/communication/TunnelToServer.cpp)

add_executable(freeaoe src/Engine.cpp src/main.cpp 
               ${FILE_SRC}
               ${RESOURCE_SRC}
               ${GLOBAL_SRC}
               ${DATA_SRC}
               ${MECHANICS_SRC}
               ${RENDER_SRC}
               ${SERVER_SRC}
               ${UNSORTED_SRC})

target_link_libraries(freeaoe 
                      ${SFML_WINDOW_LIBRARY}
                      ${SFML_SYSTEM_LIBRARY}
                      ${SFML_GRAPHICS_LIBRARY} )
                      

add_subdirectory(src)
