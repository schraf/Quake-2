cmake_minimum_required(VERSION 3.16)

project(client)

add_library(client OBJECT
	cl_cin.c
	cl_ents.c
	cl_fx.c
	cl_input.c
	cl_inv.c
	cl_main.c
	cl_newfx.c
	cl_parse.c
	cl_pred.c
	cl_scrn.c
	cl_tent.c
	cl_view.c
	console.c
	keys.c
	menu.c
	qmenu.c
	snd_dma.c
	snd_mem.c
	snd_mix.c
	x86.c
	../game/q_shared.c
	../game/m_flash.c)
