#define PLAY_USING_GAMEOBJECT_MANAGER
#pragma once
#include <string>
#include "Maths.h"
#include "SpriteManager.h"
#include "Utilities.h"

class Enemy;


//class EnemyHandler;



class Gun
{
public:

	Gun();
	
	Gun(GameObjectType bulletType, std::string spriteName, SpriteManager* spriteManager);
	//generate a bullet
	//add bullet to _bullets 
	void spawnBullet(Vec2 vOrigin, Vec2 vDir);

	//iterate over all children bullets
	//move them along their own own vector
	//run every tick
	void moveBullets(std::vector<Enemy*>* enemies);
	GameObjectType _bulletType = GameObjectType::TYPE_PLAYER;
	float _bulletSpeed;
	std::string _spriteName;
	SpriteManager* _spriteManager;
private:
	//ids of all spawend bullets child to this gun


};

