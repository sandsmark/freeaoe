cmake_minimum_required(VERSION 2.6)

project(freeaoe)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost 1.42 COMPONENTS iostreams program_options REQUIRED)
find_package(SFML COMPONENTS SYSTEM WINDOW GRAPHICS REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(src/
  ${CMAKE_HOME_DIRECTORY}/extern/geniedat/include
  ${Boost_INCLUDE_DIRS}
  ${SFML_INCLUDE_DIR})

add_subdirectory( extern/geniedat )

# additional compiler flags 
add_definitions(-Wall)

set(GLOBAL_SRC src/global/Config.cpp 
               src/global/FileException.cpp
               src/global/Logger.cpp)
             
set(RESOURCE_SRC src/resource/ResourceManager.cpp
                 src/resource/DataManager.cpp 
                 src/resource/Resource.cpp
                 src/resource/Graphic.cpp
                 )

set(FILE_SRC src/file/ColorPalette.cpp
             src/file/FileIO.cpp
             src/file/SlpFrame.cpp
             src/file/SlpFile.cpp
             src/file/DrsFile.cpp
             src/file/BinaFile.cpp)

set(MECHANICS_SRC src/mechanics/Map.cpp
                  src/mechanics/StateManager.cpp 
                  src/mechanics/GameState.cpp 
                  src/mechanics/ActionMove.cpp
                   )

set(RENDER_SRC src/render/CompGraphic.cpp 
               src/render/EntityFormManager.cpp 
               src/render/GameRenderer.cpp
               src/render/RenderGraphic.cpp
               )

set(SERVER_SRC src/server/GameServer.cpp)

set(COMMUNICATION_SRC src/communication/TunnelToClient.cpp 
                      src/communication/TunnelToServer.cpp
                      src/communication/commands/CommandMove.cpp 
                      src/communication/UnitStatus.cpp 
                      src/client/GameClient.cpp 
                      src/communication/tunnels/LocalTunnelToServer.cpp 
                      src/communication/tunnels/LocalTunnelToClient.cpp 
                      src/communication/commands/CommandSpawn.cpp )
 

set(UNSORTED_SRC src/render/MapRender.cpp src/resource/Terrain.cpp src/render/ActAnimate.cpp src/mechanics/CompUnitData.cpp src/mechanics/EntityManager.cpp src/mechanics/CompMapObject.cpp src/core/IAction.cpp src/core/IAttribute.cpp src/mechanics/EntityFactory.cpp src/core/Attributes.cpp src/core/IComponent.cpp src/core/Entity.cpp

                 )

add_executable(freeaoe src/Engine.cpp src/main.cpp 
               ${FILE_SRC}
               ${RESOURCE_SRC}
               ${GLOBAL_SRC}
               ${MECHANICS_SRC}
               ${RENDER_SRC}
#               ${SERVER_SRC}
#               ${COMMUNICATION_SRC}
               ${UNSORTED_SRC})

target_link_libraries(freeaoe 
                      ${SFML_WINDOW_LIBRARY}
                      ${SFML_SYSTEM_LIBRARY}
                      ${SFML_GRAPHICS_LIBRARY}
                      geniedat)
                      

add_subdirectory(src)
