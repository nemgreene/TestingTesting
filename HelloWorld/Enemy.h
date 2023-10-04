#define PLAY_USING_GAMEOBJECT_MANAGER
#pragma once
#include <string>
#include "Maths.h"
#include "SpriteManager.h"
#include "Gun.h"

class Enemy
{
private:
	float _speed;
	int _health;
	SpriteManager* _spriteManager;
	Gun* _equippedGun = nullptr;
	int _iEnemyId;
	//bullet frequency set
	float _frequency;

public:

	float _spawnTime;

	GameObject* enemyObject;

	Enemy();
	Enemy(Gun equippedGun, SpriteManager* spriteManager, int health, Vec2 position, std::string spriteName);

	void moveRandomly();
	void takeDamage(int damage);
	void destruct();
	void fireGun();

};

