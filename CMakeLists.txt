cmake_minimum_required(VERSION 2.6)

set (CMAKE_CXX_STANDARD 17)

set(SFML_STATIC_LIBRARIES TRUE)

project(freeaoe)

find_package(SFML COMPONENTS system window graphics REQUIRED)

if(MSVC)
    add_definitions(/D_USE_MATH_DEFINES /wd4244 /wd4018 /wd4267 /wd4996 /wd4305)
    include_directories(extern/genieutils/extern/win-iconv/)

    find_package(BZip2)
    find_package(ZLIB)
    find_package(PNG)
    set(EXTRA_LIBS PNG::PNG ZLIB::ZLIB BZip2::BZip2)

    foreach(flag
            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        if(${flag} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
        endif()
    endforeach()
else()
    add_definitions(-Wall -Wextra -Wno-sign-compare -Wno-unused-parameter)
    set(EXTRA_LIBS stdc++fs)
    set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)
endif()


include_directories(src/
  ${CMAKE_HOME_DIRECTORY}/extern/genieutils/include
  ${SFML_INCLUDE_DIR})

set (GENIEUTILS_STATIC_BUILD True)
add_subdirectory( extern/genieutils )

# additional compiler flags 
#add_definitions(-Wall )
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")

set(GLOBAL_SRC 
    src/global/Config.cpp 
    src/global/Logger.cpp
    )
             
set(RESOURCE_SRC 
    src/resource/ResourceManager.cpp
    src/resource/DataManager.cpp 
    src/resource/Resource.cpp
    src/resource/Graphic.cpp
    src/resource/LanguageManager.cpp
    )

set(MECHANICS_SRC 
    src/mechanics/Map.cpp
    src/mechanics/StateManager.cpp 
    src/mechanics/GameState.cpp 
    src/mechanics/ActionMove.cpp
    src/mechanics/ActionBuild.cpp
    src/mechanics/Civilization.cpp
    src/mechanics/Player.cpp
    )

set(RENDER_SRC 
    src/render/IRenderer.cpp
    src/render/GraphicRender.cpp 
    src/render/MapRenderer.cpp
    src/render/SfmlRenderTarget.cpp
    src/render/ActionPanel.cpp
    )

set(SERVER_SRC 
    src/server/GameServer.cpp)

set(COMMUNICATION_SRC 
    src/communication/TunnelToClient.cpp 
    src/communication/TunnelToServer.cpp
    src/communication/commands/CommandMove.cpp 
    src/communication/UnitStatus.cpp 
    src/client/GameClient.cpp 
    src/communication/tunnels/LocalTunnelToServer.cpp 
    src/communication/tunnels/LocalTunnelToClient.cpp 
    src/communication/commands/CommandSpawn.cpp )
 

set(UNSORTED_SRC src/render/Camera.cpp
    src/resource/Terrain.cpp
    src/render/ActAnimate.cpp
    src/mechanics/CompUnitData.cpp
    src/mechanics/UnitManager.cpp
    src/mechanics/CompMapObject.cpp
    src/core/IAction.cpp
    src/mechanics/UnitFactory.cpp
    src/core/IComponent.cpp
    src/core/Entity.cpp
)

add_executable(freeaoe src/Engine.cpp src/main.cpp 
               ${RESOURCE_SRC}
               ${GLOBAL_SRC}
               ${MECHANICS_SRC}
               ${RENDER_SRC}
#               ${SERVER_SRC}
#               ${COMMUNICATION_SRC}
               ${UNSORTED_SRC})

target_link_libraries(freeaoe
    sfml-system
    sfml-window
    sfml-graphics
    ${EXTRA_LIBS}
    genieutils
)
                      

add_subdirectory(src)
