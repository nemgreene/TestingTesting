#pragma once
#include "Gun.h"

class TennisGun : public Gun
{
public:
	TennisGun(enum GameObjectType bulletType, std::string spriteName, SpriteManager* spriteManager);
	//overwriting moveBullets
	void moveBullets();

private:

};

