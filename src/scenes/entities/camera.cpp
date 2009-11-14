
#include "camera.h"
#include <cmath>

using namespace std;

Camera::Camera()
{
	settings = Settings::Instance();
	camerasensitivity = settings->getCVarPtr("camerasensitivity");

// 	position	= btVector3( 0.0f, 0.0f, 0.0f);
// 	rotation	= Vector3f( 90.0f,  0.0f, 0.0f);
	position.setIdentity();
// 	position.setOrigin( btVector3(-5.0f, 10.0f, 0.0f) );
// 	position.getBasis().setEulerZYX( 75.0f*.18f, 0.0f, 0.0f );
// 	position.setOrigin( btVector3(0.0f, 0.0f, 0.0f) );
}

void Camera::place()
{
	glViewport(0,0,*settings->winWidth,*settings->winHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float nheight = 0.5f * ((float)(*settings->winHeight) / *settings->winWidth);
	glFrustum(-0.5f,0.5f,-nheight,nheight,1.0f,10000.0f);

// 	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
// 	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
// 	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
//  	glTranslatef(position.getOrigin().getX(), position.getOrigin().getY(), position.getOrigin().getZ());

	btScalar positionr[16];
	position.inverse().getOpenGLMatrix(positionr);
	glMultMatrixf(positionr);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Camera::follow(btDefaultMotionState* myMotionState) const
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

	btScalar position[16];
	myMotionState->m_graphicsWorldTrans.inverse().getOpenGLMatrix(position);
	glMultMatrixf(position);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Moving

void Camera::moveForward(const float& factor)
{
// 	position.getOrigin() += position.getBasis()[2] * factor;
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin( btVector3(0.0f, 0.0f, -factor * *camerasensitivity) ); // 1.5707f  (float)settings->getCVar("energy")/10
	position *= tr;
}

void Camera::moveBackward(const float& factor)
{
// 	position.getOrigin() -= position.getBasis()[2] * factor;
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin( btVector3(0.0f, 0.0f, factor * *camerasensitivity) ); // 1.5707f  (float)settings->getCVar("energy")/10
	position *= tr;
}

void Camera::moveRight(const float& factor)
{
// 	position.getOrigin() += position.getBasis()[0] * factor;
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin( btVector3(factor * *camerasensitivity, 0.0f, 0.0f) ); // 1.5707f  (float)settings->getCVar("energy")/10
	position *= tr;
}

void Camera::moveLeft(const float& factor)
{
// 	position.getOrigin() -= position.getBasis()[0] * factor;
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin( btVector3(-factor * *camerasensitivity, 0.0f, 0.0f) ); // 1.5707f  (float)settings->getCVar("energy")/10
	position *= tr;
}

void Camera::moveUp(const float& factor)
{
// 	position.getOrigin() -= position.getBasis()[1] * factor;
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin( btVector3(0.0f, factor * *camerasensitivity, 0.0f) ); // 1.5707f  (float)settings->getCVar("energy")/10
	position *= tr;
}

void Camera::moveDown(const float& factor)
{
// 	position.getOrigin() += position.getBasis()[1] * factor;
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin( btVector3(0.0f, -factor * *camerasensitivity, 0.0f) ); // 1.5707f  (float)settings->getCVar("energy")/10
	position *= tr;
}

void Camera::rollLeft(const float& factor)
{
// 	rotation.z += factor * *camerasensitivity;
}

void Camera::rollRight(const float& factor)
{
// 	rotation.z -= factor * *camerasensitivity;
}

// Looking

void Camera::lookRight(const float& factor)
{
//         rotation.y += factor * *camerasensitivity;
// 	if ( rotation.y > 360.0f ) rotation.y -= 360.0f;
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(btVector3(0,0,0));
	tr.getBasis().setEulerZYX( 0.0f, -factor * *camerasensitivity, 0.0f ); // 1.5707f  (float)settings->getCVar("energy")/10
	position.getBasis() *= tr.getBasis();
}

void Camera::lookLeft(const float& factor)
{
//         rotation.y -= factor * *camerasensitivity;
// 	if ( rotation.y < 0.0f ) rotation.y += 360.0f;
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(btVector3(0,0,0));
	tr.getBasis().setEulerZYX( 0.0f, factor * *camerasensitivity, 0.0f ); // 1.5707f  (float)settings->getCVar("energy")/10
	position *= tr;
}

void Camera::lookUp(const float& factor)
{
//         rotation.x -= factor * *camerasensitivity;
// 	if ( rotation.x < 0.0f ) rotation.x += 360.0f;

	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(btVector3(0,0,0));
	tr.getBasis().setEulerZYX( factor * *camerasensitivity, 0.0f, 0.0f ); // 1.5707f  (float)settings->getCVar("energy")/10
	position *= tr;
}

void Camera::lookDown(const float& factor)
{
//         rotation.x += factor * *camerasensitivity;
// 	if ( rotation.x > 360.0f ) rotation.x -= 360.0f;

	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(btVector3(0,0,0));
	tr.getBasis().setEulerZYX( -factor * *camerasensitivity, 0.0f, 0.0f ); // 1.5707f  (float)settings->getCVar("energy")/10
	position *= tr;
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

 		
	
/*	float directiondepth = 1000000.f;
	btVector3 origin = position;

	float reusedX = (360.0f-rotation.x) * 0.0174532925f;
	float reusedY = rotation.y * 0.0174532925f;
	float reusedZ = rotation.z * 0.0174532925f;
	
	float sinX = sin(reusedX);
	float sinY = sin(reusedY);
// 	float sinZ = sin(reusedZ);
	float cosX = cos(reusedX);
	float cosY = cos(reusedY);
// 	float cosZ = cos(reusedZ);

// 	cerr << sinZ << endl;
	
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
// 	rayTo.setX(-rayTo.getX());
	rayTo.setY(-rayTo.getY());
	rayTo.setZ(-rayTo.getZ());

 	return rayTo;
*/
}

Camera::~Camera()
{
}
