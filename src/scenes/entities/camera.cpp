
#include "camera.h"
#include <cmath>


using namespace std;

Camera::Camera()
{
	position	= Vector3f(-1.5, -10.0, -4.5);
	rotation	= Vector3f( 80.0,  0.0, 0.0);
}


Camera::~Camera()
{
}

void Camera::place(unsigned int *width, unsigned int *height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,*width,*height);
	float nheight = 0.5f * ((float)(*height) / *width);
	glFrustum(-0.5f,0.5f,-nheight,nheight,1.0f,10000.0f);

//	glLoadIdentity();
	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
	glTranslatef(position.x, position.y, position.z);
}

// Moving

void Camera::moveForward(const float& factor)
{
	float reused = (360.0f-rotation.y) * 0.0174532925f;
        position.x += sin(reused) * factor;
        position.z += cos(reused) * factor;
}

void Camera::moveBackward(const float& factor)
{
	float reused = (360.0f-rotation.y) * 0.0174532925f;
        position.x -= sin(reused) * factor;
        position.z -= cos(reused) * factor;
}

void Camera::moveRight(const float& factor)
{
	float reused = (90.0f-rotation.y) * 0.0174532925f;
        position.x -= sin(reused) * factor;
        position.z -= cos(reused) * factor;
}

void Camera::moveLeft(const float& factor)
{
	float reused = (270.0f-rotation.y) * 0.0174532925f;
        position.x -= sin(reused) * factor;
        position.z -= cos(reused) * factor;
}

void Camera::moveUp(const float& factor)
{
	position.y -= factor;
}

void Camera::moveDown(const float& factor)
{
	position.y += factor;
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
