#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Maths.h"

#pragma once

// Accepts 2 position vectors, and calculates the directional vector from vec1 to vec 2
// Arguments:
// Vec2 vec1: origin vector
// Vec2 vec2: target vector
Vec2 utilHandleCursorDirection(Vec2 vec1, Vec2 vec2) ;

//Pass a string to print out to the debug console
//Arguments:
//std::string: string to print out
//int x: x coord of debug message
//int y: y coord of debug message

void utilDebugString(std::string debugMessage, int x, int y);

void utilJanitor();

enum GameObjectType
{
	TYPE_PLAYER, //0
	TYPE_ENEMY, //1
	TYPE_BULLET_PRIMARY,  //2
	TYPE_GUN_PRIMARY,
	TYPE_DESTROYED,
	TYPE_UI,
};
