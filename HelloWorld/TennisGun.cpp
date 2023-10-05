#include "TennisGun.h"

TennisGun::TennisGun(GameObjectType bulletType, std::string spriteName, SpriteManager* spriteManager) :
	Gun(bulletType, spriteName, spriteManager)
{
}

void TennisGun::moveBullets()
{
	//collect all enemies
	std::vector<int> vEnemyIds = Play::CollectGameObjectIDsByType(TYPE_ENEMY);

	std::vector<int> childBullets = Play::CollectGameObjectIDsByType(GetGameObjectType());
	for (int iBullet : childBullets)
	{
		GameObject& bullet = Play::GetGameObject(iBullet);
		if (MaxsCollisionChecker({ bullet.pos.x, bullet.pos.y }, simpleCollisionMap)) {
			//reflect off wall
			//vanishes after a certain length of time?
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
