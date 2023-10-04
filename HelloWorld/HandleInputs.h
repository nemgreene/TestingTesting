#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include <string>
#include "Maths.h"
#include "Play.h"
#include "Gun.h"

//pawn class
// characeter
//	enemies
// movePawn (vector)
bool toggle = false;

void handleInputs(Vec2 vPlayerPos, Vec2 vAimVector, Gun* primaryGun)
{
	//left click
	if (Play::KeyPressed(VK_LBUTTON))
	{
		primaryGun->spawnBullet(vPlayerPos, vAimVector);

	}
}