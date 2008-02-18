
#include "camera.h"
#include <cmath>


using namespace std;

Camera::Camera()
{
	// for 7*7 use 				position	= Vector3f(-3.5, -8.0, -5.2);

	position	= Vector3f(-3.5, -8.0, -5.2);
	rotation	= Vector3f( 80.0,  0.0, 0.0);
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

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glTranslatef(position.x, position.y, position.z);

}

void Camera::follow(unsigned int *width, unsigned int *height, Critter *c)
{
	glViewport(0,0,*width,*height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float nheight = 0.05f * ((float)(*height) / *width);
	glFrustum(-0.05f,0.05f,-nheight,nheight,0.1f,100.0f);

	glRotatef(0.0f, -1.0f, 0.0f, 0.0f);
	glRotatef(c->rotation, 0.0f, -1.0f, 0.0f);
	glTranslatef(-c->cameraposition.x, -c->cameraposition.y, -c->cameraposition.z);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Moving

void Camera::moveForward(const float& factor)
{
	float reused = (360.0f-rotation.y) * 0.0174532925f;
        position.x += sin(reused) * factor;
        position.z += cos(reused) * factor;
//	cerr << " camera: " << position.x << ":" << position.y << ":" << position.z << endl;
}

void Camera::moveBackward(const float& factor)
{
	float reused = (360.0f-rotation.y) * 0.0174532925f;
        position.x -= sin(reused) * factor;
        position.z -= cos(reused) * factor;
//	cerr << " camera: " << position.x << ":" << position.y << ":" << position.z << endl;
}

void Camera::moveRight(const float& factor)
{
	float reused = (90.0f-rotation.y) * 0.0174532925f;
        position.x -= sin(reused) * factor;
        position.z -= cos(reused) * factor;
//	cerr << " camera: " << position.x << ":" << position.y << ":" << position.z << endl;
}

void Camera::moveLeft(const float& factor)
{
	float reused = (270.0f-rotation.y) * 0.0174532925f;
        position.x -= sin(reused) * factor;
        position.z -= cos(reused) * factor;
//	cerr << " camera: " << position.x << ":" << position.y << ":" << position.z << endl;
}

void Camera::moveUp(const float& factor)
{
	position.y -= factor;
//	cerr << " camera: " << position.x << ":" << position.y << ":" << position.z << endl;
}

void Camera::moveDown(const float& factor)
{
	position.y += factor;
//	cerr << " camera: " << position.x << ":" << position.y << ":" << position.z << endl;
}


// Looking

void Camera::lookRight(const float& factor)
{
        rotation.y += factor;
//	cout << rotation.y << endl;
}

void Camera::lookLeft(const float& factor)
{
        rotation.y -= factor;
//	cout << rotation.y << endl;
}

void Camera::lookUp(const float& factor)
{
        rotation.x += factor;
//	cout << rotateX << endl;
}

void Camera::lookDown(const float& factor)
{
        rotation.x -= factor;
//	cout << rotateX << endl;

}
