
#include "camera.h"
#include <cmath>

using namespace std;

Camera::Camera()
{
	settings = Settings::Instance();
	camerasensitivity = settings->getCVarPtr("camerasensitivity");

	position	= Vector3f( 0.0f, 0.0f, 0.0f);
	rotation	= Vector3f( 75.0f,  0.0f, 0.0f);
}

void Camera::place()
{
	glViewport(0,0,*Settings::Instance()->winWidth,*Settings::Instance()->winHeight);
// 	glViewport(0,0,800,600);

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
// 	glFrustum( -0.05f, 0.05f,-nheight,nheight, 0.1f, Settings::Instance()->critter_sightrange);
	glFrustum( -0.05f, 0.05f,-nheight,nheight, 0.1f, 10000.0f);

 	glRotatef(4.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation, 0.0f, -1.0f, 0.0f);

// 	glTranslatef(-cameraposition.x, -cameraposition.y, -cameraposition.z);

	float reused = rotation * 0.0174532925f;
	float x = cameraposition.x + (sin(reused) * 1.0f);
 	float z = cameraposition.z + (cos(reused) * 1.0f);
  	float y = cameraposition.y + 0.35f;
	glTranslatef(-x, -y, -z);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Camera::follow(btDefaultMotionState* myMotionState) const
{
	float nheight = 0.05f * ((float)(*Settings::Instance()->winHeight) / *Settings::Instance()->winWidth);
	glViewport(
		*Settings::Instance()->winWidth - *Settings::Instance()->winWidth/8,
		0,
		*Settings::Instance()->winWidth/8,
		*Settings::Instance()->winHeight/8
	);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum( -0.05f, 0.05f,-nheight,nheight, 0.1f, 10000.0f);

	btScalar position[16];
	btTransform tr = myMotionState->m_graphicsWorldTrans.inverse();
	tr.getOpenGLMatrix(position);
	glMultMatrixf(position);

//  	myMotionState->m_graphicsWorldTrans.getOpenGLMatrix(position);
// 	float revposition[16] = {0};
//         revposition[0]  = position[0]; revposition[1] = position[4]; revposition[2]  = position[8];
//         revposition[4]  = position[1]; revposition[5] = position[5]; revposition[6]  = position[9];
//         revposition[8]  = position[2]; revposition[9] = position[6]; revposition[10] = position[10];
//         revposition[3]  = 0.0f; revposition[7] = 0.0f; revposition[11] = 0.0f;
//         revposition[15] = 1.0f;
// 
//         revposition[12] = -(position[12] * position[0]) - (position[13] * position[1]) - (position[14] * position[2]);
//         revposition[13] = -(position[12] * position[4]) - (position[13] * position[5]) - (position[14] * position[6]);
//         revposition[14] = -(position[12] * position[8]) - (position[13] * position[9]) - (position[14] * position[10]);
//  	glMultMatrixf(revposition);

// 	rayToTrans.setIdentity();
// 	rayToTrans.setOrigin(rayTo);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Moving

void Camera::moveForwardXZ(const float& factor)
{
	float reusedY = (360.0f-rotation.y) * 0.0174532925f;

	position.x += sin(reusedY) * factor * *camerasensitivity;
	position.z += cos(reusedY) * factor * *camerasensitivity;

// 	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
// 	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;
}

void Camera::moveBackwardXZ(const float& factor)
{
	float reusedY = (360.0f-rotation.y) * 0.0174532925f;

	position.x -= sin(reusedY) * factor * *camerasensitivity;
	position.z -= cos(reusedY) * factor * *camerasensitivity;

/*	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;*/
}

void Camera::moveForwardXYZ(const float& factor)
{
	float reusedX = (360.0f-rotation.x) * 0.0174532925f;
	float reusedY = (360.0f-rotation.y) * 0.0174532925f;

	position.x += sin(reusedY) * cos(reusedX) * factor * *camerasensitivity;
	position.y -= sin(reusedX) * factor * *camerasensitivity;
	position.z += cos(reusedY) * cos(reusedX) * factor * *camerasensitivity;

/*	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;*/
}

void Camera::moveBackwardXYZ(const float& factor)
{
	float reusedX = (360.0f-rotation.x) * 0.0174532925f;
	float reusedY = (360.0f-rotation.y) * 0.0174532925f;

	position.x -= sin(reusedY) * cos(reusedX) * factor * *camerasensitivity;
	position.y += sin(reusedX) * factor * *camerasensitivity;
	position.z -= cos(reusedY) * cos(reusedX) * factor * *camerasensitivity;

/*	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;*/
}

void Camera::moveRight(const float& factor)
{
	float reused = (90.0f-rotation.y) * 0.0174532925f;
	position.x -= sin(reused) * factor * *camerasensitivity;
	position.z -= cos(reused) * factor * *camerasensitivity;

/*	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;*/
}

void Camera::moveLeft(const float& factor)
{
	float reused = (270.0f-rotation.y) * 0.0174532925f;
	position.x -= sin(reused) * factor * *camerasensitivity;
	position.z -= cos(reused) * factor * *camerasensitivity;

/*	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;*/
}

void Camera::moveUp(const float& factor)
{
	position.y -= factor * *camerasensitivity;

/*	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;*/
}

void Camera::moveDown(const float& factor)
{
	position.y += factor * *camerasensitivity;

/*	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;*/
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

/*	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;*/
}

void Camera::lookLeft(const float& factor)
{
        rotation.y -= factor * *camerasensitivity;
	if ( rotation.y < 0.0f ) rotation.y += 360.0f;

/*	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;*/
}

void Camera::lookUp(const float& factor)
{
        rotation.x -= factor * *camerasensitivity;
	if ( rotation.x < 0.0f ) rotation.x += 360.0f;

/*	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;*/
}

void Camera::lookDown(const float& factor)
{
        rotation.x += factor * *camerasensitivity;
	if ( rotation.x > 360.0f ) rotation.x -= 360.0f;

/*	cerr << " camera rot: " << rotation.x << ":" << rotation.y << ":" << rotation.z << endl;
	cerr << " camera pos: " << position.x << ":" << position.y << ":" << position.z << endl;*/
}

Camera::~Camera()
{
}
