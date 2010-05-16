#ifndef CONCAVEFLOOR_H
#define CONCAVEFLOOR_H

#include "../entities/worldb.h"

class GlDrawcallback : public btTriangleCallback
{
public:

	bool	m_wireframe;

	GlDrawcallback()
		:m_wireframe(false)
	{
// 		cerr << "hello0" << endl;
	}

	virtual void processTriangle(btVector3* triangle,int partId, int triangleIndex)
	{
// 		cerr << "hello" << endl;

		(void)triangleIndex;
		(void)partId;

		if (m_wireframe)
		{
			glBegin(GL_LINES);
			glColor3f(1, 0, 0);
			glVertex3d(triangle[0].getX(), triangle[0].getY(), triangle[0].getZ());
			glVertex3d(triangle[1].getX(), triangle[1].getY(), triangle[1].getZ());
			glColor3f(0, 1, 0);
			glVertex3d(triangle[2].getX(), triangle[2].getY(), triangle[2].getZ());
			glVertex3d(triangle[1].getX(), triangle[1].getY(), triangle[1].getZ());
			glColor3f(0, 0, 1);
			glVertex3d(triangle[2].getX(), triangle[2].getY(), triangle[2].getZ());
			glVertex3d(triangle[0].getX(), triangle[0].getY(), triangle[0].getZ());
			glEnd();
		} else
		{
			glBegin(GL_TRIANGLES);
			//glColor3f(1, 1, 1);
			
			
			glVertex3d(triangle[0].getX(), triangle[0].getY(), triangle[0].getZ());
			glVertex3d(triangle[1].getX(), triangle[1].getY(), triangle[1].getZ());
			glVertex3d(triangle[2].getX(), triangle[2].getY(), triangle[2].getZ());

			glVertex3d(triangle[2].getX(), triangle[2].getY(), triangle[2].getZ());
			glVertex3d(triangle[1].getX(), triangle[1].getY(), triangle[1].getZ());
			glVertex3d(triangle[0].getX(), triangle[0].getY(), triangle[0].getZ());
			glEnd();
		}
// 		cerr << "hello" << endl;
	}
};

class Concavefloor : public WorldB {

	public:
		Concavefloor();
		~Concavefloor();

		void		process();
		void		init();
		void		drawWithGrid();
	private:
		const unsigned int* worldsizeZ;
// 		void		drawSphere(btScalar radius, int lats, int longs);
// 		btVector3	findPosition();
		void		makeFloor();
		void		drawfloor(float dim);
// 		void		childPositionOffset(btVector3* v);
		void		setVertexPositions(float waveheight, float offset);

// 		btCollisionObject* fixedGround;
		btRigidBody* fixedGround;
		btCollisionShape* groundShape;
		btTransform groundTransform;
		btDefaultSerializer* serializer;
		btVector3 aabbMin;
		btVector3 aabbMax;


		btVector3* gVertices;
		btTriangleIndexVertexArray* m_indexVertexArrays;
		int* gIndices;
		btBvhTriangleMeshShape* trimeshShape;
		float waveheight;
		float TRIANGLE_SIZE;
		int NUM_VERTS_X;
		int NUM_VERTS_Y;
		int totalVerts;
		int border;
		GlDrawcallback drawCallback;

};

#endif
