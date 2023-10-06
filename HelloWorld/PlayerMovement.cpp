#include "PlayerMovement.h"
#include "Utilities.h"
#include "Map.h"
void HandlePlayerMovement(float _elapsedTime)
{
	GameObject& player = Play::GetGameObjectByType(TYPE_PLAYER);
	Vector2D tempVelocity = { 0 , 0 };
	int moveSpeed;
	if (player.Dashing == false)
	{
		moveSpeed = 2;
		player.radius = 20;
	}
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
	if (tempVelocity.x != 0 && tempVelocity.y != 0)
	{
		tempVelocity.x /= 1.414;
		tempVelocity.y /= 1.414;
	}

	// Dash function
	if (Play::KeyPressed(VK_SPACE) && player.Timer < 1)
	{
		player.Dashing = true;
		player.radius = 0;
	}
	if (player.Dashing == true)
	{
		moveSpeed = 10;
		player.Timer += _elapsedTime;
	}
	if (player.Timer >= 0.1)
	{
		player.Dashing = false;
		player.Timer += _elapsedTime;
	}
	if (player.Timer >= 3)
	{
		player.Timer = 0;
	}



	tempVelocity = tempVelocity * moveSpeed;
	player.velocity = tempVelocity;
	if (MaxsCollisionChecker({player.pos}, simpleCollisionMap))
		player.pos = player.oldPos;
}