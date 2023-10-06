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

		int randomRoll = (std::rand() % 2) + 1;

		if (randomRoll == 1)
		{
			Play::PlayAudio("cluck_01");
		}
		else
		{
			Play::PlayAudio("cluck_02");
		}

	}

	//right click
	if (Play::KeyPressed(VK_RBUTTON))
	{
		secondaryGun->spawnBullet(vPlayerPos, vAimVector);
	
		int randomRoll = (std::rand() % 2) + 1;

		if (randomRoll == 1)
		{
			Play::PlayAudio("zap_01");
		}
		else
		{
			Play::PlayAudio("zap_02");
		}

	}
}
