#pragma once
#include "Gun.h"

class ChickenGun : public Gun
{
public:
	ChickenGun(enum GameObjectType bulletType, std::string spriteName, SpriteManager* spriteManager);
	//overwriting moveBullets
	void spawnBullet(Vec2 vOrigin, Vec2 vDir);
	void moveBullets(float _elapsedTime);
	
private:
	float _bulletSpeed = 2;
	float _gunCooldown = 2;
};
