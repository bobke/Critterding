#ifndef CAMERA_H
#define CAMERA_H

#include "../../utils/settings.h"
#include "GL/gl.h"
#include "vector3f.h"
#include "btBulletDynamicsCommon.h"

class Camera{
public:

	Camera();
	~Camera();

	// Position
	Vector3f position;

	// Controls
	Vector3f rotation;

	void place();
	void follow(Vector3f &cameraposition, float &rotation);
	void follow(btDefaultMotionState* myMotionState) const;

	void lookRight(const float& factor);
	void lookLeft(const float& factor);
	void lookUp(const float& factor);
	void lookDown(const float& factor);
	void lookRollRight(const float& factor);
	void lookRollLeft(const float& factor);
	void moveForward(const float& factor);
	void moveBackward(const float& factor);
	void moveForwardXZ(const float& factor);
	void moveBackwardXZ(const float& factor);
	void moveForwardXYZ(const float& factor);
	void moveBackwardXYZ(const float& factor);
	void moveRight(const float& factor);
	void moveLeft(const float& factor);
	void moveUp(const float& factor);
	void moveDown(const float& factor);
	void moveRollLeft(const float& factor);
	void rollRight(const float& factor);
	void rollLeft(const float& factor);
private:
	Settings *settings;
	const unsigned int*	camerasensitivity;
};

#endif
