#include "vector3f.h"

Vector3f::Vector3f()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3f::Vector3f(const Vector3f &other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

Vector3f::Vector3f(const float xv, const float yv, const float zv)
{
	x = xv;
	y = yv;
	z = zv;
}

bool Vector3f::operator==(const Vector3f& other) const {

	if (x != other.x) return false;
	if (y != other.y) return false;
	if (z != other.z) return false;

	return true;
}

Vector3f::~Vector3f()
{
}
