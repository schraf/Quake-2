cmake_minimum_required(VERSION 3.16)

project(quake2)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory("deps/sdl")
add_subdirectory("deps/enet")
add_subdirectory("deps/libuv")
add_subdirectory("client")
add_subdirectory("game")
add_subdirectory("qcommon")
add_subdirectory("server")
add_subdirectory("ref_gl")
add_subdirectory("platform")
add_subdirectory("tools")

add_executable(quake2 $<TARGET_OBJECTS:platform>)
target_link_libraries(quake2 qcommon server client SDL2 SDL2main uv enet)
