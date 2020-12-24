cmake_minimum_required(VERSION 3.16)

project(game)

add_library(game SHARED
	g_entity.c
	g_main.c
	p_client.c
	p_view.c
	q_shared.c)

target_compile_definitions(game PRIVATE GAME_BUILD)
