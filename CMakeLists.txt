if(${CMAKE_VERSION} VERSION_LESS "3.9.0")
 cmake_minimum_required(VERSION 2.6)
 message("Please upgrade to cmake 3.9 to get more fancy stuff")
else()
 cmake_minimum_required(VERSION 3.9)
endif()

option(BUILD_TESTS "Build tests")

set (CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(freeaoe)

if(DEFAULT_DATA_PATH)
    add_definitions(-DDEFAULT_DATA_PATH=\"${DEFAULT_DATA_PATH}\")
endif()

#############################
## Compiler specific stuff ##
#############################
option(ENABLE_IPO "Enable link-time optimization, improves speed and memory usage (https://en.wikipedia.org/wiki/Interprocedural_optimization)")
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

if (VC_STATIC)
    message(STATUS "Static build with MSVC")
    set(CMAKE_CXX_FLAGS_RELEASE "/MT /O2 /Ob2 /DNDEBUG")
    set(CMAKE_C_FLAGS_RELEASE "/MT /O2 /Ob2 /DNDEBUG")
endif()

#find_package(SDL2 REQUIRED)

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

find_program(BUILDCACHE_PROGRAM buildcache)
if(BUILDCACHE_PROGRAM)
    message(STATUS "Using buildcache: ${BUILDCACHE_PROGRAM}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${BUILDCACHE_PROGRAM}")
endif()


option(ENABLE_SANITIZERS "Enable runtime sanitizing (for development)")
if (ENABLE_SANITIZERS)
    message("Enabling asan and ubsan")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
endif()

##################
## Dependencies ##
##################

if(WIN32)
    include_directories(src/extern/genieutils/extern/win-iconv/)
    add_definitions(-DNTDDI_VERSION=NTDDI_WINBLUE)
endif()

if(MSVC)
    add_definitions(/D_USE_MATH_DEFINES)
    add_definitions(/wd4244 /wd4018 /wd4267 /wd4996 /wd4305 /wd4800 /wd4065)

    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /fp:fast")

    find_package(SFML 2.5 CONFIG COMPONENTS system window graphics REQUIRED)
    find_package(BZip2)
    find_package(ZLIB)
    find_package(PNG)
    set(EXTRA_LIBS PNG::PNG ZLIB::ZLIB BZip2::BZip2)
else()
    add_definitions(-fno-math-errno)
    if (NOT CMAKE_BUILD_TYPE MATCHES Debug)
        # clang gets undefined references to builtin exp, log, etc. with -ffinite-math-only/-fno-honor-infinities, so we do this the hard way
        if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -funsafe-math-optimizations -fno-honor-nans -fassociative-math -freciprocal-math -fno-signed-zeros -fno-trapping-math -ffp-contract=fast")
            add_definitions(-D__FAST_MATH__)
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math")
        endif()
        #string(REPLACE "-O3" "-Ofast" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
    endif()

    add_definitions(-Wall -Wextra -pedantic -Wno-sign-compare -Wno-unused-parameter)
    set(EXTRA_LIBS pthread dl)

    # Somehow need this because otherwise the SFML config gets fucked
    find_package(ZLIB)

    find_package(SFML COMPONENTS system window graphics REQUIRED)
endif()

if(NOT APPLE)
    set(EXTRA_LIBS ${EXTRA_LIBS} stdc++fs)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_definitions(-Wno-nested-anon-types)
endif()

# TODO: proper find_packages
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/extern/miniaudio/miniaudio.h)
    message(STATUS "Using bundled miniaudio")
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/extern/)
endif()

# TODO: proper find_packages
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/extern/genieutils/include/genie/Types.h)
    message(STATUS "Using bundled genieutils")
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/extern/genieutils/include/)

    set(GUTILS_STATIC True)
    add_subdirectory(src/extern/genieutils)
endif()


include_directories(
    src/
    src/extern/
    ${PROJECT_BINARY_DIR}
  )


# Because we want to support msvc we can't use the standard funny linker or incbin tricks
add_subdirectory(src/tools/resgen)
add_resource(FONT_ALEGREYA misc/fonts/Alegreya/Alegreya-Bold.latin)
add_resource(FONT_BERRYROTUNDA misc/fonts/BerryRotunda/BerryRotunda.ttf)
add_resource(IMAGE_PARCHMENT misc/images/parchment.jpg)

set(AI_SRC
    src/ai/grammar.gen.tab.cpp
    src/ai/lex.yy.cc
    src/ai/AiRule.cpp
    src/ai/AiScript.cpp
    src/ai/ScriptLoader.cpp
    src/ai/actions/Actions.cpp
    src/ai/conditions/Conditions.cpp
    src/ai/Ids.cpp
    src/ai/AiPlayer.cpp
    )

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
    src/resource/Sprite.cpp
    src/resource/LanguageManager.cpp
    src/resource/Resource.cpp
    src/resource/AssetManager.cpp
    src/resource/TerrainSprite.cpp
    )

set(MECHANICS_SRC
    src/mechanics/Entity.cpp
    src/mechanics/Civilization.cpp
    src/mechanics/Farm.cpp
    src/mechanics/GameState.cpp
    src/mechanics/Map.cpp
    src/mechanics/Player.cpp
    src/mechanics/StateManager.cpp
    src/mechanics/UnitActionHandler.cpp
    src/mechanics/UnitFactory.cpp
    src/mechanics/UnitManager.cpp
    src/mechanics/Unit.cpp
    src/mechanics/Missile.cpp
    src/mechanics/MapTile.cpp
    src/mechanics/Building.cpp
    src/mechanics/ScenarioController.cpp
    )

set(ACTIONS_SRC
    src/actions/IAction.cpp
    src/actions/ActionAttack.cpp
    src/actions/ActionBuild.cpp
    src/actions/ActionGather.cpp
    src/actions/ActionMove.cpp
    src/actions/ActionFly.cpp
    src/actions/ActionGarrison.cpp
    )

set(RENDER_SRC
    src/render/Camera.cpp
    src/render/GraphicRender.cpp
    src/render/IRenderer.cpp
    src/render/IRenderTarget.cpp
    src/render/MapRenderer.cpp
    src/render/SfmlRenderTarget.cpp
    src/render/UnitsRenderer.cpp
    )

set(SERVER_SRC
    src/server/GameServer.cpp
    )

set(SETTINGS_SRC
    src/settings/input.cpp
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
    src/audio/Implementations.cpp
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

    ${IMAGE_PARCHMENT}
    )

set (EDITOR_SRC
    src/editor/Editor.cpp
    )

set(DEBUG_SRC
    src/debug/AllunitsGameSample.cpp
    src/debug/BasicGameSample.cpp
    src/debug/SampleGameFactory.cpp
    )

set(ENGINE_SRC
    src/Engine.cpp
    ${CORE_SRC}
    ${AI_SRC}
    ${RESOURCE_SRC}
    ${GLOBAL_SRC}
    ${MECHANICS_SRC}
    ${ACTIONS_SRC}
    ${RENDER_SRC}
    ${UNSORTED_SRC}
    ${UI_SRC}
    ${FONT_ALEGREYA}
    ${FONT_BERRYROTUNDA}
    ${SETTINGS_SRC}
    ${DEBUG_SRC}
    ${EDITOR_SRC}
    )

set(ALL_LIBRARIES
    sfml-system
    sfml-window
    sfml-graphics
    genieutils
    ${EXTRA_LIBS}
#    SDL2::SDL2
#    SDL2::SDL2main
)

add_library(freeaoe_common OBJECT ${ENGINE_SRC})
target_link_libraries(freeaoe_common ${ALL_LIBRARIES})

#add_executable(freeaoe src/main.cpp ${ENGINE_SRC})
add_executable(freeaoe src/main.cpp $<TARGET_OBJECTS:freeaoe_common>)
target_link_libraries(freeaoe ${ALL_LIBRARIES})
install(TARGETS freeaoe DESTINATION bin)

if (BUILD_TESTS)
    add_executable(test src/test/main.cpp $<TARGET_OBJECTS:freeaoe_common>)
    target_link_libraries(test ${ALL_LIBRARIES})

    add_executable(ai-test src/test/ai-test.cpp $<TARGET_OBJECTS:freeaoe_common>)
    target_link_libraries(ai-test ${ALL_LIBRARIES})
endif()

if (ENABLE_SANITIZERS)
    # these are way too big and complex for the sanitizers
    set_source_files_properties(src/ai/grammar.gen.tab.cpp PROPERTIES COMPILE_FLAGS -fno-sanitize=all)
    set_source_files_properties(src/ai/lex.yy.cc PROPERTIES COMPILE_FLAGS -fno-sanitize=all)
endif()

#if (CMAKE_BUILD_TYPE MATCHES Debug)
#    if(CLANG_TIDY_EXE)
#        set_target_properties(
#            freeaoe PROPERTIES
#            CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
#            )
#    endif()
#endif()

