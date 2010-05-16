
#include "camera.h"
#include <cmath>

using namespace std;

Camera::Camera()
{
	settings = Settings::Instance();
	camerasensitivity = settings->getCVarPtr("camerasensitivity");

	position.setIdentity();
}

void Camera::place()
{
	glViewport(0,0,*settings->winWidth,*settings->winHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float nheight = 0.05f * ((float)(*settings->winHeight) / *settings->winWidth);
	glFrustum(-0.05f,0.05f,-nheight,nheight,0.1f,10000.0f);

// 	btVector3 loc = position.getOrigin();
// 	glRotatef(x*57.2957795131, 1.0f, 0.0f, 0.0f);
// 	glRotatef(y*57.2957795131, 0.0f, 1.0f, 0.0f);
// 	glRotatef(z*57.2957795131, 0.0f, 0.0f, 1.0f);
//  	glTranslatef(-position.getOrigin().getX(), -position.getOrigin().getY(), -position.getOrigin().getZ());

	position.inverse().getOpenGLMatrix(positionr);
	glMultMatrixf(positionr);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Camera::follow(btDefaultMotionState* myMotionState)
{
	glViewport(
		*settings->winWidth - *settings->winWidth/8,
		0,
		*settings->winWidth/8,
		*settings->winHeight/8
	);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	float nheight = 0.05f * ((float)(*settings->winHeight) / *settings->winWidth);
	glFrustum( -0.05f, 0.05f,-nheight,nheight, 0.1f, 10000.0f);

// 	btScalar positionr[16];
	myMotionState->m_graphicsWorldTrans.inverse().getOpenGLMatrix(positionr);
	glMultMatrixf(positionr);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Moving

void Camera::moveForward(const float& factor)
{
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin( btVector3(0.0f, 0.0f, -factor * *camerasensitivity) );
	position *= tr;
}

void Camera::moveBackward(const float& factor)
{
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin( btVector3(0.0f, 0.0f, factor * *camerasensitivity) );
	position *= tr;
}

void Camera::moveRight(const float& factor)
{
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin( btVector3(factor * *camerasensitivity, 0.0f, 0.0f) );
	position *= tr;
}

void Camera::moveLeft(const float& factor)
{
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin( btVector3(-factor * *camerasensitivity, 0.0f, 0.0f) );
	position *= tr;
}

void Camera::moveUp(const float& factor)
{
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin( btVector3(0.0f, factor * *camerasensitivity, 0.0f) );
	position *= tr;
}

void Camera::moveDown(const float& factor)
{
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin( btVector3(0.0f, -factor * *camerasensitivity, 0.0f) );
	position *= tr;
}

void Camera::rollLeft(const float& factor)
{
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(btVector3(0,0,0));
	tr.getBasis().setEulerZYX( 0.0f, 0.0f, factor * *camerasensitivity );
	position.getBasis() *= tr.getBasis();
}

void Camera::rollRight(const float& factor)
{
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(btVector3(0,0,0));
	tr.getBasis().setEulerZYX( 0.0f, 0.0f, -factor * *camerasensitivity );
	position.getBasis() *= tr.getBasis();
}

// Looking

void Camera::lookRight(const float& factor)
{
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(btVector3(0,0,0));
	tr.getBasis().setEulerZYX( 0.0f, -factor * *camerasensitivity, 0.0f );
	position.getBasis() *= tr.getBasis();
}

void Camera::lookLeft(const float& factor)
{
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(btVector3(0,0,0));
	tr.getBasis().setEulerZYX( 0.0f, factor * *camerasensitivity, 0.0f );
	position *= tr;
}

void Camera::lookUp(const float& factor)
{
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(btVector3(0,0,0));
	tr.getBasis().setEulerZYX( factor * *camerasensitivity, 0.0f, 0.0f );
	position *= tr;
}

void Camera::lookDown(const float& factor)
{
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(btVector3(0,0,0));
	tr.getBasis().setEulerZYX( -factor * *camerasensitivity, 0.0f, 0.0f );
	position *= tr;
}

void Camera::moveTowards(const btVector3& direction)
{
	position.setOrigin( position.getOrigin() + direction ); 
}

void Camera::moveAwayFrom(const btVector3& direction)
{
	position.setOrigin( position.getOrigin() - direction ); 
}

btVector3 Camera::getScreenDirection(const int& x, const int& y)
{
	float directionlength = 1000000.f;

	btVector3 forwardRay( 
		-position.getBasis()[0][2], 
		-position.getBasis()[1][2], 
		-position.getBasis()[2][2]); 
	forwardRay *=  directionlength;

	btVector3 upRay( 
		position.getBasis()[0][1], 
		position.getBasis()[1][1], 
		position.getBasis()[2][1]); 

	btVector3 hor = forwardRay.cross(upRay);
	hor.normalize();
	hor *= directionlength;

	upRay = hor.cross(forwardRay);
	upRay.normalize();
	upRay *= directionlength * ((float)*settings->winHeight / *settings->winWidth);

	btVector3 rayTo = (position.getOrigin() + forwardRay) - (0.5f * hor) + (0.5f * upRay);
	rayTo += x * (hor * (1.0f/((float)*settings->winWidth)));
	rayTo -= y * (upRay * (1.0f/((float)*settings->winHeight)));

	return rayTo;
}

Camera::~Camera()
{
}
