#pragma once
#include "EnemyController.h"



EnemyController::EnemyController() {};


EnemyController::EnemyController( SpriteManager* spriteManager)
{
	EnemyController::_spriteManager = spriteManager;
};

void EnemyController::spawnEnemies(std::map<int, EnemySchema> constructorSchema) {
	//for each type of enemy
	for (auto const& x : constructorSchema)
	{
		////spawn as many enemies
		for (int i = 0; i < x.first; ++i)
		{
			Enemy iEnemy = Enemy(x.second.gun, EnemyController::_spriteManager, x.second.health, Vec2(i * 100 + 200, 250), x.second.sprite);
			iEnemy._equippedGun->_spriteName = x.second.gun._spriteName;

			EnemyController::_enemies.push_back(&iEnemy);
		};

	}

};
void EnemyController::moveEnemies() {


	for (Enemy* enemyObj : EnemyController::_enemies)
	{
		enemyObj->incrementSpawn();
		//enemyObj->moveRandomly();
	}
	//for (Enemy enemyObj : EnemyController::_enemies)
	//{
	//	float tic = (abs(enemyObj->_spawnTime));
	//	if (enemyObj->_spawnTime + enemyObj->_spawnTime > EnemyController::_spriteManager->_deltaTime)
	//	{
	//		enemyObj->fireGun();
	//		enemyObj->_spawnTime = EnemyController::_spriteManager->_deltaTime;
	//	}
	//	enemyObj->moveRandomly();
	//}
}
//void EnemyController::getEnemies() {
//	EnemyController::_enemies;
//	std::vector<Enemy*>* ref = &_enemies;
//
//};
std::vector<Enemy*>* EnemyController::getEnemies()
{
	return(&_enemies);
};