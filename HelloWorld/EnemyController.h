#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Gun.h"
#include "SpriteManager.h"
#include "Map.h"

class EnemyController
{
private:

	SpriteManager* _spriteManager;
	GameState* _gameState;

public:

	void moveEnemies();
	std::map<int, float> _enemyIds;
	int playerId;


	EnemyController();
	EnemyController(SpriteManager* spriteManager, GameState* gameState);

	void spawnEnemy(GameObjectType type, Point2f origin, int radius, std::string spriteName);
	void fireGun(int id);
	void checkPlayerCollisions();
};