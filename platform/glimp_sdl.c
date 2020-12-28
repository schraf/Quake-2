#include "../ref_gl/gl_local.h"
#include "glimp_sdl.h"

sdl_state_t sdl_state;

void		GLimp_BeginFrame( float camera_separation )
{
}

void		GLimp_EndFrame( void )
{
}

int 		GLimp_Init( void *hinstance, void *hWnd )
{
	return 1;
}

void		GLimp_Shutdown( void )
{
	if (sdl_state.renderer != NULL)
	{
		SDL_DestroyRenderer(sdl_state.renderer);
		sdl_state.renderer = NULL;
	}

	if (sdl_state.window != NULL)
	{
		SDL_DestroyWindow(sdl_state.window);
		sdl_state.window = NULL;
	}
}

int		GLimp_SetMode (int *pwidth, int *pheight, int mode, qboolean fullscreen)
{
	int			width, height;
	Uint32		flags;

	ri.Con_Printf (PRINT_ALL, "Initializing OpenGL display\n");

	ri.Con_Printf (PRINT_ALL, "...setting mode %d:", mode);

	if (!ri.Vid_GetModeInfo ( &width, &height, mode ))
	{
		ri.Con_Printf( PRINT_ALL, " invalid mode\n" );
		return rserr_invalid_mode;
	}

	ri.Con_Printf (PRINT_ALL, " %d %d %s\n", width, height, fullscreen ? "FS" : "W");

	// destroy the existing window
	if (sdl_state.window)
		GLimp_Shutdown ();

	flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_FOCUS;

	if (fullscreen)
		flags |= SDL_WINDOW_FULLSCREEN;

	if (SDL_CreateWindowAndRenderer (width, height, flags, &sdl_state.window, &sdl_state.renderer))
	{
		ri.Con_Printf (PRINT_ALL, "fail to create window: %s\n", SDL_GetError());
		return rserr_invalid_mode;
	}

	*pwidth = width;
	*pheight = height;

	return rserr_ok;
}

void		GLimp_AppActivate( qboolean active )
{
}
