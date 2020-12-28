cmake_minimum_required(VERSION 3.16)

project(ref_gl)

add_library(ref_gl SHARED
	gl_draw.c
	gl_image.c
	gl_light.c
	gl_mesh.c
	gl_model.c
	gl_rmain.c
	gl_rmisc.c
	gl_rsurf.c
	gl_warp.c
	../game/q_shared.c
	../platform/glimp_sdl.c
	../platform/qgl_sdl.c
	../platform/q_shsdl.c)

if(WIN32)
target_link_libraries(ref_gl opengl32)
endif()

target_link_libraries(ref_gl SDL2 uv)
target_compile_definitions(ref_gl PRIVATE REF_BUILD)
target_include_directories(ref_gl PRIVATE
	../deps/libuv/include
	../deps/sdl/include)
