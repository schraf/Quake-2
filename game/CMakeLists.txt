cmake_minimum_required(VERSION 3.16)

project(game)

add_library(game SHARED
	g_ai.c
	g_chase.c
	g_cmds.c
	g_combat.c
	g_func.c
	g_items.c
	g_main.c
	g_misc.c
	g_monster.c
	g_phys.c
	g_save.c
	g_spawn.c
	g_svcmds.c
	g_target.c
	g_trigger.c
	g_turret.c
	g_utils.c
	g_weapon.c
	m_actor.c
	m_flash.c
	m_infantry.c
	m_move.c
	m_soldier.c
	p_client.c
	p_hud.c
	p_trail.c
	p_view.c
	p_weapon.c
	q_shared.c)

target_compile_definitions(game PRIVATE GAME_BUILD)
