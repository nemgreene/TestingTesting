#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include <string>
#include "Maths.h"
#include "Play.h"


void utilDebugString(std::string debugMessage, int x, int y);

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


	std::map<int, std::string> _rotationCache;


	void _checkPlayerSprite(Vec2 vMousePos, float fAimVec)
	{
		//check user orientation
		GameObject& player = Play::GetGameObjectByType(0);
		std::string rot = std::to_string(fAimVec);


		//down
		if (2.094 > fAimVec && fAimVec > 1.047)
		{
			player.spriteScale= { 1, 1 };
			changeSprites(player.GetId(), "fry_ruinning_down_6");
		} 

		//down right
		else if (1.047 > fAimVec && fAimVec > 0) 
		{

			player.spriteScale= { 1, 1 };
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
			player.spriteScale= { 1, 1 };
			changeSprites(player.GetId(), "fry_ruinning_ur_6");

		}
		//up left
		else if (-2.094 > fAimVec && fAimVec > (PLAY_PI * -1))
		{
			player.spriteScale = { -1, 1 };
			changeSprites(player.GetId(), "fry_ruinning_ur_6");
		}
		//up
		else if (-1.047 > fAimVec && fAimVec > -2.094 )
		{
			player.spriteScale= { 1, 1 };
			changeSprites(player.GetId(), "fry_ruinning_up_6");
		}
	};


	Vec2 _findSpriteCoords(int id) {
		for (unsigned int y = 0; y < _spriteCache.size(); y++)
		{
			if (_spriteCache[y].find(id) != _spriteCache[y].end())
			{
				Vec2 ret = Vec2(_spriteCache[y].find(id)->first, y);
				return ret;

			}
		}
		return(Vec2(-1, -1));
	}

public:
	//load all sprites into cache, build layers, iterate over them, draw them in order 
	void initializeSprites(std::vector<std::map<int, std::string>> vInitializeSpriteMap)
	{
		_spriteCache = vInitializeSpriteMap;
	}

	//Change a game objects animation by id
	void changeSprites(int id, std::string spriteName )
	{
		Vec2 coords = _findSpriteCoords(id);
		if (coords.GetX() != -1)
		{
			_spriteCache[coords.GetY()][coords.GetX()] = spriteName;
		}
	}
	//add sprite to cache
	// 
	void addSprite(int id, std::string spriteName, int layerIndex )
	{
		_spriteCache[layerIndex][id] = spriteName;
	};
	// 
	//chain animations together, with callback

	//Move a sprite id to a different render layer
	void updateSpriteOrder(std::vector < std::vector<int>> sprites) {

		for (std::vector<int> spriteIdentifier : sprites)
		{
			//find coords in map where sprite id is
			Vec2 targ = _findSpriteCoords(spriteIdentifier[0]);
			//get sprite name
			std::string targetSprite = _spriteCache[targ.GetY()][targ.GetX()];
			//remove sprite from layer
			_spriteCache[targ.GetY()].erase(targ.GetX());
			//add to new layer
			_spriteCache[spriteIdentifier[1]].insert(std::pair<int, std::string>(spriteIdentifier[0], targetSprite));
		}

	}


	//Run every tick to animate all the sprites IN _SPRITECACHE
	void tickSprites(Vec2 vMousePos, float fAimVec)
	{
		//_checkPlayerSprite(vMousePos, fAimVec);

		for (std::map<int, std::string> layer : _spriteCache)
		{
			for (auto const& x : layer)
			{
				GameObject& obj = Play::GetGameObject(x.first);
				const char* spriteName = x.second.c_str();
				Play::SetSprite(obj,spriteName, 0.2f);
				Play::UpdateGameObject(obj);
				//Drawing types have differenet computational demand
				//highest demand
				if (obj.spriteScale.x != 0 || obj.spriteScale.y != 0 )
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
	}
;
};

