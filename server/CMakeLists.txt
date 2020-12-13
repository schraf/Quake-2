cmake_minimum_required(VERSION 3.16)

project(server)

add_library(server OBJECT
	sv_ccmds.c
	sv_ents.c
	sv_game.c
	sv_init.c
	sv_main.c
	sv_send.c
	sv_user.c
	sv_world.c)
