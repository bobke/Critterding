
#include "camera.h"
#include <cmath>

using namespace std;

Camera::Camera()
{
	settings = Settings::Instance();
	camerasensitivity = settings->getCVarPtr("camerasensitivity");

	position	= btVector3( 0.0f, 0.0f, 0.0f);
	rotation	= Vector3f( 75.0f,  0.0f, 0.0f);
}

void Camera::place()
{
	glViewport(0,0,*Settings::Instance()->winWidth,*Settings::Instance()->winHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float nheight = 0.5f * ((float)(*Settings::Instance()->winHeight) / *Settings::Instance()->winWidth);
	glFrustum(-0.5f,0.5f,-nheight,nheight,1.0f,10000.0f);

	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
	glTranslatef(position.getX(), position.getY(), position.getZ());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Camera::follow(btDefaultMotionState* myMotionState) const
{
	glViewport(
		*Settings::Instance()->winWidth - *Settings::Instance()->winWidth/8,
		0,
		*Settings::Instance()->winWidth/8,
		*Settings::Instance()->winHeight/8
	);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	float nheight = 0.05f * ((float)(*Settings::Instance()->winHeight) / *Settings::Instance()->winWidth);
	glFrustum( -0.05f, 0.05f,-nheight,nheight, 0.1f, 10000.0f);

	btScalar position[16];
	btTransform tr = myMotionState->m_graphicsWorldTrans.inverse();
	tr.getOpenGLMatrix(position);
	glMultMatrixf(position);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Moving

void Camera::moveForwardXZ(const float& factor)
{
	float reusedY = (360.0f-rotation.y) * 0.0174532925f;

	position.setX( position.getX() + sin(reusedY) * factor * *camerasensitivity );
	position.setZ( position.getZ() + cos(reusedY) * factor * *camerasensitivity );
}

void Camera::moveBackwardXZ(const float& factor)
{
	float reusedY = (360.0f-rotation.y) * 0.0174532925f;

	position.setX( position.getX() - sin(reusedY) * factor * *camerasensitivity );
	position.setZ( position.getZ() - cos(reusedY) * factor * *camerasensitivity );
}

void Camera::moveForwardXYZ(const float& factor)
{
	float reusedX = (360.0f-rotation.x) * 0.0174532925f;
	float reusedY = (360.0f-rotation.y) * 0.0174532925f;

	position.setX( position.getX() + sin(reusedY) * cos(reusedX) * factor * *camerasensitivity );
	position.setY( position.getY() - sin(reusedX) * factor * *camerasensitivity );
	position.setZ( position.getZ() + cos(reusedY) * cos(reusedX) * factor * *camerasensitivity );
}

void Camera::moveBackwardXYZ(const float& factor)
{
	float reusedX = (360.0f-rotation.x) * 0.0174532925f;
	float reusedY = (360.0f-rotation.y) * 0.0174532925f;

	position.setX( position.getX() - sin(reusedY) * cos(reusedX) * factor * *camerasensitivity );
	position.setY( position.getY() + sin(reusedX) * factor * *camerasensitivity );
	position.setZ( position.getZ() - cos(reusedY) * cos(reusedX) * factor * *camerasensitivity );
}

void Camera::moveRight(const float& factor)
{
	float reused = (90.0f-rotation.y) * 0.0174532925f;
	position.setX( position.getX() - sin(reused) * factor * *camerasensitivity );
	position.setZ( position.getZ() - cos(reused) * factor * *camerasensitivity );
}

void Camera::moveLeft(const float& factor)
{
	float reused = (270.0f-rotation.y) * 0.0174532925f;
	position.setX( position.getX() - sin(reused) * factor * *camerasensitivity );
	position.setZ( position.getZ() - cos(reused) * factor * *camerasensitivity );
}

void Camera::moveUpXZ(const float& factor)
{
	position.setY( position.getY() - factor * *camerasensitivity );
}

void Camera::moveUpXYZ(const float& factor)
{
	float reusedX = (360.0f-rotation.x) * 0.0174532925f;
	float reusedY = (360.0f-rotation.y) * 0.0174532925f;

	position.setX( position.getX() - sin(reusedY) * sin(reusedX) * factor * *camerasensitivity );
	position.setY( position.getY() - cos(reusedX) * factor * *camerasensitivity );
	position.setZ( position.getZ() - cos(reusedY) * sin(reusedX) * factor * *camerasensitivity );
}

void Camera::moveDownXZ(const float& factor)
{
	position.setY( position.getY() + factor * *camerasensitivity );
}

void Camera::moveDownXYZ(const float& factor)
{
	float reusedX = (360.0f-rotation.x) * 0.0174532925f;
	float reusedY = (360.0f-rotation.y) * 0.0174532925f;

	position.setX( position.getX() + sin(reusedY) * sin(reusedX) * factor * *camerasensitivity );
	position.setY( position.getY() + cos(reusedX) * factor * *camerasensitivity );
	position.setZ( position.getZ() + cos(reusedY) * sin(reusedX) * factor * *camerasensitivity );
}

void Camera::rollLeft(const float& factor)
{
	rotation.z += factor * *camerasensitivity;
}

void Camera::rollRight(const float& factor)
{
	rotation.z -= factor * *camerasensitivity;
}

// Looking

void Camera::lookRight(const float& factor)
{
        rotation.y += factor * *camerasensitivity;
	if ( rotation.y > 360.0f ) rotation.y -= 360.0f;
}

void Camera::lookLeft(const float& factor)
{
        rotation.y -= factor * *camerasensitivity;
	if ( rotation.y < 0.0f ) rotation.y += 360.0f;
}

void Camera::lookUp(const float& factor)
{
        rotation.x -= factor * *camerasensitivity;
	if ( rotation.x < 0.0f ) rotation.x += 360.0f;
}

void Camera::lookDown(const float& factor)
{
        rotation.x += factor * *camerasensitivity;
	if ( rotation.x > 360.0f ) rotation.x -= 360.0f;
}

btVector3 Camera::getScreenDirection(const int& x, const int& y)
{
	float directiondepth = 1000000.f;
	btVector3 origin = position;

	float reusedX = (360.0f-rotation.x) * 0.0174532925f;
	float reusedY = (rotation.y) * 0.0174532925f;
	
	float sinX = sin(reusedX);
	float sinY = sin(reusedY);
	float cosX = cos(reusedX);
	float cosY = cos(reusedY);

	btVector3 forwardRay = btVector3( sinY * cosX, -sinX, cosY * cosX ) * directiondepth;
	btVector3 upRay = btVector3( -sinY * sinX, -cosX, -cosY * sinX );

	btVector3 hor = forwardRay.cross(upRay);
	hor.normalize();
	hor *= directiondepth;

	upRay = hor.cross(forwardRay);
	upRay.normalize();
	upRay *= directiondepth * ((float)*settings->winHeight / *settings->winWidth);

	btVector3 rayTo = (origin + forwardRay) - (0.5f * hor) + (0.5f * upRay);
	rayTo += x * (hor * (1.0f/((float)*settings->winWidth)));
	rayTo -= y * (upRay * (1.0f/((float)*settings->winHeight)));

	// FIXME
	rayTo.setY(-rayTo.getY());
	rayTo.setZ(-rayTo.getZ());

	return rayTo;
}

Camera::~Camera()
{
}
