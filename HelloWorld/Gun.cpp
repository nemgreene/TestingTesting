#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Gun.h"
#include <string>




Gun::Gun(enum GameObjectType bulletType, std::string spriteName, SpriteManager* spriteManager) {
	_bulletSpeed = 1.0f;
	_bulletType = bulletType;
	_spriteName = spriteName;
	_spriteManager = spriteManager;

}

void Gun::spawnBullet(Vec2 vOrigin, Vec2 vDir)
{
	//create bullet object
	int iBullet = Play::CreateGameObject(GetGameObjectType(), Point2D(vOrigin.GetX(), vOrigin.GetY()), 50, _spriteName.c_str());
	GameObject& bulletSpawned = Play::GetGameObject(iBullet);
	bulletSpawned.velocity = { vDir.GetX(),vDir.GetY(), };
	bulletSpawned.rotation = vDir.rad();

	//pass to sprite manager to track drawing
	Gun::_spriteManager->addSprite(iBullet, _spriteName, 1);

}
	
void Gun::moveBullets()
{
	//collect all enemies
	std::vector<int> vEnemyIds = Play::CollectGameObjectIDsByType(TYPE_ENEMY);

	std::vector<int> childBullets = Play::CollectGameObjectIDsByType(_bulletType);
	for (int iBullet : childBullets)
	{
		
		GameObject& bullet= Play::GetGameObject(iBullet);
		if (MaxsCollisionChecker(Vec2(bullet.pos), simpleCollisionMap)) {
				bullet.type = TYPE_DESTROYED;
				Play::UpdateGameObject(bullet);
				continue;
		}
		for (int id : vEnemyIds)
		{
			//get enemy game object
			GameObject& enemy = Play::GetGameObject(id);
			if (Play::IsColliding(bullet, enemy))
			{
				enemy.type = TYPE_DESTROYED;
				bullet.type = TYPE_DESTROYED;
				Play::UpdateGameObject(bullet);
				Play::UpdateGameObject(enemy);
			}
		}
	}
}

GameObjectType Gun::GetGameObjectType()
{
	return _bulletType;
}

void Gun::SetGameObjectType(GameObjectType _newType)
{
	_bulletType = _newType;
}

float Gun::GetBulletSpeed()
{
	return _bulletSpeed;
}

void Gun::SetBulletSpeed(float speed)
{
	_bulletSpeed = speed;
}

std::string Gun::GetSpriteName()
{
	return _spriteName;
}

void Gun::SetSpriteName(std::string NewName)
{
	_spriteName = NewName;
}

SpriteManager* Gun::GetSpriteManager()
{
	return _spriteManager;
}
