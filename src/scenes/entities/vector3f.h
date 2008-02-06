#ifndef VECTOR3F_H
#define VECTOR3F_H

class Vector3f {

	public:
		Vector3f();
		~Vector3f();
	
		// other constructors
		Vector3f(const Vector3f &other);
		Vector3f(const float xv, const float yv, const float zv);
	
		bool operator==(const Vector3f &other) const;
	
		float	x;
		float	y;
		float	z;

};

#endif
