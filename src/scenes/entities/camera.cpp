
#include "camera.h"
#include <cmath>


using namespace std;

Camera::Camera()
{
	position	= Vector3f(-2.5, -5.36942, -4.60814);
//	position	= Vector3f(-5.0, -10.5, -8.66);
	rotation	= Vector3f( 74.0,  0.0, 0.0);
}


Camera::~Camera()
{
}

void Camera::place(unsigned int *width, unsigned int *height)
{
	glViewport(0,0,*width,*height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float nheight = 0.5f * ((float)(*height) / *width);
	glFrustum(-0.5f,0.5f,-nheight,nheight,1.0f,10000.0f);

	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
	glTranslatef(position.x, position.y, position.z);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Camera::follow(unsigned int *width, unsigned int *height, CritterB *c)
{
	glViewport(0,0,*width,*height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float nheight = 0.05f * ((float)(*height) / *width);
	glFrustum(-0.05f,0.05f,-nheight,nheight,0.1f,5.0f);

	glRotatef(c->rotation, 0.0f, -1.0f, 0.0f);
	glTranslatef(-c->cameraposition.x, -c->cameraposition.y, -c->cameraposition.z);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Moving

void Camera::moveForward(const float& factor)
{
	float reusedX = (360.0f-rotation.x) * 0.0174532925f;
	float reusedY = (360.0f-rotation.y) * 0.0174532925f;

	position.x += sin(reusedY) * cos(reusedX) * factor;
	position.y -= sin(reusedX) * factor;
	position.z += cos(reusedY) * cos(reusedX) * factor;

	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;
}

void Camera::moveBackward(const float& factor)
{
	float reusedX = (360.0f-rotation.x) * 0.0174532925f;
	float reusedY = (360.0f-rotation.y) * 0.0174532925f;

	position.x -= sin(reusedY) * cos(reusedX) * factor;
	position.y += sin(reusedX) * factor;
	position.z -= cos(reusedY) * cos(reusedX) * factor;

	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;
}

void Camera::moveRight(const float& factor)
{
	float reused = (90.0f-rotation.y) * 0.0174532925f;
	position.x -= sin(reused) * factor;
	position.z -= cos(reused) * factor;

	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;
}

void Camera::moveLeft(const float& factor)
{
	float reused = (270.0f-rotation.y) * 0.0174532925f;
	position.x -= sin(reused) * factor;
	position.z -= cos(reused) * factor;

	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;
}

void Camera::moveUp(const float& factor)
{
	position.y -= factor;

	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;
}

void Camera::moveDown(const float& factor)
{
	position.y += factor;

	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;
}

void Camera::rollLeft(const float& factor)
{
	rotation.z += factor;
}

void Camera::rollRight(const float& factor)
{
	rotation.z -= factor;
}


// Looking

void Camera::lookRight(const float& factor)
{
        rotation.y += factor;
	if ( rotation.y > 360.0f ) rotation.y -= 360.0f;

	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;
}

void Camera::lookLeft(const float& factor)
{
        rotation.y -= factor;
	if ( rotation.y < 0.0f ) rotation.y += 360.0f;

	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;
}

void Camera::lookUp(const float& factor)
{
        rotation.x += factor;
	if ( rotation.x > 360.0f ) rotation.x -= 360.0f;

	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;
}

void Camera::lookDown(const float& factor)
{
        rotation.x -= factor;
	if ( rotation.x < 0.0f ) rotation.x += 360.0f;

	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;
}
