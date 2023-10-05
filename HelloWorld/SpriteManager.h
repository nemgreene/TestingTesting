#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include <string>
#include "Maths.h"
#include "Play.h"
#include "Utilities.h"


struct _ChainedObj;


class SpriteManager
{
private:
	//Nucleus of the sprite manager function
	//layer system should be:
	//[Background]  0
	//[Bullets] 1
	//[Enemies] <--------------------| will swap
	//[Enemies guns/utilities]<------|
	//[Char] <--]
	//[Gun] <---] will swap
	//[ForeGround]


	std::vector<std::map<int, std::string>> _spriteCache;
	//std::vector<_ChainedObj> _chainedCache;
	std::vector<int> _chainedIds;
	std::map<int, std::string> _rotationCache;
	void _checkPlayerSprite(Vec2 vMousePos, float fAimVec);
	Vec2 _findSpriteCoords(int id);
	void _continueChain(int id);

public:
	SpriteManager();
	float _deltaTime;
	//load all sprites into cache, build layers, iterate over them, draw them in order 
	void initializeSprites(std::vector<std::map<int, std::string>> vInitializeSpriteMap);
	//add sprite to cache
	// 
	void addSprite(int id, std::string spriteName, int layerIndex);
	// CHange sprite
	void changeSprites(int id, std::string spriteName);
	//Move a sprite id to a different render layer
	void updateSpriteOrder(std::vector < std::vector<int>> sprites);
	//delete sprite from cache
	void deleteSprites(int id);

	//chain animations, 
	//void chainAnimation(int id, std::string newSprite, int duration, void (*callback)());
	//Run every tick to animate all the sprites IN _SPRITECACHE
	void tickSprites(Vec2 vMousePos, float fAimVec, float deltaTime);
};
