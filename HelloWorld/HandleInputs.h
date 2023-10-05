#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include <string>
#include "Maths.h"
#include "Play.h"
#include "Gun.h"
#include "ChickenGun.h"

//pawn class
// characeter
//	enemies
// movePawn (vector)
bool toggle = false;

void handleInputs(Vec2 vPlayerPos, Vec2 vAimVector, Gun* primaryGun, Gun* secondaryGun)
{
	//left click
	if (Play::KeyPressed(VK_LBUTTON))
	{
		primaryGun->spawnBullet(vPlayerPos, vAimVector);
	}
	//right click
	if (Play::KeyPressed(VK_RBUTTON))
	{
		secondaryGun->spawnBullet(vPlayerPos, vAimVector);
	}
}
