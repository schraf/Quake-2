/*
Copyright (C) 2020 Marc Schraffenberger

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
#include "../qcommon/qcommon.h"
#include "enet/enet.h"

void	NET_Init (void)
{
}

void	NET_Shutdown (void)
{
}

void	NET_Config (qboolean multiplayer)
{
}

qboolean	NET_GetPacket (netsrc_t sock, netadr_t *net_from, sizebuf_t *net_message)
{
	return false;
}

void	NET_SendPacket (netsrc_t sock, int length, void *data, netadr_t to)
{
}

qboolean	NET_CompareAdr (netadr_t a, netadr_t b)
{
	return false;
}

qboolean	NET_CompareBaseAdr (netadr_t a, netadr_t b)
{
	return false;
}

qboolean	NET_IsLocalAddress (netadr_t adr)
{
	return false;
}

char		*NET_AdrToString (netadr_t a)
{
}

qboolean	NET_StringToAdr (char *s, netadr_t *a)
{
	return false;
}

void		NET_Sleep(int msec)
{
}
