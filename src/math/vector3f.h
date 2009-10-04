#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <cmath>

class Vector3f {

	public:
		Vector3f();
		~Vector3f();
	
		// other constructors
		Vector3f(const Vector3f &other);
		Vector3f(const float xv, const float yv, const float zv);
	
		bool operator==(const Vector3f &other) const;
		Vector3f operator-(const Vector3f &other) const;
		Vector3f & operator/=(const float scalar);
		Vector3f & operator/=(const Vector3f &other);

		float length() const;
		float lengthsquared() const;
		void normalize();
		float dot(const Vector3f& vector);
// 		void crossproduct(const Vector3f& v1, const Vector3f& v2);

		float	x;
		float	y;
		float	z;

};

#endif
