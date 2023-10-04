#pragma once

#include "EnemyController.h"
#include "Utilities.h"
#include "Enemy.h"
#include "SpriteManager.h"


class EnemyController
{
private:
	std::map<int, EnemySchema> _constructorSchema;
	SpriteManager* _spriteManager;

public:
	std::vector<Enemy*> enemies;

	EnemyController();

	EnemyController(std::map<int, EnemySchema> constructorSchema, SpriteManager* spriteManager);

	void spawnEnemies();
	void moveEnemies();

};