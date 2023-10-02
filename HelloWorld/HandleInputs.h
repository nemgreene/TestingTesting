#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include <string>
#include "Maths.h"
#include "Play.h"
#include "Gun.h"

// 0000JKK
//
void handleInputs(Vec2 vPlayerPos, Vec2 vAimVector, Gun* primaryGun);


void handleInputs(Vec2 vPlayerPos, Vec2 vAimVector, Gun* primaryGun)
{
	//left click
	if (Play::KeyPressed(VK_LBUTTON))
	{
		primaryGun->spawnBullet(vPlayerPos, vAimVector);
		primaryGun->spawnBullet(vPlayerPos, vAimVector);
		//primary.makeBullet(origin, vector)
		//int iBullet = Play::CreateGameObject(TYPE_BULLET, { vPlayerPos.GetX(), vPlayerPos.GetY() }, 50, "acid_bullets_4");
		//pass to spriteManager
		// 
		//fire primary gun

	}
}