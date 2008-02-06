#ifndef MESH_H
#define MESH_H
#include "GL/gl.h"
#include "vector3f.h"
#include <cmath>
#include <iostream>


struct Vertex {

	Vector3f position;
	int incidents;			//	Amount of incidents; this vertex occurs in the faces
	int occursinTriangles[4];	//	List of triangle-indices where vertex appears in
	Vector3f normal;
};

struct Triangle {

	Vertex *verts[3];
	Vector3f normal;
};

class Mesh {

/*	void calcFaceNormals();*/
	void createIndexVertices();
// 	void calcVertexNormals();

	public:
		Mesh();
		~Mesh();
	
		Vector3f position;
	
		static const unsigned int nVertices=6;
		static const unsigned int nTriangles=8;
	
		struct Vertex vertices[nVertices];
		struct Triangle triangles[nTriangles];
	
		float size;
		void create();
		void draw();
};

#endif
