#pragma once
#include "SpriteManager.h"


void utilDebugString(std::string debugMessage, int x, int y);


SpriteManager::SpriteManager() {};




void SpriteManager::_checkPlayerSprite(Vec2 vMousePos, float fAimVec)
{
	//check user orientation
	GameObject& player = Play::GetGameObjectByType(0);
	std::string rot = std::to_string(fAimVec);


	//down
	if (2.094 > fAimVec && fAimVec > 1.047)
	{
		player.spriteScale = { 1, 1 };
		changeSprites(player.GetId(), "fry_ruinning_down_6");
	}

	//down right
	else if (1.047 > fAimVec && fAimVec > 0)
	{

		player.spriteScale = { 1, 1 };
		changeSprites(player.GetId(), "fry_ruinning_dr_6");
	}
	//down left
	else if (PLAY_PI > fAimVec && fAimVec > 2.094)
	{
		player.spriteScale = { -1, 1 };
		changeSprites(player.GetId(), "fry_ruinning_dr_6");
	}
	//up right
	else if (0 > fAimVec && fAimVec > -1.047)
	{
		player.spriteScale = { 1, 1 };
		changeSprites(player.GetId(), "fry_ruinning_ur_6");

	}
	//up left
	else if (-2.094 > fAimVec && fAimVec > (PLAY_PI * -1))
	{
		player.spriteScale = { -1, 1 };
		changeSprites(player.GetId(), "fry_ruinning_ur_6");
	}
	//up
	else if (-1.047 > fAimVec && fAimVec > -2.094)
	{
		player.spriteScale = { 1, 1 };
		changeSprites(player.GetId(), "fry_ruinning_up_6");
	}
};;


Vec2 SpriteManager::_findSpriteCoords(int id) {
	for (unsigned int y = 0; y < SpriteManager::_spriteCache.size(); y++)
	{
		if (SpriteManager::_spriteCache[y].find(id) != _spriteCache[y].end())
		{
			Vec2 ret = Vec2(_spriteCache[y].find(id)->first, y);
			return ret;

		}
	}
	return(Vec2(-1, -1));
};


//load all sprites into cache, build layers, iterate over them, draw them in order 
void SpriteManager::initializeSprites(std::vector<std::map<int, std::string>> vInitializeSpriteMap)
{
	SpriteManager::_spriteCache = vInitializeSpriteMap;
};


//Change a game objects animation by id
void SpriteManager::changeSprites(int id, std::string spriteName)
{
	Vec2 coords = SpriteManager::_findSpriteCoords(id);
	if (coords.GetX() != -1)
	{
		SpriteManager::_spriteCache[coords.GetY()][coords.GetX()] = spriteName;
	}
};
//add sprite to cache
// 
void SpriteManager::addSprite(int id, std::string spriteName, int layerIndex)
{
	SpriteManager::_spriteCache[layerIndex].insert(std::pair<int, std::string>(id, spriteName));
	_spriteCache;
};
// 
//chain animations together, with callback

//Move a sprite id to a dWifferent render layer
void SpriteManager::updateSpriteOrder(std::vector < std::vector<int>> sprites) {

	for (std::vector<int> spriteIdentifier : sprites)
	{
		//find coords in map where sprite id is
		Vec2 targ = SpriteManager::_findSpriteCoords(spriteIdentifier[0]);
		//get sprite name
		std::string targetSprite = SpriteManager::_spriteCache[targ.GetY()][targ.GetX()];
		//remove sprite from layer
		SpriteManager::_spriteCache[targ.GetY()].erase(targ.GetX());
		//add to new layer
		SpriteManager::_spriteCache[spriteIdentifier[1]].insert(std::pair<int, std::string>(spriteIdentifier[0], targetSprite));
	}

}

void SpriteManager::deleteSprites(int id)
{
	Vec2 targ = SpriteManager::_findSpriteCoords(id);
	if (targ.GetX() != -1)
	{
		SpriteManager::_spriteCache[targ.GetY()].erase(id);
	}
}

//Run every tick to animate all the sprites IN _SPRITECACHE
void SpriteManager::tickSprites(Vec2 vMousePos, float fAimVec, float deltaTime)
{
	SpriteManager::_deltaTime = deltaTime;
	SpriteManager::_checkPlayerSprite(vMousePos, fAimVec);
	//SpriteManager::chainAnimation(0, "fry_rolling_down_9", 9, [] {return;});

	for (std::map<int, std::string> layer : SpriteManager::_spriteCache)
	{
		for (auto const& x : layer)
		{
			//if sprite is chained, continue its animation
			//if (std::find(SpriteManager::_chainedIds.begin(), SpriteManager::_chainedIds.end(), x.first) != SpriteManager::_chainedIds.end())
			//{
			//	SpriteManager::_continueChain(x.first);
			//	continue;
			//}
			//else update normally
			GameObject& obj = Play::GetGameObject(x.first);
			std::string newSprite = x.second;

			//c_str
			const char* spriteName = newSprite.c_str();

			Play::SetSprite(obj, spriteName, 0.2f);
			Play::UpdateGameObject(obj);
			//Drawing types have differenet computational demand
			//highest demand
			if (obj.spriteScale.x != 0 || obj.spriteScale.y != 0)
			{
				Play::DrawObjectRotatedScaled(obj, { obj.spriteScale.x, obj.spriteScale.y });
			}
			else if (obj.rotation != 0)
			{
				Play::DrawObjectRotated(obj);
			}
			else {
				Play::DrawObject(obj);
			}
		}
	}

	//check player sprites
	//check enemy sprites
	//
};

void SpriteManager::chainAnimation(int id, std::string newSprite, int duration, void (*callback)() = [] {return;})
{
	Vec2 targCoords = SpriteManager::_findSpriteCoords(id);
	if (targCoords.GetX() == -1)
	{
		callback();
		return;
	}
	SpriteManager::changeSprites(id, newSprite);
	_ChainedObj insert = { id, duration, newSprite };

	SpriteManager::_chainedCache.push_back(insert);
	SpriteManager::_chainedIds.push_back(id);
	callback();


}

void SpriteManager::_continueChain(int id)
{
	Vec2 targCoords = _findSpriteCoords(id);
	std::string currentSprite = SpriteManager::_spriteCache[targCoords.GetY()][targCoords.GetX()];


	//clever logic to run the sprite to the end of the chain, then reset it after
	// draw the sprite
	// tic down duration
	// if duration == 0
	// remove from caches
	// return to render loop
	// 
	//SpriteManager::_chainedCache[id].duration--;


	//GameObject& obj = Play::GetGameObject(id);

	//const char* spriteName = currentSprite.c_str();
	//Play::SetSprite(obj, spriteName, 0.2f);
	//Play::UpdateGameObject(obj);
	////Drawing types have differenet computational demand
	////highest demand
	//if (obj.spriteScale.x != 0 || obj.spriteScale.y != 0)
	//{
	//	Play::DrawObjectRotatedScaled(obj, { obj.spriteScale.x, obj.spriteScale.y });
	//}
	//else if (obj.rotation != 0)
	//{
	//	Play::DrawObjectRotated(obj);
	//}
	//else {
	//	Play::DrawObject(obj);
	//};
	//if(SpriteManager::_chainedCache[id].duration = < 0)
	//{
	//	return
	//}

};