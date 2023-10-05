#pragma once
#include "Gun.h"

class ChickenGun : public Gun
{
public:
	ChickenGun(enum GameObjectType bulletType, std::string spriteName, SpriteManager* spriteManager);
	//overwriting moveBullets
	void spawnBullet(Vec2 vOrigin, Vec2 vDir);
	void moveBullets();
	
private:
	float _bulletSpeed = 2;
};
