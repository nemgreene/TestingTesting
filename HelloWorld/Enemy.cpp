#define PLAY_USING_GAMEOBJECT_MANAGER
#pragma once
#include "Play.h"
#include "Enemy.h"
#include "Maths.h"
#include "Gun.h"
#include "Utilities.h"
#include <random>




Enemy::Enemy() {};

Enemy::Enemy(Gun equippedGun, SpriteManager* spriteManager, int health, Vec2 position, std::string spriteName) {

	Gun enemyGun = Gun(equippedGun._bulletType, equippedGun._spriteName, spriteManager);
	Enemy::_equippedGun = &enemyGun;

	const char* PS = spriteName.c_str();
	Enemy::_iEnemyId = Play::CreateGameObject(GameObjectType::TYPE_ENEMY, {position.GetX(), position.GetY()}, 50, PS );

	Enemy::_spriteManager = spriteManager;
	spriteManager->addSprite(_iEnemyId, spriteName, 2);
	//_gameObject = enemyObject;
	Enemy::_health = health;
	Enemy::_spawnTime = 1.0f;
	Enemy::_frequency = 1;
	Enemy::enemyObject = &Play::GetGameObject(_iEnemyId);


}
//handles movement and firing
void Enemy::moveRandomly()
{

	GameObject& obj = Play::GetGameObject(_iEnemyId);

	if (Enemy::_spawnTime >= 10)
	{
		Enemy::fireGun();
	}


	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(-1, 1); // define the range
	obj.velocity.x += distr(gen) * .25;
	obj.velocity.y += distr(gen)  * .25 ;
	obj.velocity.x = (obj.velocity.x < -1) ? -1 : (obj.velocity.x > 1) ? 1 : obj.velocity.x;
	obj.velocity.y = (obj.velocity.y < -1) ? -1 : (obj.velocity.y > 1) ? 1 : obj.velocity.y;
	//Play::UpdateGameObject(obj);

	if (Play::IsLeavingDisplayArea(obj)) {
		obj.pos = obj.oldPos;
	};

	Play::UpdateGameObject(obj);

	//when to fire gun
}
void Enemy::takeDamage(int damage)
{
	if (_health - damage >= 0) {
		Enemy::destruct();
	}
	else {
		_health -= damage;
	}
}
void Enemy::destruct()
{
	//remove from sprite manager
	_spriteManager->deleteSprites(_iEnemyId);
	GameObject& target = Play::GetGameObject(_iEnemyId);
	
	//set type to destroyed to be cleaned up by janitor
	target.type = GameObjectType::TYPE_DESTROYED;
}

//just generates the actual bullets from origin
void Enemy::fireGun()
{

	GameObject& player = Play::GetGameObjectByType(TYPE_PLAYER);
	Vec2 vEnemyAim = utilHandleCursorDirection(Vec2(enemyObject->pos), Vec2(player.pos));
	//create bullet objec
	
	int iBullet = Play::CreateGameObject(GameObjectType::TYPE_BULLET_PRIMARY, enemyObject->pos, 50, "laser_2");

	GameObject& bulletSpawned = Play::GetGameObject(iBullet);
	bulletSpawned.velocity = { vEnemyAim.GetX(),vEnemyAim.GetY(), };
	bulletSpawned.rotation = vEnemyAim.rad();
	Enemy::_spriteManager->addSprite(iBullet, "laser_2", 1);

	//pass to sprite manager to track drawing
	//_equippedGun;
	//_equippedGun->spawnBullet(Vec2(enemyObject->pos), vEnemyAim);
	
};

void Enemy::incrementSpawn()
{
	_spawnTime = _spawnTime + 1.0;
};