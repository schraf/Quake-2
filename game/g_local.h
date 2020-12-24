/*
Copyright (C) 1997-2001 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
// g_local.h -- local definitions for game module

#include "q_shared.h"

// define GAME_INCLUDE so that game.h does not define the
// short, server-visible gclient_t and edict_t structures,
// because we define the full size ones in this file
#define	GAME_INCLUDE
#include "game.h"

// the "gameversion" client command will print this plus compile date
#define	GAMEVERSION	"baseq2"

// protocol bytes that can be directly added to messages
#define	svc_muzzleflash		1
#define	svc_muzzleflash2	2
#define	svc_temp_entity		3
#define	svc_layout			4
#define	svc_inventory		5
#define	svc_stufftext		11

//==================================================================

#define	FRAMETIME		0.1

// memory tags to allow dynamic memory to be cleaned up
#define	TAG_GAME	765		// clear when unloading the dll
#define	TAG_LEVEL	766		// clear when loading a new level

//
// this structure is left intact through an entire game
// it should be initialized at dll load time, and read/written to
// the server.ssv file for savegames
//
typedef struct
{
	gclient_t	*clients;		// [maxclients]

	int			framenum;
	int			time;

	// store latched cvars here that we want to get at often
	int			maxclients;
	int			maxentities;
} game_locals_t;

extern	game_locals_t	game;
extern	game_import_t	gi;
extern	game_export_t	globals;
extern	edict_t			*g_edicts;

#define	FOFS(x) (intptr_t)&(((edict_t *)0)->x)

extern	cvar_t	*maxentities;
extern	cvar_t	*maxclients;
extern	cvar_t	*gravity;
extern	cvar_t	*maxvelocity;
extern	cvar_t	*rollspeed;
extern	cvar_t	*rollangle;
extern	cvar_t	*run_pitch;
extern	cvar_t	*run_roll;

//
// fields are needed for spawning from the entity string
// and saving / loading games
//
#define FFL_SPAWNTEMP		1
#define FFL_NOSPAWN			2

typedef enum {
	F_INT,
	F_FLOAT,
	F_LSTRING,			// string on disk, pointer in memory, TAG_LEVEL
	F_GSTRING,			// string on disk, pointer in memory, TAG_GAME
	F_VECTOR,
	F_ANGLEHACK,
	F_EDICT,			// index on disk, pointer in memory
	F_ITEM,				// index on disk, pointer in memory
	F_CLIENT,			// index on disk, pointer in memory
	F_FUNCTION,
	F_MMOVE,
	F_IGNORE
} fieldtype_t;

typedef struct
{
	char	*name;
	int		ofs;
	fieldtype_t	type;
	int		flags;
} field_t;


extern	field_t fields[];

// g_entity.c
edict_t *G_Find (edict_t *from, int fieldofs, char *match);
void G_InitEdict (edict_t *e);
edict_t *G_Spawn (void);
void G_FreeEdict (edict_t *ed);
void SpawnEntities (char *mapname, char *entities, char *spawnpoint);

// p_client.c
void ClientBegin (edict_t *ent);
void ClientUserinfoChanged (edict_t *ent, char *userinfo);
qboolean ClientConnect (edict_t *ent, char *userinfo);
void ClientDisconnect (edict_t *ent);
void ClientThink (edict_t *ent, usercmd_t *ucmd);

// p_view.c
void ClientEndServerFrame (edict_t *ent);


//============================================================================

// client data that stays across multiple level loads
typedef struct
{
	char		userinfo[MAX_INFO_STRING];
	char		netname[16];

	qboolean	connected;			// a loadgame will leave valid entities that
									// just don't have a connection yet
} client_persistant_t;

// client data that stays across deathmatch respawns
typedef struct
{
	int			enterframe;			// level.framenum the client entered the game
	vec3_t		cmd_angles;			// angles sent over in the last command
} client_respawn_t;

// this structure is cleared on each PutClientInServer(),
// except for 'client->pers'
struct gclient_s
{
	// known to server
	player_state_t	ps;				// communicated by server to clients
	int				ping;

	// private to game
	client_persistant_t	pers;
	client_respawn_t	resp;
	pmove_state_t		old_pmove;	// for detecting out-of-pmove changes

	int			buttons;
	int			oldbuttons;
	int			latched_buttons;

	vec3_t		v_angle;			// aiming direction
	vec3_t		oldviewangles;
	vec3_t		oldvelocity;
};


struct edict_s
{
	entity_state_t	s;
	struct gclient_s	*client;	// NULL if not a player
									// the server expects the first part
									// of gclient_s to be a player_state_t
									// but the rest of it is opaque

	qboolean	inuse;
	int			linkcount;

	// FIXME: move these fields to a server private sv_entity_t
	link_t		area;				// linked to a division node or leaf

	int			num_clusters;		// if -1, use headnode instead
	int			clusternums[MAX_ENT_CLUSTERS];
	int			headnode;			// unused if num_clusters != -1
	int			areanum, areanum2;

	//================================

	int			svflags;
	vec3_t		mins, maxs;
	vec3_t		absmin, absmax, size;
	solid_t		solid;
	int			clipmask;
	edict_t		*owner;


	// DO NOT MODIFY ANYTHING ABOVE THIS, THE SERVER
	// EXPECTS THE FIELDS IN THAT ORDER!

	//================================
	char		*classname;
	int			movetype;
	float		freetime;			// sv.time when the object was freed
	vec3_t		velocity;
	float		gravity;		// per entity gravity multiplier (1.0 is normal)
								// use for lowgrav artifact, flares
	int			viewheight;		// height above origin where eyesight is determined
	int			light_level;
};

