#ifndef H_ROTATIONS
#define H_ROTATIONS
/*
  This code shows how to calculate a rotation of a SDL_Surface.

  Copyright (C) 2006 Florent Humbert http://www.developpez.net/forums/member.php?u=103584

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#include "SDL/SDL.h"
/*effectue une rotation centrale, alloue automatiquement la mémoire*/
SDL_Surface* SDL_RotationCentralN(SDL_Surface* origine, float angle);
/*effectue une rotation centrale d'angle en degré, alloue automatiquement la mémoire*/
SDL_Surface* SDL_RotationCentral(SDL_Surface* origine, float angle);

#endif
