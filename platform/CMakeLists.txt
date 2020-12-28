cmake_minimum_required(VERSION 3.16)

project(platform)

add_library(platform OBJECT
	in_null.c
	music_null.c
	net_enet.c
	q_shsdl.c
	snddma_null.c
	sys_sdl.c
	vid_null.c)

target_include_directories(platform PRIVATE
	../deps/libuv/include
	../deps/enet/include
	../deps/sdl/include)