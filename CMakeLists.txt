cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(CMakeSFMLProject 
    src/Main.cpp 
    src/Game/Game.cpp 
    src/InGame/Animation.cpp
    src/InGame/Player.cpp
    src/InGame/InGameState.cpp
    src/MainMenu/Menu.cpp
)

target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics)
target_compile_features(CMakeSFMLProject PRIVATE cxx_std_20)
target_include_directories(CMakeSFMLProject PUBLIC src)

# Copy assets to build directory
add_custom_command(TARGET CMakeSFMLProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:CMakeSFMLProject>/assets)

if(WIN32 AND TARGET sfml-graphics)
    add_custom_command(TARGET CMakeSFMLProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-graphics>
        $<TARGET_FILE_DIR:CMakeSFMLProject>)
endif()

install(TARGETS CMakeSFMLProject)
