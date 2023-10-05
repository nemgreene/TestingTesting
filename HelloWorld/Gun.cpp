#define PLAY_USING_GAMEOBJECT_MANAGER
#pragma once
#include "Play.h"
#include "Gun.h"
#include <string>
#include "Maths.h"
#include "Utilities.h"


Gun::Gun()
{
	
};

Gun::Gun(GameObjectType bulletType, std::string spriteName, SpriteManager* spriteManager)
{
	Gun::_bulletSpeed = 1.0f;
	Gun::_bulletType = bulletType;
	Gun::_spriteName = spriteName;
	Gun::_spriteManager = spriteManager;

	int iBullet = Play::CreateGameObject(GameObjectType::TYPE_GUN_PRIMARY, Point2D(0, 0), 50, Gun::_spriteName.c_str());
	Gun::_spriteManager->addSprite(iBullet, Gun::_spriteName, 3);


}

void Gun::spawnBullet(Vec2 vOrigin, Vec2 vDir)
{
	//create bullet objec
	int iBullet = Play::CreateGameObject(GameObjectType::TYPE_BULLET_PRIMARY, Point2D(vOrigin.GetX(), vOrigin.GetY()), 50, Gun::_spriteName.c_str());
	GameObject& bulletSpawned = Play::GetGameObject(iBullet);
	bulletSpawned.velocity = { vDir.GetX(),vDir.GetY(), };
	bulletSpawned.rotation = vDir.rad();

	//pass to sprite manager to track drawing
	Gun::_spriteManager->addSprite(iBullet, Gun::_spriteName, 1);

}
	
void Gun::moveBullets(std::vector<Enemy*>* enemies)
{
	//collect all enemies

	std::vector<int> childBullets = Play::CollectGameObjectIDsByType(Gun::_bulletType);
	if (childBullets.size() <= 0) {
		return;
	};
	for (int iBullet : childBullets)
	{
		
		GameObject& bullet= Play::GetGameObject(iBullet);
		if (Play::IsLeavingDisplayArea(bullet)) {
			bullet.type = GameObjectType::TYPE_DESTROYED;
			Play::UpdateGameObject(bullet);
			continue;
		};

		int size = enemies->size();

		//for (int x = 0; x < enemies->size(); ++x)
		//{
		//	Enemy* enemyObj = (*enemies)[x];

		//	std::cout << "test";

		//}
		//for (Enemy* internalEnemy : enemies)
		//{
		//	std::cout << "test";
		//	get enemy game objecvt
		//	internalEnemy;
		//	Enemy enemyObj = &internalEnemy;
		//	GameObject& enemy = Play::GetGameObject(&internalEnemy);
		//	if (Play::IsColliding(bullet, enemy))
		//	{
		//		enemy.type = GameObjectType::TYPE_DESTROYED;
		//		bullet.type = GameObjectType::TYPE_DESTROYED;
		//		Play::UpdateGameObject(bullet);
		//		Play::UpdateGameObject(enemy);
		//	}
		//}
	}
}