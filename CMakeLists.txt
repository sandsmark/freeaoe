cmake_minimum_required(VERSION 2.6)

project(freeaoe)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)

find_package(SFML COMPONENTS SYSTEM WINDOW GRAPHICS REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(src/
  ${CMAKE_HOME_DIRECTORY}/extern/thor/include 
  ${Boost_INCLUDE_DIRS})# 

add_subdirectory( extern/thor )

set(GLOBAL_SRC src/global/Config.cpp 
               src/global/FileException.cpp
               src/global/Logger.cpp)
             
set(RESOURCE_SRC src/resource/ResourceManager.cpp
                 src/resource/Resource.cpp
                 src/resource/Graphic.cpp
                 )

set(FILE_SRC src/file/ColorPalette.cpp
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
                   )

set(RENDER_SRC src/render/RenderUnit.cpp 
               src/render/RenderGame.cpp 
               src/render/RenderGraphic.cpp )

set(SERVER_SRC src/server/GameServer.cpp)

set(UNSORTED_SRC src/render/RenderMap.cpp src/mechanics/ActionMove.cpp src/communication/commands/CommandMove.cpp src/communication/UnitStatus.cpp src/client/GameClient.cpp src/communication/tunnels/LocalTunnelToServer.cpp src/communication/tunnels/LocalTunnelToClient.cpp src/communication/commands/CommandSpawn.cpp
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
                      ${SFML_GRAPHICS_LIBRARY}
                      ${THOR_TARGET})
                      

add_subdirectory(src)
