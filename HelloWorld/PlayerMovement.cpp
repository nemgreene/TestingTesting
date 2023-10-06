#include "PlayerMovement.h"
#include "Utilities.h"
#include "Map.h"
void HandlePlayerMovement()
{
	GameObject& player = Play::GetGameObjectByType(TYPE_PLAYER);
	Vector2D tempVelocity = { 0 , 0 };
	int moveSpeed = 2;
	if (Play::KeyDown('W'))
	{
		tempVelocity.y = -2;
	}
	if (Play::KeyDown('S'))
	{
		tempVelocity.y = 2;
	}
	if (Play::KeyDown('A'))
	{
		tempVelocity.x = -2;
	}
	if (Play::KeyDown('D'))
	{
		tempVelocity.x = 2;
	}

	tempVelocity = tempVelocity * moveSpeed;
	if (Play::KeyPressed(VK_SPACE))
	{
		tempVelocity *= 50;
	}
	if (tempVelocity.x != 0 && tempVelocity.y != 0)
	{
		tempVelocity.x /= 1.414;
		tempVelocity.y /= 1.414;
	}
	player.velocity = tempVelocity;
	if (MaxsCollisionChecker({ player.pos.x, player.pos.y }, simpleCollisionMap))
		player.pos = player.oldPos;
}