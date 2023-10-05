#include "ChickenGun.h"

ChickenGun::ChickenGun(GameObjectType bulletType, std::string spriteName, SpriteManager* spriteManager) :
	Gun(bulletType, spriteName, spriteManager)
{
}


void ChickenGun::spawnBullet(Vec2 vOrigin, Vec2 vDir)
{
	//create bullet object
	int iBullet = Play::CreateGameObject(GetGameObjectType(), Point2D(vOrigin.GetX(), vOrigin.GetY()), 50, GetSpriteName().c_str());
	GameObject& bulletSpawned = Play::GetGameObject(iBullet);
	bulletSpawned.velocity = { vDir.GetX(),vDir.GetY(), };
	bulletSpawned.rotation = 0;
	//pass to sprite manager to track drawing
	Gun::GetSpriteManager()->addSprite(iBullet, GetSpriteName(), 1);

}

void ChickenGun::moveBullets()
{
	//collect all bullets belonging to this gun and all enemies
	std::vector<int> vEnemyIds = Play::CollectGameObjectIDsByType(TYPE_ENEMY);
	std::vector<int> childBullets = Play::CollectGameObjectIDsByType(GetGameObjectType());

	//change the angle of their velocity towards an enemy?
	//Play::SetGameObjectDirection();

	for (int iBullet : childBullets)
	{
		GameObject& bullet = Play::GetGameObject(iBullet);
		if (MaxsCollisionChecker({ bullet.pos.x, bullet.pos.y }, simpleCollisionMap)) {
			bullet.type = TYPE_DESTROYED;
			Play::UpdateGameObject(bullet);
			continue;
		}
		bullet.rotation = 0;
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
			else
			{
				Vec2 Evec = enemy.pos;
				Vec2 Distance = Evec - Vec2(bullet.pos);
				Vec2 BulletVel = { GetBulletSpeed()*Distance.GetX() / mag(Distance), GetBulletSpeed()*Distance.GetY() / mag(Distance) };
				if (mag(Distance)< 150)
				{
					bullet.velocity = { BulletVel.GetX(), BulletVel.GetY()};
				}
			}
		}
		if (bullet.velocity.x >= 0)
		{
			//sprite facing right
			bullet.spriteScale = { 1,1 };
		}
		else
		{
			bullet.spriteScale = { -1,1 };
			//sprite facing left
		}
	}

}


