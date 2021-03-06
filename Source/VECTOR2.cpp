#include "VECTOR2.h"



VECTOR2::VECTOR2()
{
}


VECTOR2::~VECTOR2()
{
}

VECTOR2::VECTOR2(int x, int y)
{
	this->x = x;
	this->y = y;
}

//VECTOR2::VECTOR2(float dx, float dy)
//{
//	this->dx = dx;
//	this->dy = dy;
//}

VECTOR2 & VECTOR2::operator=(const VECTOR2 & vec)
{
	this->x = vec.x;
	this->y = vec.y;
	return (*this);
}

int & VECTOR2::operator[](int i)
{
	if (i == 0)
	{
		return x;
	}
	else if (i == 1)
	{
		return y;
	}
	else if (i == 2)
	{
		return x;
	}
}

bool VECTOR2::operator==(const VECTOR2 & vec) const
{
	return ((this->x == vec.x) && (this->y == vec.y));
}
bool operator==(const VECTOR2 & vec, int k)
{
	return ((k == vec.x) && (k == vec.y));
}

bool VECTOR2::operator!=(const VECTOR2 & vec) const
{
	return !((this->x == vec.x) && (this->y == vec.y));
}

VECTOR2 & VECTOR2::operator+=(const VECTOR2 & vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return (*this);
}

VECTOR2 & VECTOR2::operator-=(const VECTOR2 & vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return (*this);
}

VECTOR2 & VECTOR2::operator*=(const VECTOR2 & vec)
{
	this->x *= vec.x;
	this->y *= vec.y;

	return (*this);
}

VECTOR2 & VECTOR2::operator/=(const VECTOR2 & vec)
{
	this->x /= vec.x;
	this->y /= vec.y;

	return (*this);
}

VECTOR2 VECTOR2::operator+() const
{
	return (*this);
}

VECTOR2 VECTOR2::operator-() const
{
	return -(*this);
}

VECTOR2 operator+(const VECTOR2 & u, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = u.x + v.x;
	vec.y = u.y + v.y;

	return vec;
}

VECTOR2 operator+(const VECTOR2 & u, int k)
{
	VECTOR2 vec;
	vec.x = u.x + k;
	vec.y = u.y + k;
	return vec;
}

VECTOR2 operator+(int k, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = k + v.x;
	vec.y = k + v.y;
	return vec;
}

VECTOR2 operator-(const VECTOR2 & u, int k)
{
	VECTOR2 vec;
	vec.x = u.x - k;
	vec.y = u.y - k;
	return vec;
}

VECTOR2 operator-(const VECTOR2 & u, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = u.x - v.x;
	vec.y = u.y - v.y;

	return vec;
}

VECTOR2 operator%(const VECTOR2 & u, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = u.x % v.y;
	vec.y = u.y % v.y;

	return vec;
}

VECTOR2 operator%(const VECTOR2 & u, int k)
{
	VECTOR2 vec;
	vec.x = u.x % k;
	vec.y = u.y % k;
	return vec;
}

VECTOR2 operator*(int k, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = k * v.x;
	vec.y = k * v.y;

	return vec;
}



VECTOR2 operator*(const VECTOR2 & u, int k)
{
	VECTOR2 vec;
	vec.x = u.x * k;
	vec.y = u.y * k;

	return vec;
}

VECTOR2 operator/(const VECTOR2 & u, int k)
{
	VECTOR2 vec;
	vec.x = u.x / k;
	vec.y = u.y / k;

	return vec;
}

VECTOR2 operator/(const int k, VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = k / v.x;
	vec.y = k / v.y;

	return vec;
}

VECTOR2 & operator+=(const VECTOR2 & v, int k)
{
	VECTOR2 vec;
	vec.x += k;
	vec.y += k;

	return vec;
}

VECTOR2 operator<(const VECTOR2 & u, VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = u.x < v.x;
	vec.y = u.y < v.y;

	return vec;
}

VECTOR2 operator<(const VECTOR2 & u, const int k)
{
	VECTOR2 vec;
	vec.x = u.x < k;
	vec.y = u.y < k;

	return vec;
}

VECTOR2 operator>(const int k, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = k > vec.x;
	vec.y = k > vec.y;

	return vec;
}

