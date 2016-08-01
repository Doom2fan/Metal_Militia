/*
**  Metal Militia - A GZDoom mod
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

#include "includes.h"
#include "misc.h"

Script_C void MM_SpeedScript ENTER () {
    // Not needed or desired in TitleMaps.
    if (GameType () == GAME_TITLE_MAP)
        return;
    
    int health;
    
    while (true) {
        health = GetActorProperty (0, APROP_Health);
        
        if (health <= 20)
            GiveInventory (s"MM_Dying", 9999999);
        else
            TakeInventory (s"MM_Dying", 9999999);
        
        Delay(1);
    }
}

Script_C void MM_WaterScript ENTER () {
    // Not needed or desired in TitleMaps.
    if (GameType () == GAME_TITLE_MAP)
        return;
    
    while (true) {
        if (GetActorProperty(0, APROP_Waterlevel) > 2) // if underwater...
            GiveInventory (s"MM_IsUnderwater", 1); // give MM_IsUnderwater

        else if (GetActorProperty(0, APROP_Waterlevel) <= 2) // if not underwater
            TakeInventory (s"MM_IsUnderwater", 1); // take MM_IsUnderwater
        
        Delay (1);
    }
}

Script_C void MM_Keys ENTER () {
    // Not needed or desired in TitleMaps.
    if (GameType () == GAME_TITLE_MAP)
        return;
    
    while (true) {
        if (KeyPressed (BT_RELOAD))
            UseInventory (s"MM_ReloadKey");
        
        Delay (1);
    }
}

/*Script_C void MM_SetProjectilePitch () {
    accum x = GetActorVelX (0); accum y = GetActorVelY (0); accum z = GetActorVelZ (0);
    accum angle = GetActorAngle (0);
    accum pitch = 0;

    // [BB] Calculate the pitch using spherical coordinates.
    if (z || x || y)
        pitch = AtanA (z / FixedSqrt (x * x + y * y)) / piA * 180.0k;
            
    // Correcting pitch if model is moving backwards
    if (x || y) {
        if ((x * CosA (angle * piA / 180.0k) + y * SinA (angle * piA / 180.0k)) / FixedSqrt (x * x + y * y) < 0.0k)
            pitch *= -1.0k;
    }
    else
        pitch = AbsA (pitch);

    //pitch = -pitch;

    SetActorPitch (0, ScaleValueAccum (pitch, -90.0k, 90.0k, -0.25k, 0.25k));
}

Script_C void AAAA () {
    Print ("%k", GetActorPitch (0));
}*/

#ifdef DEBUG
Script_C void MM_DebugVelocity () {
    accum x = 0, y = 0, z = 0,
        angle = 0, speed = 0;
    while (true) {
        x = GetActorVelX (0);
        y = GetActorVelY (0);
        z = GetActorVelZ (0);
        speed = x * x + y * y + z * z;
        Print ("Velocity: %k\n", FixedSqrt (speed));
        
        Delay (1);
    }
}

Script_C void MM_DebugVelocityInKmH () {
    accum x = 0, y = 0, z = 0,
        speed = 0, speed2;
    while (true) {
        x = GetActorVelX (0);
        y = GetActorVelY (0);
        z = GetActorVelZ (0);
        speed = x * x + y * y + z * z;
        speed2 = 3.6k * ((FixedSqrt (speed) * 35.0k) / 64.0k);
        Print ("Velocity: %k km/h\n", speed2);
        
        Delay (1);
    }
}
#endif