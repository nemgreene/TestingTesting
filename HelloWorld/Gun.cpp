#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Gun.h"
#include <string>
#include "Maths.h"
#include "Play.h"
#include "Utilities.h"


Gun::Gun(){};

Gun::Gun(enum GameObjectType bulletType, std::string spriteName, SpriteManager* spriteManager) {
	_bulletSpeed = 1.0f;
	_bulletType = bulletType;
	_spriteName = spriteName;
	_spriteManager = spriteManager;

}

void Gun::spawnBullet(Vec2 vOrigin, Vec2 vDir)
{
	//create bullet objec
	int iBullet = Play::CreateGameObject(TYPE_BULLET_PRIMARY, Point2D(vOrigin.GetX(), vOrigin.GetY()), 50, _spriteName.c_str());
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
		if (Play::IsLeavingDisplayArea(bullet)) {
				bullet.type = TYPE_DESTROYED;
				Play::UpdateGameObject(bullet);
				continue;
		}
		for (int id : vEnemyIds)
		{
			//get enemy game objecvt
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