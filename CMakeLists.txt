cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

#include(FetchContent)
#FetchContent_Declare(SFML
#    GIT_REPOSITORY https://github.com/SFML/SFML.git
#    GIT_TAG 2.6.x)
#FetchContent_MakeAvailable(SFML)


find_package(SFML 2 REQUIRED COMPONENTS graphics)

add_executable(CMakeSFMLProject src/Main.cpp
    src/MapSelection/MapSelectionState.hpp
    src/MapSelection/MapSelection.hpp
    src/MapSelection/chunk.hpp

    src/Game/Game.hpp

    src/InGame/InGameState.hpp
    src/InGame/InGame.hpp
    src/InGame/Map.hpp
    src/InGame/Chunk.hpp
    src/InGame/TileMap.hpp
    src/InGame/Tile.hpp
    src/InGame/Player.hpp

    src/Renderer/renderer.hpp

    src/State/GameState.hpp
    src/State/StateManager.hpp
)

target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics)
target_compile_features(CMakeSFMLProject PRIVATE cxx_std_20)
target_include_directories(CMakeSFMLProject PUBLIC src)

if(WIN32)
    add_custom_command(
        TARGET CMakeSFMLProject
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
        VERBATIM)
endif()

install(TARGETS CMakeSFMLProject)
