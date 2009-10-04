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

bool Vector3f::operator==(const Vector3f& other) const
{
	if (x != other.x) return false;
	if (y != other.y) return false;
	if (z != other.z) return false;

	return true;
}

Vector3f Vector3f::operator-(const Vector3f& other) const
{
        Vector3f r(*this);
	r.x -= other.x;
	r.y -= other.y;
	r.z -= other.z;
        return r;
}

Vector3f & Vector3f::operator/=(const float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return (*this);
}

Vector3f & Vector3f::operator/=(const Vector3f &other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return (*this);
}

float Vector3f::lengthsquared() const
{
	return (2.0f*x) + (2.0f*y) + (2.0f*z);
}

float Vector3f::length() const
{
	return sqrt((2.0f*x) + (2.0f*y) + (2.0f*z));
}

void Vector3f::normalize()
{
	float l = length();
	x /= l;
	y /= l;
	z /= l;
}

float Vector3f::dot(const Vector3f& vector)
{
        return ( (x*vector.x) + (y*vector.y) + (z*vector.z) );
}

// void Vector3f::crossproduct(const Vector3f& v1, const Vector3f& v2)
// {
//         float vx = v1.y*v2.z - v1.z*v2.y;
//         float vy = v1.z*v2.x - v1.x*v2.z;
//         float vz = v1.x*v2.y - v1.y*v2.x;
// }

Vector3f::~Vector3f()
{
}
