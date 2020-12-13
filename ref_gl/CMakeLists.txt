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
	../game/q_shared.c)

if(WIN32)
	target_sources(ref_gl PRIVATE
		../win32/qgl_win.c
		../win32/glw_imp.c
		../win32/q_shwin.c)
	target_link_libraries(ref_gl winmm)
endif()

target_compile_definitions(ref_gl PRIVATE REF_BUILD)
