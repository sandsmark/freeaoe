cmake_minimum_required(VERSION 2.6)

set (CMAKE_CXX_STANDARD 17)

project(freeaoe)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
endif()


if(WIN32)
    include_directories(extern/genieutils/extern/win-iconv/)
    add_definitions(-DNTDDI_VERSION=NTDDI_WINBLUE)
endif()

if(MSVC)
    add_definitions(/D_USE_MATH_DEFINES)
    #add_definitions(/wd4244 /wd4018 /wd4267 /wd4996 /wd4305 /wd4800)

    find_package(SFML COMPONENTS system window graphics REQUIRED)
    find_package(BZip2)
    find_package(ZLIB)
    find_package(PNG)
    set(EXTRA_LIBS PNG::PNG ZLIB::ZLIB BZip2::BZip2)
else()
    add_definitions(-Wall -Wextra -Wno-sign-compare -Wno-unused-parameter)
    set(EXTRA_LIBS stdc++fs)
    set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)
    find_package(SFML COMPONENTS system window graphics REQUIRED)
endif()

include_directories(
    src/
    ${CMAKE_CURRENT_SOURCE_DIR}/extern/genieutils/include
    ${PROJECT_BINARY_DIR}
  )

set(GENIEUTILS_STATIC_BUILD True)

add_subdirectory(extern/genieutils)
add_subdirectory(tools/resgen)

# additional compiler flags 
#add_definitions(-Wall -Wextra)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")

set(GLOBAL_SRC
    src/global/Config.cpp
    src/global/Logger.cpp
    )

set(RESOURCE_SRC
    src/resource/DataManager.cpp
    src/resource/Graphic.cpp
    src/resource/LanguageManager.cpp
    src/resource/Resource.cpp
    src/resource/ResourceManager.cpp
    src/resource/Terrain.cpp
    )

set(MECHANICS_SRC
    src/mechanics/ActionBuild.cpp
    src/mechanics/ActionMove.cpp
    src/mechanics/Civilization.cpp
    src/mechanics/CompMapObject.cpp
    src/mechanics/CompUnitData.cpp
    src/mechanics/Farm.cpp
    src/mechanics/GameState.cpp
    src/mechanics/Map.cpp
    src/mechanics/Player.cpp
    src/mechanics/StateManager.cpp
    src/mechanics/UnitFactory.cpp
    src/mechanics/UnitManager.cpp
    )

set(RENDER_SRC
    src/render/ActAnimate.cpp
    src/render/ActionPanel.cpp
    src/render/Camera.cpp
    src/render/GraphicRender.cpp
    src/render/IRenderer.cpp
    src/render/MapRenderer.cpp
    src/render/SfmlRenderTarget.cpp
    )

set(SERVER_SRC
    src/server/GameServer.cpp
    )

set(COMMUNICATION_SRC
    src/client/GameClient.cpp
    src/communication/TunnelToClient.cpp
    src/communication/TunnelToServer.cpp
    src/communication/UnitStatus.cpp
    src/communication/commands/CommandMove.cpp
    src/communication/commands/CommandSpawn.cpp
    src/communication/tunnels/LocalTunnelToClient.cpp
    src/communication/tunnels/LocalunnelToServer.cpp
    )

set(UNSORTED_SRC
    src/core/Entity.cpp
    src/core/IAction.cpp
    src/core/IComponent.cpp
)

set (UI_SRC
    src/ui/FileDialog.cpp
    )

add_resource(FONT_RES
    fonts/Alegreya-Bold.latin
    )

add_executable(freeaoe src/Engine.cpp src/main.cpp 
               ${RESOURCE_SRC}
               ${GLOBAL_SRC}
               ${MECHANICS_SRC}
               ${RENDER_SRC}
#               ${SERVER_SRC}
#               ${COMMUNICATION_SRC}
               ${UNSORTED_SRC}
               ${UI_SRC}
               ${FONT_RES}
               )

target_link_libraries(freeaoe
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
    ${EXTRA_LIBS}
    genieutils
)
