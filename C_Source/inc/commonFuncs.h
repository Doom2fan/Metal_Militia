/*
**  Vicious Doom - A GZDoom mod
**  Copyright (C) 2015  Chronos Ouroboros
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation; either version 2 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License along
**  with this program; if not, write to the Free Software Foundation, Inc.,
**  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef COMMONFUNCS_H
#define COMMONFUNCS_H

#include <ACS_ZDoom.h>

int KeyUp (int key);
int KeyDown (int key);
int KeyPressed (int key);

int UnusedTID (int start, int end);

accum GetVelocity ();

int Clamp (int x, int min, int max);
accum ClampAccum (accum x, accum min, accum max);
int ScaleValue (int x, int fromMin, int fromMax, int toMin, int toMax);
accum ScaleValueAccum (accum x, accum fromMin, accum fromMax, accum toMin, accum toMax);

/*accum ResizeV3D (accum len, vec3d vec*);
accum LengthV3D (vec3d vec*);*/

struct vec2d {
    accum x;
    accum y;
};
typedef struct vec2d vec2d;

struct vec3d {
    accum x;
    accum y;
    accum z;
};
typedef struct vec3d vec3d;

#endif