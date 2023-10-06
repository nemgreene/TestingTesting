#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Gun.h"
#include <string>




Gun::Gun(enum GameObjectType bulletType, std::string spriteName, SpriteManager* spriteManager) {
	_bulletSpeed = 5.0f;
	_bulletType = bulletType;
	_spriteName = spriteName;
	_spriteManager = spriteManager;
}

void Gun::spawnBullet(Vec2 vOrigin, Vec2 vDir)
{
	//create bullet object
	if (getFiredGun() == false)
	{
		GameObject& secondaryGun = Play::GetGameObjectByType(TYPE_GUN_SECONDARY);
		int secodnaryId = Play::GetSpriteId("shotgun");
		float width = Play::GetSpriteWidth(secodnaryId);

		Vec2 bulletSpawnLocation = vOrigin + (vDir * width);


		int iBullet = Play::CreateGameObject(GetGameObjectType(), Point2D(bulletSpawnLocation.GetX(), bulletSpawnLocation.GetY()), 50, _spriteName.c_str());
		GameObject& bulletSpawned = Play::GetGameObject(iBullet);

		bulletSpawned.velocity = { vDir.GetX() * 5,vDir.GetY() * 5, };
		bulletSpawned.rotation = vDir.rad();

		//pass to sprite manager to track drawing
		Gun::_spriteManager->addSprite(iBullet, _spriteName, 1);
		setFiredGun(true);
	}

}
	
void Gun::moveBullets(float _elapsedTime)
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
				//if robit dies
				if (vEnemyIds.size() == 2)
				{
					Play::PlayAudio("robit_shout_01");
				}
				else
				{
					Play::PlayAudio("robit_break_01");

				}
				enemy.type = TYPE_DESTROYED;
				bullet.type = TYPE_DESTROYED;
				Play::UpdateGameObject(bullet);
				Play::UpdateGameObject(enemy);
			}
		}
	}

	if (getFiredGun())
	{
		setTimer(getTimer() + _elapsedTime);
		if (getTimer()>getCooldown())
		{
			setTimer(0);
			setFiredGun(false);
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

float Gun::getCooldown()
{
	return _gunCooldown;
}

void Gun::setCooldown(float newCooldown)
{
	_gunCooldown = newCooldown;
}

float Gun::getTimer()
{
	return _timer;
}

void Gun::setTimer(float newtime)
{
	_timer = newtime;
}

bool Gun::getFiredGun()
{
	return firedGun;
}

void Gun::setFiredGun(bool fired)
{
	firedGun = fired;
}
