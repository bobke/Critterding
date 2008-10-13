
#include "camera.h"
#include <cmath>


using namespace std;

Camera::Camera()
{
	position	= Vector3f( 0.0f, 0.0f, 0.0f);
	rotation	= Vector3f( 76.0f,  0.0f, 0.0f);

	sensitivity	= 1;
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
	glTranslatef(position.x, position.y, position.z);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// FIXME as in take the REAL camera of the critter to look at
void Camera::follow(Vector3f &cameraposition, float &rotation)
{
	float nheight = 0.05f * ((float)(*Settings::Instance()->winHeight) / *Settings::Instance()->winWidth);
	glViewport(0,0,*Settings::Instance()->winWidth,*Settings::Instance()->winHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum( -0.05f, 0.05f,-nheight,nheight, 0.1f, Settings::Instance()->critter_sightrange);

	glRotatef(rotation, 0.0f, -1.0f, 0.0f);
	glTranslatef(-cameraposition.x, -cameraposition.y, -cameraposition.z);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Moving

void Camera::moveForwardXZ(const float& factor)
{
	float reusedY = (360.0f-rotation.y) * 0.0174532925f;

	position.x += sin(reusedY) * factor * sensitivity;
	position.z += cos(reusedY) * factor * sensitivity;

/*	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;*/
}

void Camera::moveBackwardXZ(const float& factor)
{
	float reusedY = (360.0f-rotation.y) * 0.0174532925f;

	position.x -= sin(reusedY) * factor * sensitivity;
	position.z -= cos(reusedY) * factor * sensitivity;

/*	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;*/
}

void Camera::moveForwardXYZ(const float& factor)
{
	float reusedX = (360.0f-rotation.x) * 0.0174532925f;
	float reusedY = (360.0f-rotation.y) * 0.0174532925f;

	position.x += sin(reusedY) * cos(reusedX) * factor * sensitivity;
	position.y -= sin(reusedX) * factor * sensitivity;
	position.z += cos(reusedY) * cos(reusedX) * factor * sensitivity;

/*	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;*/
}

void Camera::moveBackwardXYZ(const float& factor)
{
	float reusedX = (360.0f-rotation.x) * 0.0174532925f;
	float reusedY = (360.0f-rotation.y) * 0.0174532925f;

	position.x -= sin(reusedY) * cos(reusedX) * factor * sensitivity;
	position.y += sin(reusedX) * factor * sensitivity;
	position.z -= cos(reusedY) * cos(reusedX) * factor * sensitivity;

/*	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;*/
}

void Camera::moveRight(const float& factor)
{
	float reused = (90.0f-rotation.y) * 0.0174532925f;
	position.x -= sin(reused) * factor * sensitivity;
	position.z -= cos(reused) * factor * sensitivity;

/*	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;*/
}

void Camera::moveLeft(const float& factor)
{
	float reused = (270.0f-rotation.y) * 0.0174532925f;
	position.x -= sin(reused) * factor * sensitivity;
	position.z -= cos(reused) * factor * sensitivity;

/*	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;*/
}

void Camera::moveUp(const float& factor)
{
	position.y -= factor * sensitivity;

/*	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;*/
}

void Camera::moveDown(const float& factor)
{
	position.y += factor * sensitivity;

/*	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;*/
}

void Camera::rollLeft(const float& factor)
{
	rotation.z += factor * sensitivity;
}

void Camera::rollRight(const float& factor)
{
	rotation.z -= factor * sensitivity;
}


// Looking

void Camera::lookRight(const float& factor)
{
        rotation.y += factor * sensitivity;
	if ( rotation.y > 360.0f ) rotation.y -= 360.0f;

/*	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;*/
}

void Camera::lookLeft(const float& factor)
{
        rotation.y -= factor * sensitivity;
	if ( rotation.y < 0.0f ) rotation.y += 360.0f;

/*	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;*/
}

void Camera::lookUp(const float& factor)
{
        rotation.x += factor * sensitivity;
	if ( rotation.x > 360.0f ) rotation.x -= 360.0f;

/*	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;*/
}

void Camera::lookDown(const float& factor)
{
        rotation.x -= factor * sensitivity;
	if ( rotation.x < 0.0f ) rotation.x += 360.0f;

/*	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;*/
}

Camera::~Camera()
{
}
