if(${CMAKE_VERSION} VERSION_LESS "3.9.0")
 cmake_minimum_required(VERSION 2.6)
 message("Please upgrade to cmake 3.9 to get more fancy stuff")
else()
 cmake_minimum_required(VERSION 3.9)
endif()

set (CMAKE_CXX_STANDARD 17)

project(freeaoe)

#############################
## Compiler specific stuff ##
#############################
if (ENABLE_IPO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT IPO_AVAILABLE OUTPUT IPO_ERROR)
    if (IPO_AVAILABLE)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION True)

        if (CMAKE_COMPILER_IS_GNUCXX)
            message(STATUS "Enabling all link time optimizations")
            add_definitions(-fuse-linker-plugin)
        else()
            message(STATUS "Disabling linker plugin for link time optimization")
        endif()
    else()
        message(STATUS "IPO/LTO not supported: <${IPO_ERROR}>")
    endif()
else()
    message(STATUS "Not enabling IPO/LTO")
endif()

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)

    find_program(
        CLANG_TIDY_EXE
        NAMES "clang-tidy"
        DOC "Path to clang-tidy executable"
        )
    if(NOT CLANG_TIDY_EXE)
        message(STATUS "clang-tidy not found.")
    else()
        message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
        set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}")
    endif()
endif()

if (ENABLE_SANITIZERS)
    message("Enabling asan and ubsan")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
endif()

##################
## Dependencies ##
##################

if(WIN32)
    include_directories(extern/genieutils/extern/win-iconv/)
    add_definitions(-DNTDDI_VERSION=NTDDI_WINBLUE)
endif()

if(MSVC)
    add_definitions(/D_USE_MATH_DEFINES)
    add_definitions(/wd4244 /wd4018 /wd4267 /wd4996 /wd4305 /wd4800)

    find_package(SFML COMPONENTS system window graphics REQUIRED)
    find_package(BZip2)
    find_package(ZLIB)
    find_package(PNG)
    set(EXTRA_LIBS PNG::PNG ZLIB::ZLIB BZip2::BZip2)
else()
    add_definitions(-Wall -Wextra -pedantic -Wno-sign-compare -Wno-unused-parameter)
    set(EXTRA_LIBS stdc++fs pthread dl)
    set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)
    find_package(SFML COMPONENTS system window graphics REQUIRED)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_definitions(-Wno-nested-anon-types)
endif()

# TODO: proper find_packages
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/extern/mini_al/mini_al.h)
    message(STATUS "Using bundled mini_al")
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extern/)
endif()

# TODO: proper find_packages
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/extern/genieutils/include/genie/Types.h)
    message(STATUS "Using bundled genieutils")
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extern/genieutils/include/)

    set(GENIEUTILS_STATIC_BUILD True)
    add_subdirectory(extern/genieutils)
endif()


include_directories(
    src/
    ${PROJECT_BINARY_DIR}
  )


add_subdirectory(tools/resgen)
add_resource(FONT_ALEGREYA fonts/Alegreya/Alegreya-Bold.latin)
add_resource(FONT_BERRYROTUNDA fonts/BerryRotunda/BerryRotunda.ttf)

set(CORE_SRC
    src/core/Logger.cpp
    src/core/Utility.cpp
    )

set(GLOBAL_SRC
    src/global/Config.cpp
    src/global/EventManager.cpp
    src/global/EventListener.cpp
    )

set(RESOURCE_SRC
    src/resource/DataManager.cpp
    src/resource/Graphic.cpp
    src/resource/LanguageManager.cpp
    src/resource/Resource.cpp
    src/resource/AssetManager.cpp
    src/resource/Terrain.cpp
    )

set(MECHANICS_SRC
    src/mechanics/Entity.cpp
    src/mechanics/Civilization.cpp
    src/mechanics/Farm.cpp
    src/mechanics/GameState.cpp
    src/mechanics/Map.cpp
    src/mechanics/Player.cpp
    src/mechanics/StateManager.cpp
    src/mechanics/UnitFactory.cpp
    src/mechanics/UnitManager.cpp
    src/mechanics/Unit.cpp
    src/mechanics/Missile.cpp
    src/mechanics/MapTile.cpp
    src/mechanics/Building.cpp
    )

set(ACTIONS_SRC
    src/actions/IAction.cpp
    src/actions/ActionAttack.cpp
    src/actions/ActionBuild.cpp
    src/actions/ActionGather.cpp
    src/actions/ActionMove.cpp
    src/actions/ActionFly.cpp
    )

set(RENDER_SRC
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
    src/audio/AudioPlayer.cpp
    src/audio/sts_mixer.cpp
)

set (UI_SRC
    src/ui/ActionPanel.cpp
    src/ui/FileDialog.cpp
    src/ui/UnitInfoPanel.cpp
    src/ui/HomeScreen.cpp
    src/ui/HistoryScreen.cpp
    src/ui/UiScreen.cpp
    src/ui/TextButton.cpp
    src/ui/Minimap.cpp
    src/ui/Dialog.cpp
    src/ui/NumberLabel.cpp
    src/ui/MouseCursor.cpp
    src/ui/IconButton.cpp
    )

set(DEBUG_SRC
    src/debug/AllunitsGameSample.cpp
    src/debug/BasicGameSample.cpp
    src/debug/SampleGameFactory.cpp
    )

set(ENGINE_SRC
    src/Engine.cpp
    ${CORE_SRC}
    ${RESOURCE_SRC}
    ${GLOBAL_SRC}
    ${MECHANICS_SRC}
    ${ACTIONS_SRC}
    ${RENDER_SRC}
    ${UNSORTED_SRC}
    ${UI_SRC}
    ${FONT_ALEGREYA}
    ${FONT_BERRYROTUNDA}
    ${DEBUG_SRC}
    )

set(ALL_LIBRARIES
    sfml-system
    sfml-window
    sfml-graphics
    ${EXTRA_LIBS}
    genieutils
    )

add_executable(freeaoe src/main.cpp ${ENGINE_SRC})
target_link_libraries(freeaoe ${ALL_LIBRARIES})
install(TARGETS freeaoe DESTINATION bin)

add_executable(test test/main.cpp ${ENGINE_SRC})
target_link_libraries(test ${ALL_LIBRARIES})

#if (CMAKE_BUILD_TYPE MATCHES Debug)
#    if(CLANG_TIDY_EXE)
#        set_target_properties(
#            freeaoe PROPERTIES
#            CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
#            )
#    endif()
#endif()

