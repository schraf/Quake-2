cmake_minimum_required(VERSION 3.16)

project(win32)

add_library(win32 OBJECT
	cd_win.c
	conproc.c
	in_win.c
	net_wins.c
	q_shwin.c
	snd_win.c
	sys_win.c
	vid_dll.c
	vid_menu.c)
