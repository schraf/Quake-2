cmake_minimum_required(VERSION 3.16)

project(qcommon)

add_library(qcommon OBJECT
	cmd.c
	cmodel.c
	common.c
	crc.c
	cvar.c
	files.c
	md4.c
	net_chan.c
	pmove.c)
