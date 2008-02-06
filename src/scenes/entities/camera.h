
#ifndef ___CAMERA__
#define ___CAMERA__


#endif // ___CAMERA__
#ifndef CAMERA_H
#define CAMERA_H
#include "GL/gl.h"
#include "vector3f.h"

class Camera{
public:

	Camera();
	~Camera();

	// Position
	Vector3f position;

	// Controls
	Vector3f rotation;

	void place(unsigned int *width, unsigned int *height);

	void lookRight(const float& factor);
	void lookLeft(const float& factor);
	void lookUp(const float& factor);
	void lookDown(const float& factor);
	void lookRollRight(const float& factor);
	void lookRollLeft(const float& factor);
	void moveForward(const float& factor);
	void moveBackward(const float& factor);
	void moveRight(const float& factor);
	void moveLeft(const float& factor);
	void moveUp(const float& factor);
	void moveDown(const float& factor);
	void moveRollLeft(const float& factor);

};

#endif
