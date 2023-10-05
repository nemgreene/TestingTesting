#pragma once
#include <cmath>
#include "Play.h"
class Vec2
{
public:
	//constructors, you can make an empty Vector, one from coordinates, or one from another vector
	Vec2();
	Vec2(float _x, float _y);
	Vec2(const Vec2& other);
	Vec2(const Point2D& other);

	Vec2 operator+(const Vec2& other);//adding vectors
	Vec2 operator-(const Vec2& other);//taking away
	Vec2 operator*(const float other);//multiplying

	friend std::ostream& operator<<(std::ostream& os, const Vec2& point);
	float rad(); //finds the rotation

	float GetX();
	float GetY();
	void SetX(float _x);
	void SetY(float _y);
private:
	float x;
	float y;
};

float mag(Vec2 _Vector); //finds the square root