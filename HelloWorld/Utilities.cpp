#include "Utilities.h"

#pragma once

// Accepts 2 position vectors, and calculates the directional vector from vec1 to vec 2
// Arguments:
// Vec2 vec1: origin vector
// Vec2 vec2: target vector
Vec2 utilHandleCursorDirection(Vec2 vec1, Vec2 vec2) {
	//returns degrees to rotate sprites and vector to send bullet along
	Vec2 vecDir = vec2 - vec1;
	float vecDirMag = vecDir.mag(vecDir);
	Vec2 vUnitVec{ vecDir.GetX() / vecDirMag, vecDir.GetY() / vecDirMag };
	return vUnitVec;
};

//Pass a string to print out to the debug console
//Arguments:
//std::string: string to print out
//int x: x coord of debug message
//int y: y coord of debug message

void utilDebugString(std::string debugMessage, int x, int y) {
	const char* PS = debugMessage.c_str();
	Play::DrawDebugText({ x,y }, PS);
};


void utilJanitor() {

	Play::DestroyGameObjectsByType(TYPE_DESTROYED);

}

