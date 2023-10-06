#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include <string>
#include "Maths.h"
#include "Play.h"
#include "SpriteManager.h"
#include "Map.h"
#include "Utilities.h"

class Gun
{
public:

	Gun(enum GameObjectType bulletType, std::string spriteName, SpriteManager* spriteManager);
	//generate a bullet
	//add bullet to _bullets 
	void spawnBullet(Vec2 vOrigin, Vec2 vDir);

	//iterate over all children bullets
	//move them along their own own vector
	//run every tick
	void moveBullets(float _elapsedTime);

	enum GameObjectType GetGameObjectType();
	void SetGameObjectType(GameObjectType _newType);
	float GetBulletSpeed();
	void SetBulletSpeed(float speed);
	std::string GetSpriteName();
	void SetSpriteName(std::string NewName);
	SpriteManager* GetSpriteManager();
	float getCooldown();
	void setCooldown(float newCooldown);
	float getTimer();
	void setTimer(float newtime);
	bool getFiredGun();
	void setFiredGun(bool fired);

private:
	//ids of all spawned bullets child to this gun
	enum GameObjectType _bulletType;
	float _bulletSpeed;
	std::string _spriteName;
	SpriteManager* _spriteManager;
	float _gunCooldown = 0.4;
	float _timer = 0;
	bool firedGun = false;
};

