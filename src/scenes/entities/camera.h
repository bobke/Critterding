#ifndef CAMERA_H
#define CAMERA_H

#include "../../utils/settings.h"
#include "../../math/vector3f.h"
#include "GL/gl.h"
#include "../../utils/bullet/btBulletDynamicsCommon.h"

class Camera{
public:

	Camera();
	~Camera();

	// Position
// 	btVector3 position;
	btTransform position;

	// Controls
	Vector3f rotation;

	void place();
	void follow(btDefaultMotionState* myMotionState) const;

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
	void rollRight(const float& factor);
	void rollLeft(const float& factor);

	btVector3 getScreenDirection(const int& x, const int& y);
private:
	Settings *settings;
	const unsigned int* camerasensitivity;
};

#endif
