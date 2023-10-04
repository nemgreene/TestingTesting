#include "Map.h"

bool MaxsCollisionChecker(Vec2 Pos, std::vector<std::vector<bool>> _collisionMap)
{
	int XCoord = int(Pos.GetX() / 33); //	takes the x and y coords of the object and converts them to coordinates
	int YCoord = int(Pos.GetY() / 33); //	for the array by dividing them by the size of the tile
	if (YCoord > 0 || YCoord < 19 || XCoord > 0 || XCoord < 29) // checks the coordinates to not go out the bounds of the vector
	{
	bool isColliding = _collisionMap[YCoord][XCoord];
		return isColliding;
	}
	return true;
}
