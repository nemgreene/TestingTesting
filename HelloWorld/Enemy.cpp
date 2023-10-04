#include "Enemy.h"


Enemy::Enemy() {};

Enemy::Enemy(Gun equippedGun, SpriteManager* spriteManager, int health, Vec2 position, std::string spriteName) {
	const char* PS = spriteName.c_str();
	_iEnemyId = Play::CreateGameObject(TYPE_ENEMY, {position.GetX(), position.GetY()}, 50, PS );
	
	spriteManager->addSprite(_iEnemyId, spriteName, 2);
	//_gameObject = enemyObject;
	_health = health;
	_spawnTime = spriteManager->_deltaTime;
	_frequency = 1;
	GameObject& enemyObj = Play::GetGameObject(_iEnemyId);


}
//handles movement and firing
void Enemy::moveRandomly()
{

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
	target.type = TYPE_DESTROYED;
}

//just generates the actual bullets from origin
void Enemy::fireGun()
{
	GameObject& player = Play::GetGameObjectByType(TYPE_PLAYER);
	Vec2 vEnemyAim = utilHandleCursorDirection(Vec2(enemyObject->pos), Vec2(player.pos));
	_equippedGun.spawnBullet(Vec2(enemyObject->pos), vEnemyAim);
}
;