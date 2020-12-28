// sys_null.h -- null system driver to aid porting efforts

#include "../qcommon/qcommon.h"
#include "SDL.h"

int			curtime;
unsigned	sys_frame_time;

static void	*game_library;

void Sys_mkdir (char *path)
{
}

void Sys_Error (char *error, ...)
{
	va_list		argptr;

	printf ("Sys_Error: ");
	va_start (argptr,error);
	vprintf (error,argptr);
	va_end (argptr);
	printf ("\n");

	exit (1);
}

void Sys_Quit (void)
{
	SDL_Quit ();
	exit (0);
}

void	Sys_UnloadGame (void)
{
	if (game_library != NULL)
	{
		SDL_UnloadObject (game_library);
		game_library = NULL;
	}
}

void	*Sys_GetGameAPI (void *parms)
{
	void	*(*GetGameAPI) (void *);
	char	name[MAX_OSPATH];
	char	*path;
	char	*cwd;

#if defined __WINDOWS__
	const char *gamename = "game.dll";
#else
	const char *gamename = "game.so";
#endif

#ifdef NDEBUG
	const char *debugdir = "build/Release";
#else
	const char *debugdir = "build/Debug";
#endif

	if (game_library)
		Com_Error (ERR_FATAL, "Sys_GetGameAPI without Sys_UnloadingGame");

	// check the current debug directory first for development purposes
	cwd = SDL_GetBasePath ();
	Com_sprintf (name, sizeof(name), "%s/%s/%s", cwd, debugdir, gamename);
	game_library = SDL_LoadObject ( name );
	if (game_library)
	{
		Com_DPrintf ("LoadLibrary (%s)\n", name);
	}
	else
	{
		// check the current directory for other development purposes
		Com_sprintf (name, sizeof(name), "%s/%s", cwd, gamename);
		game_library = SDL_LoadObject ( name );
		if (game_library)
		{
			Com_DPrintf ("LoadLibrary (%s)\n", name);
		}
		else
		{
			// now run through the search paths
			path = NULL;
			while (1)
			{
				path = FS_NextPath (path);
				if (!path)
					return NULL;		// couldn't find one anywhere
				Com_sprintf (name, sizeof(name), "%s/%s", path, gamename);
				game_library = SDL_LoadObject (name);
				if (game_library)
				{
					Com_DPrintf ("LoadLibrary (%s)\n",name);
					break;
				}
			}
		}
	}

	GetGameAPI = SDL_LoadFunction (game_library, "GetGameAPI");

	if (!GetGameAPI)
	{
		Sys_UnloadGame ();
		return NULL;
	}

	return GetGameAPI (parms);
}

char *Sys_ConsoleInput (void)
{
	return NULL;
}

void	Sys_ConsoleOutput (char *string)
{
	char	text[256];

	if (!dedicated || !dedicated->value)
		return;

	SDL_Log(string);
}

void Sys_SendKeyEvents (void)
{
	sys_frame_time = SDL_GetTicks ();	// FIXME: should this be at start?
}

void Sys_AppActivate (void)
{
}

void Sys_CopyProtect (void)
{
}

char *Sys_GetClipboardData( void )
{
	return NULL;
}

char	*Sys_FindFirst (char *path, unsigned musthave, unsigned canthave)
{
	return NULL;
}

char	*Sys_FindNext (unsigned musthave, unsigned canthave)
{
	return NULL;
}

void	Sys_FindClose (void)
{
}

void	Sys_Init (void)
{
	Uint32		flags;

	flags = SDL_INIT_TIMER | SDL_INIT_EVENTS;

	if (!dedicated->value)
		flags |= SDL_INIT_AUDIO & SDL_INIT_VIDEO & SDL_INIT_GAMECONTROLLER;

	if (SDL_Init(flags) != 0)
		Sys_Error ("SDL_Init failed: %s\n", SDL_GetError());
}

//=============================================================================

int main (int argc, char **argv)
{
	int				time, oldtime, newtime;

	Qcommon_Init (argc, argv);
	oldtime = Sys_Milliseconds ();

	while (1)
	{
		do
		{
			newtime = Sys_Milliseconds ();
			time = newtime - oldtime;
		} while (time < 1);

		Qcommon_Frame (time);

		oldtime = newtime;
	}

	return 0;
}


