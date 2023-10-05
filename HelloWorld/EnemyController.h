#pragma once
#include "Enemy.h"
#include "SpriteManager.h"
#include "EnemySchema.h"
#include "Gun.h"

class EnemyController
{
private:

	SpriteManager* _spriteManager;

public:
	std::vector<Enemy*> _enemies;

	EnemyController();

	EnemyController( SpriteManager* spriteManager);

	void spawnEnemies(std::map<int, EnemySchema> constructorSchema);
	void moveEnemies();
	std::vector<Enemy*>* getEnemies();


};