#include "mesh.h"
using std::cerr;
using std::endl;



Mesh::Mesh()
{
}

void Mesh::draw()
{
/*	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer (3,GL_FLOAT,sizeof(struct Vertex), vertices);
*/

	glBegin(GL_TRIANGLES);
	for (unsigned int i=0; i < nTriangles; i++)
	{
		Triangle &triangle = triangles[i];
		
		glNormal3f(triangle.verts[0] -> normal.x, triangle.verts[0] -> normal.y, triangle.verts[0] -> normal.z);
		
		glVertex3f(triangle.verts[0] -> position.x, triangle.verts[0] -> position.y, triangle.verts[0] -> position.z);
		
		glNormal3f(triangle.verts[1] -> normal.x, triangle.verts[1] -> normal.y, triangle.verts[1] -> normal.z);
		
		glVertex3f(triangle.verts[1] -> position.x, triangle.verts[1] -> position.y, triangle.verts[1] -> position.z);
		
		glNormal3f(triangle.verts[2] -> normal.x, triangle.verts[2] -> normal.y, triangle.verts[2] -> normal.z);
		
		glVertex3f(triangle.verts[2] -> position.x, triangle.verts[2] -> position.y, triangle.verts[2] -> position.z);
	}
	glEnd();

/*	//	Draw the NormalS
	glBegin(GL_LINES);
	for (unsigned int i=0; i < nTriangles; i++)
	{
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(triangles[i].normal.x()*2, triangles[i].normal.y()*2, triangles[i].normal.z()*2);
	}
	for (unsigned int j=0; j < nVertices; j++)
	{
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(vertices[j].normal.x()*2, vertices[j].normal.y()*2, vertices[j].normal.z()*2);

	}
	glEnd();
*/

}


void Mesh::create()
{
	vertices[0].position = Vector3f( 0.0f, size, 0.0f);
	vertices[1].position = Vector3f( size, 0.0f,-size);
	vertices[2].position = Vector3f(-size, 0.0f,-size);
	vertices[3].position = Vector3f(-size, 0.0f, size);
	vertices[4].position = Vector3f( size, 0.0f, size);
	vertices[5].position = Vector3f( 0.0f, -size, 0.0f);

	triangles[0].verts[0]=&vertices[0]; triangles[0].verts[1]=&vertices[1]; triangles[0].verts[2]=&vertices[2];
	triangles[1].verts[0]=&vertices[0]; triangles[1].verts[1]=&vertices[2]; triangles[1].verts[2]=&vertices[3];
	triangles[2].verts[0]=&vertices[0]; triangles[2].verts[1]=&vertices[3]; triangles[2].verts[2]=&vertices[4];
	triangles[3].verts[0]=&vertices[0]; triangles[3].verts[1]=&vertices[4]; triangles[3].verts[2]=&vertices[1];

	triangles[4].verts[0]=&vertices[5]; triangles[4].verts[1]=&vertices[2]; triangles[4].verts[2]=&vertices[1];
	triangles[5].verts[0]=&vertices[5]; triangles[5].verts[1]=&vertices[3]; triangles[5].verts[2]=&vertices[2];
	triangles[6].verts[0]=&vertices[5]; triangles[6].verts[1]=&vertices[4]; triangles[6].verts[2]=&vertices[3];
	triangles[7].verts[0]=&vertices[5]; triangles[7].verts[1]=&vertices[1]; triangles[7].verts[2]=&vertices[4];

// 	calcFaceNormals();
	createIndexVertices();
// 	calcVertexNormals();
}

/*
void Mesh2::calcFaceNormals()
{
	for (unsigned int i=0; i < nTriangles; i++)
	{
		Triangle &triangle = triangles[i];

		Vector3f a,b;
		a = triangle.verts[0] -> position - triangle.verts[1] -> position;
//		a = vertices[triangles[i].verts[0]].position - vertices[triangles[i].verts[1]].position;
		b = triangle.verts[0] -> position - triangle.verts[2] -> position;
//		b = vertices[triangles[i].verts[0]].position - vertices[triangles[i].verts[2]].position;

		// Take the Cross
		triangle.normal.x() = a.y() * b.z() - b.y() * a.z();
		triangle.normal.y() = a.z() * b.x() - b.z() * a.x();
		triangle.normal.z() = a.x() * b.y() - b.x() * a.y();
		// Normalize the Normal
		float normval = 
			(float) sqrt (triangle.normal.x()*triangle.normal.x()
			+ triangle.normal.y()*triangle.normal.y()
			+ triangle.normal.z()*triangle.normal.z());
		triangle.normal /= normval;

		//	Print normal values
		cerr << "Normal of triangle " << i << "= X=" << triangle.normal.x() << 
		", Y=" << triangle.normal.y() << 
		", Z=" << triangle.normal.z() << endl;
	}
}*/

void Mesh::createIndexVertices()
{
	// Create an index of the vertex incidents in the triangles
	//	for all Vertices
	for (unsigned int i=0; i < nVertices; i++)
	{
		//	for all triangles
		vertices[i].incidents = 0;
		for (unsigned int j=0; j < nTriangles; j++)
		{
			//	for each face vertex, check if its the same as the vertex in our current outer vertex loop.
			for (unsigned int k=0; k < 3; k++)
			{
				if (triangles[j].verts[k] -> position == vertices[i].position)
				{
					//add this face to linked list of this vertex
					vertices[i].occursinTriangles[vertices[i].incidents]=j;
					vertices[i].incidents++;
				}
			}
		}
	}

}
/*
void Mesh2::calcVertexNormals()
{

	// Calculate the Vertex normals
	for (unsigned int i=0; i < nVertices; i++)
	{
		vertices[i].normal=Vector3f(0.0f,0.0f,0.0f);
		// for all incidents
		for (unsigned int j=0; j < vertices[i].incidents; j++)
		{
			vertices[i].normal+=triangles[vertices[i].occursinTriangles[j]].normal;
		}

		// Normalize the Normal
		float normval = 
			(float) sqrt (vertices[i].normal.x()*vertices[i].normal.x()
			+ vertices[i].normal.y()*vertices[i].normal.y()
			+ vertices[i].normal.z()*vertices[i].normal.z());
		vertices[i].normal /= normval;

		//	Print normal values
		cerr << "Normal of vertex " << i << "= X=" << vertices[i].normal.x() << 
		", Y=" << vertices[i].normal.y() << 
		", Z=" << vertices[i].normal.z() << endl;

	}

}*/


Mesh::~Mesh()
{
}


