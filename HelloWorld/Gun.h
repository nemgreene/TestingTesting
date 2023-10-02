#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include <string>
#include "Maths.h"
#include "Play.h"
class Gun
{
public:

	Gun(enum GameObjectType, std::string spriteName);
	//generate a bullet
	//add bullet to _bullets 
	void spawnBullet(Vec2 vOrigin, Vec2 vDir);

	//iterate over all children bullets
	//move them along their own own vector
	//run every tick
	void moveBullets();
private:
	//ids of all spawend bullets child to this gun
	enum GameObjectType _bulletType;
	float _bulletSpeed;
	std::string _spriteName;


};

