#include "Maths.h"

Vec2::Vec2()
{
	x = 0;
	y = 0;
}

Vec2::Vec2(float _x, float _y)
{
	x = _x;
	y = _y;
}

Vec2::Vec2(const Vec2& other)
{
	x = other.x;
	y = other.y;
}

Vec2 Vec2::operator+(const Vec2& other)
{
	return Vec2(this->x + other.x, this->y + other.y);
}

Vec2 Vec2::operator-(const Vec2& other)
{
	Vec2 result;
	result.x = this->x - other.x;
	result.y = this->y - other.y;
	return result;
}

Vec2 Vec2::operator*(const float other)
{
	return Vec2(this->x * other, this->y * other);
}

float Vec2::mag(Vec2 _Vector)
{
	float X = _Vector.GetX();
	float Y = _Vector.GetY();
	return (float)sqrt(X * X + Y * Y);
}

float Vec2::GetX()
{
	return x;
}

float Vec2::GetY()
{
	return y;
}

void Vec2::SetX(float _x)
{
	x = _x;
}

void Vec2::SetY(float _y)
{
	y = _y;
}
