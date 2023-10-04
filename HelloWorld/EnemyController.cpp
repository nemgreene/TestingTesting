#pragma once
#include "EnemyController.h"


EnemyController::EnemyController() {};


EnemyController::EnemyController(std::map<int, EnemySchema> constructorSchema, SpriteManager* spriteManager)
{
	_constructorSchema = constructorSchema;
	_spriteManager = spriteManager;
};

void EnemyController::spawnEnemies() {
	//for each type of enemy
	for (auto const& x : _constructorSchema)
	{
		////spawn as many enemies
		for (int i = 0; i < x.first; ++i)
		{
			x;
			std::cout << "test";
			Enemy iEnemy = Enemy(x.second.gun, _spriteManager, x.second.health, Vec2(i * 100, 250), x.second.sprite);
			enemies.push_back(&iEnemy);
		};

	}

};
void EnemyController::moveEnemies() {

	for (Enemy* enemyObj : enemies)
	{
		float tic = (abs(enemyObj->_spawnTime));
		if (enemyObj->_spawnTime + enemyObj->_spawnTime > _spriteManager->_deltaTime)
		{
			enemyObj->fireGun();
			enemyObj->_spawnTime = _spriteManager->_deltaTime;
		}
		enemyObj->moveRandomly();
	}
}