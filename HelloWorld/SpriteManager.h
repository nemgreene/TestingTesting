#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include <string>
#include "Maths.h"
#include "Play.h"


//Abstraction to handle drawing all sprites
//will likely need to handle a hierarchy/order/z-index to draw foregroud/background

//Inintialize sprite library
//define layers:
//inintialize sprites
//check sprites: verify that player/enemy sprites are drawn in the corrrect order
//update sprites: manually change the layer a sprite is drawn on 

	//Sprites have to be draw in a dynamic order
	//when a character is facind down, gun is draw on top
	//when a char is facing up, gun is drawn below
	//some bg elements need to be drawn on top of the characters, as they should be able to walk behind them
	//we need to be able to restrucutre the hierarchy of sprites dynamically frame by frame
	//how do we build this?

	//Could have a predefined number of layers ie : [bg, utility, gun, character, utility, foreground]
	//that is constructed at the start of the game
	//then can be updated by calling UpdateSprites()

	//ie on game start   [bg, utility, gun, character, utility, foreground]
	//during runtime upateSprites(charcater: -1, gun :1)
	//output             [bg, utility, character, gun, utility, foreground]
	// 
	// 
	//adidtionally we could have a global offest that all positions reference in here that is incremented as the character moves to mimic camera follow

void utilDebugString(std::string debugMessage, int x, int y);

class SpriteManager
{
private:
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
public:
	//load all sprites into cache, build layers, iterate over them, draw them in order 
	void initializeSprites(std::vector<std::map<int, std::string>> vInitializeSpriteMap)
	{
		_spriteCache = vInitializeSpriteMap;
	}

	//Change a game objects animation by id
	void changeSprites(int id, std::string spriteName )
	{
		for (unsigned int y = 0; y < _spriteCache.size(); y++)
		{
			if(_spriteCache[y].find(id) != _spriteCache[y].end());
			{
				_spriteCache[y][id] = spriteName;
			}
		}

	};


	//Run every tick to animate all the sprites
	void tickSprites(Vec2 vMousePos, float fAimVec)
	{
		_checkPlayerSprite(vMousePos, fAimVec);

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

