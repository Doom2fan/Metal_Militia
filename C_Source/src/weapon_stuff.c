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
#include "weapon_stuff.h"

string WeaponName [] = {
    s""
};

string DummyWeapons [] = {
    s""
};

int GlobalVar LastWeapon [MAX_PLAYERS];

int GetWeaponName () {
    for (int x = 0; x < ArraySize (DummyWeapons); x++)
        if (CheckWeapon (DummyWeapons [x])) 
            return -1;
    
    for (int y = 0; y < ArraySize (WeaponName); y++)
        if (CheckWeapon (WeaponName [y]))
            return y;
    
    return -1;
}

void ChangeLastWeapon (bool mode) {
    int weaponNumber = 0;
    if (mode) {
        weaponNumber = LastWeapon [PLN];
        if (weaponNumber < 0 || weaponNumber > ArraySize (WeaponName) - 1)
            return;
        SetWeapon (WeaponName [weaponNumber]);
    } else {
        weaponNumber = GetWeaponName ();
        if (weaponNumber < 0 || weaponNumber > ArraySize (WeaponName) - 1)
            return;
        else
            LastWeapon [PLN] = weaponNumber;
    }
}

void DisableWeapon (string meh, string blah) {
    if (CheckWeapon (meh)) {
        TakeInventory (blah, 99999);
        ChangeLastWeapon (1);
        return;
    }
    GiveInventory (meh, 1);
    SetWeapon (meh);
    ChangeLastWeapon (0);
}

// Scripts
// SynthFire stuff
Script_C void MM_SynthFire () {
    while (TRUE) {
        if (!CheckInventory (s"MM_SynthFireActive"))
            return;
        
        if (KeyDown (BT_ATTACK) && !CheckInventory (s"MM_SynthFireLeft"))
            GiveInventory (s"MM_SynthFireLeft", 1);
        
        if (KeyDown (BT_ALTATTACK) && !CheckInventory (s"MM_SynthFireRight"))
            GiveInventory (s"MM_SynthFireRight", 1);
        
        Delay (1);
        
        if (KeyUp (BT_ATTACK) && CheckInventory (s"MM_SynthFireLeft"))
            TakeInventory (s"MM_SynthFireLeft", 1);
        
        if (KeyUp (BT_ALTATTACK) && CheckInventory (s"MM_SynthFireRight"))
            TakeInventory (s"MM_SynthFireRight", 1);
    }
}

Script_C int MM_SynthFireAllowChange () {
    if (!CheckInventory (s"MM_SynthFireRightReloading") || CheckInventory (s"MM_SynthFireLeftReloading"))
        return 1;
    else
        return 0;
}

Script_C void MM_RecoilPitch (accum offset) { // Called like this in code: TNT1 A 0 ACS_NamedExecuteAlways ("MM_RecoilPitch", 0, 0.5 * 65535)
    accum oldPitch = GetActorPitch (0);
    accum scaledOffset = ScaleValueAccum (offset, -90.0k, 90.0k, -0.25k, 0.25k);
    accum newPitch = ClampAccum (oldPitch - scaledOffset, -0.25k, 0.25k);
    
    SetActorPitch (0, newPitch);
}

/*Script_C void MM_SpawnTracer () {
    vec3d puff;
    vec3d shooter;
    vec3d diff;
    accum angle;
    accum pitch;
    int vspeed = 0;
    int tracerTID = UniqueTID ();
    int shooterTempTID = UniqueTID ();
    int shooterTID;

    puff.x = GetActorX (0);
    puff.y = GetActorY (0);
    puff.z = GetActorZ (0);

    if (!SetActivatorToTarget (0))
        return;

    shooter.x = GetActorX (0);
    shooter.y = GetActorY (0);
    shooter.z = GetActorZ (0);
    shooterTID = ActivatorTID ();
    Thing_ChangeTID (0, shooterTempTID);

    diff.x = MaxA (puff.x, shooter.x) - MinA (puff.x, shooter.x);
    diff.y = MaxA (puff.y, shooter.y) - MinA (puff.y, shooter.y);
    diff.z = MaxA (puff.z, shooter.z) - MinA (puff.z, shooter.z);

    angle = FixedSqrt (diff.x * diff.x + diff.y * diff.y);

    Spawn (s"MM_BaseTracer", shooter.x, shooter.y, shooter.z, tracerTID, (int) (angle >> 2))

    SetActivator (tracerTID);
    SetPointer (AAPTR_TARGET, shooterTempTID);

    vx = angle * FixedSqrt (diff.x * diff.x + diff.z * diff.z)
    vy = FixedMul (finecosine[pitch>>ANGLETOFINESHIFT], finesine[an>>ANGLETOFINESHIFT]);
    vz = -finesine[pitch>>ANGLETOFINESHIFT];
    speed = MissileActor->Speed;

    vec3d vec ()

    ResizeV3D (GetActorProperty (0, APROP_Speed), )
    //SpawnProjectile (0, s"MM_BaseTracer", (int) (angle >> 2), 0, vspeed, 0, 0);
}*/