cmake_minimum_required(VERSION 3.16)
project(Eclipse-9 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
include_directories(${CMAKE_SOURCE_DIR}/src)


include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Set SFML to static linking
set(SFML_STATIC_LIBRARIES TRUE)

file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(Eclipse-9 ${SOURCES})

set_target_properties(Eclipse-9 PROPERTIES OUTPUT_NAME Eclipse-9)


target_link_libraries(Eclipse-9 PRIVATE sfml-graphics)
target_compile_features(Eclipse-9 PRIVATE cxx_std_20)
target_include_directories(Eclipse-9 PUBLIC src)

# Copy assets to build directory
add_custom_command(TARGET Eclipse-9 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Assets
    $<TARGET_FILE_DIR:Eclipse-9>/Assets)

    if(WIN32)
    add_custom_command(TARGET Eclipse-9 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-graphics>
        $<TARGET_FILE_DIR:Eclipse-9>)
    
    # Also copy sfml-system (graphics depends on it)
    add_custom_command(TARGET Eclipse-9 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-system>
        $<TARGET_FILE_DIR:Eclipse-9>)
        
    # Copy sfml-window (graphics depends on it too)
    add_custom_command(TARGET Eclipse-9 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-window>
        $<TARGET_FILE_DIR:Eclipse-9>)
elseif(UNIX AND NOT APPLE)
    # Copy SFML libraries for Linux
    add_custom_command(TARGET Eclipse-9 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-graphics>
        $<TARGET_FILE_DIR:Eclipse-9>)
    
    add_custom_command(TARGET Eclipse-9 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-system>
        $<TARGET_FILE_DIR:Eclipse-9>)
        
    add_custom_command(TARGET Eclipse-9 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-window>
        $<TARGET_FILE_DIR:Eclipse-9>)
endif()

install(TARGETS Eclipse-9)
