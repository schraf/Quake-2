cmake_minimum_required(VERSION 3.16)

project(quake2)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_subdirectory("client")
add_subdirectory("ctf")
add_subdirectory("game")
add_subdirectory("qcommon")
add_subdirectory("server")
add_subdirectory("ref_gl")
add_subdirectory("win32")

if(WIN32)
	add_executable(quake2 WIN32 $<TARGET_OBJECTS:win32>)
	target_link_libraries(quake2 wsock32 ws2_32 winmm)
endif()

target_link_libraries(quake2 qcommon server client)
