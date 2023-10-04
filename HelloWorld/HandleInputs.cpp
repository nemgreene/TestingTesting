#include "HandleInputs.h"


void handleInputs(Vec2 vPlayerPos, Vec2 vAimVector, Gun* primaryGun)
{
	//left click
	if (Play::KeyPressed(VK_LBUTTON))
	{
		primaryGun->spawnBullet(vPlayerPos, vAimVector);

	}
}