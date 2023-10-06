#include "EnemyController.h"
#include <random>


EnemyController::EnemyController() {};

EnemyController::EnemyController(SpriteManager* spriteManager, GameState* gameState) {
	_spriteManager = spriteManager;
	_gameState = gameState;
};


void EnemyController::spawnEnemy(GameObjectType type, Point2f origin, int radius, std::string spriteName) {

	int iEnemy = Play::CreateGameObject(type, origin, radius, "robit");
	_spriteManager->addSprite(iEnemy, "robit_running_down_6", 2);
	_enemyIds.insert((std::pair<int, float>(iEnemy, 0)));

};

void EnemyController::fireGun(int id) {
	std::cout << "test";
	
	//std::vector<int> player = Play::CollectGameObjectIDsByType(TYPE_PLAYER);
	//int playerId = player[0];
	GameObject& player = Play::GetGameObject(playerId);
	GameObject& enemy = Play::GetGameObject(id);

	Vec2 vBullet = utilHandleCursorDirection(Vec2(enemy.pos), Vec2(player.pos));

	int iBullet = Play::CreateGameObject(TYPE_BULLET_ENEMY, enemy.pos, 11, "acid");
	GameObject& bulletSpawned = Play::GetGameObject(iBullet);

	bulletSpawned.velocity = { vBullet.GetX() * 2,vBullet.GetY() * 2, };
	//bulletSpawned.rotation = vBullet.rad();

	Play::SetSprite(bulletSpawned, "acid_bullets_4", 0.2f);
	Play::UpdateGameObject(bulletSpawned);

	////pass to sprite manager to track drawing
	_spriteManager->addSprite(iBullet,"acid_bullets_4", 1);
	return;
}

void EnemyController::moveEnemies() {
	for (auto const& enemyMap : _enemyIds)
	{
		GameObject& obj = Play::GetGameObject(enemyMap.first);
		if (obj.type == -1 || (obj.pos.x == 0 && obj.pos.y == 0))
		{
			_enemyIds.erase(enemyMap.first);
			return;
		}
		_enemyIds[enemyMap.first] = _enemyIds[enemyMap.first] + 1 ;

		if (obj.type && _enemyIds[enemyMap.first] > 40) {
			fireGun(enemyMap.first);
			_enemyIds[enemyMap.first] = 0;
		};

		//fire randomly

		///then move randomly
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 gen(rd()); // seed the generator
		std::uniform_int_distribution<> distr(-1, 1); // define the range
		obj.velocity.x += distr(gen) * .25;
		obj.velocity.y += distr(gen) * .25;
		obj.velocity.x = (obj.velocity.x < -1) ? -1 : (obj.velocity.x > 1) ? 1 : obj.velocity.x;
		obj.velocity.y = (obj.velocity.y < -1) ? -1 : (obj.velocity.y > 1) ? 1 : obj.velocity.y;
		//Play::UpdateGameObject(obj);

		//
		bool collided = MaxsCollisionChecker({ obj.pos.x , obj.pos.y }, simpleCollisionMap);
		if (collided) {
			obj.pos = obj.oldPos;
			obj.velocity.x = obj.velocity.x * -1;
			obj.velocity.y = obj.velocity.y * -1;
		}

		Play::UpdateGameObject(obj);
	}

};

void EnemyController::checkPlayerCollisions()
{ 
	std::vector<int> bullets = Play::CollectGameObjectIDsByType(TYPE_BULLET_ENEMY);
	GameObject& player = Play::GetGameObject(playerId);

	for (int iBullet : bullets)
	{
		GameObject& bullet = Play::GetGameObject(iBullet);
		bool colliding = Play::IsColliding(player, bullet);
		if (colliding)
		{
			bullet.type = TYPE_DESTROYED;
			_gameState->PlayerCurrentHealth = _gameState->PlayerCurrentHealth - 10;
		}
	}
}