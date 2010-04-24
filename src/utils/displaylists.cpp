#include "displaylists.h"

// PFNGLBINDBUFFERARBPROC glBindBufferARB = NULL;
// PFNGLGENBUFFERSARBPROC glGenBuffersARB = NULL;
// PFNGLBUFFERDATAARBPROC glBufferDataARB = NULL;

// 	GLfloat vertices[] = 
// 	{
// 		1.0f, 1.0f, 1.0f,   //V2
// 		1.0f,-1.0f, 1.0f,   //V1
// 		1.0f,-1.0f,-1.0f,   //V3
// 		1.0f, 1.0f,-1.0f,   //V4
// 		//Quad 2
// 		1.0f, 1.0f,-1.0f,   //V4
// 		1.0f,-1.0f,-1.0f,   //V3
// 		-1.0f,-1.0f,-1.0f,   //V5
// 		-1.0f, 1.0f,-1.0f,   //V6
// 		//Quad 3
// 		-1.0f, 1.0f,-1.0f,   //V6
// 		-1.0f,-1.0f,-1.0f,   //V5
// 		-1.0f,-1.0f, 1.0f,   //V7
// 		-1.0f, 1.0f, 1.0f,   //V8
// 		//Quad 4
// 		-1.0f, 1.0f, 1.0f,   //V8
// 		-1.0f,-1.0f, 1.0f,   //V7
// 		 1.0f,-1.0f, 1.0f,   //V1
// 		 1.0f, 1.0f, 1.0f,   //V2
// 		//Quad 5
// 		-1.0f, 1.0f,-1.0f,   //V6
// 		-1.0f, 1.0f, 1.0f,   //V8
// 		 1.0f, 1.0f, 1.0f,   //V2
// 		 1.0f, 1.0f,-1.0f,   //V4
// 		//Quad 6
// 		 1.0f,-1.0f,-1.0f,   //V4
// 		 1.0f,-1.0f, 1.0f,   //V2
// 		-1.0f,-1.0f, 1.0f,   //V8
// 		-1.0f,-1.0f,-1.0f   //V6
// 	};
// 
// 	GLfloat normals[] = 
// 	{
// 		 1.0f, 0.0f, 0.0f,
// 		 0.0f, 0.0f,-1.0f,
// 		-1.0f, 0.0f, 0.0f,
// 		 0.0f, 0.0f, 1.0f,
// 		 0.0f, 1.0f, 0.0f,
// 		0.0f, -1.0f, 0.0f
// 	};
// 
// 	GLfloat colors[] = 
// 	{
// 		 1.0f, 0.0f, 0.0f,
// 		 0.0f, 0.0f, 1.0f,
// 		 1.0f, 0.0f, 0.0f,
// 		 0.0f, 0.0f, 1.0f,
// 		 0.0f, 1.0f, 0.0f,
// 		0.0f,  1.0f, 0.0f
// 	};
	
Displaylists* Displaylists::Instance() 
{
	static Displaylists t;
	return &t;
}

GLuint Displaylists::createVBO(const void* data, int dataSize, GLenum target, GLenum usage)
{
        GLuint id = 0;
        
//         glGenBuffersARB(1, &id);
//         glBindBufferARB(target, id);
//         glBufferDataARB(target, dataSize, data, usage);
        
        return id;
}

Displaylists::Displaylists()
{
	generateList();

// 	// vbo stuff
// 	glGenBuffersARB = (PFNGLGENBUFFERSARBPROC)SDL_GL_GetProcAddress("glGenBuffersARB");
// 	glBindBufferARB = (PFNGLBINDBUFFERARBPROC)SDL_GL_GetProcAddress("glBindBufferARB");
// 	glBufferDataARB = (PFNGLBUFFERDATAARBPROC)SDL_GL_GetProcAddress("glBufferDataARB");
// 	glBufferSubDataARB = (PFNGLBUFFERSUBDATAARBPROC)SDL_GL_GetProcAddress("glBufferSubDataARB");
// 
// 	vboId = createVBO(NULL, sizeof(vertices) + sizeof(normals), GL_ARRAY_BUFFER_ARB, GL_STATIC_DRAW_ARB); //  + sizeof(colors)
// 		glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, sizeof(vertices), vertices);
// 		glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices), sizeof(normals), normals);
// // 		glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices) + sizeof(normals), sizeof(colors), colors);
// 
// 	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
//         glEnableClientState(GL_VERTEX_ARRAY);
}

void Displaylists::call(unsigned int index)
{
	glCallList(displayLists+index);

// 	if ( index == 0 )
// 	{
//                 glVertexPointer(3, GL_FLOAT, 0, 0);
//                 glDrawArrays(GL_QUADS, 0, 24);
// 	}
// 	else
// 	{
//                 glEnableClientState(GL_NORMAL_ARRAY);
// 
//                 glNormalPointer(GL_FLOAT, 0, (float*)NULL + (24)); // 
// //                 glNormalPointer(GL_FLOAT, 0, (void*)sizeof(vertices)); // ((float*)NULL + (24))
// 
//                 glVertexPointer(3, GL_FLOAT, 0, 0);
//                 glDrawArrays(GL_QUADS, 0, 24);
//                 glDisableClientState(GL_NORMAL_ARRAY);
// 	}


}

void Displaylists::generateList()
{
// 	cerr << "generating displaylists" << endl;
	glDeleteLists(displayLists, 2);
	displayLists = glGenLists(2);

	// 0 = cube with the bottom missing
	glNewList(displayLists,GL_COMPILE);

		glBegin(GL_QUADS);
			//Quad 1
			glVertex3f( 1.0f, 1.0f, 1.0f);   //V2
			glVertex3f( 1.0f,-1.0f, 1.0f);   //V1
			glVertex3f( 1.0f,-1.0f,-1.0f);   //V3
			glVertex3f( 1.0f, 1.0f,-1.0f);   //V4
			//Quad 2
			glVertex3f( 1.0f, 1.0f,-1.0f);   //V4
			glVertex3f( 1.0f,-1.0f,-1.0f);   //V3
			glVertex3f(-1.0f,-1.0f,-1.0f);   //V5
			glVertex3f(-1.0f, 1.0f,-1.0f);   //V6
			//Quad 3
			glVertex3f(-1.0f, 1.0f,-1.0f);   //V6
			glVertex3f(-1.0f,-1.0f,-1.0f);   //V5
			glVertex3f(-1.0f,-1.0f, 1.0f);   //V7
			glVertex3f(-1.0f, 1.0f, 1.0f);   //V8
			//Quad 4
			glVertex3f(-1.0f, 1.0f, 1.0f);   //V8
			glVertex3f(-1.0f,-1.0f, 1.0f);   //V7
			glVertex3f( 1.0f,-1.0f, 1.0f);   //V1
			glVertex3f( 1.0f, 1.0f, 1.0f);   //V2
			//Quad 5
			glVertex3f(-1.0f, 1.0f,-1.0f);   //V6
			glVertex3f(-1.0f, 1.0f, 1.0f);   //V8
			glVertex3f( 1.0f, 1.0f, 1.0f);   //V2
			glVertex3f( 1.0f, 1.0f,-1.0f);   //V4
			//Quad 6
			glVertex3f( 1.0f,-1.0f,-1.0f);   //V4
			glVertex3f( 1.0f,-1.0f, 1.0f);   //V2
			glVertex3f(-1.0f,-1.0f, 1.0f);   //V8
			glVertex3f(-1.0f,-1.0f,-1.0f);   //V6
		glEnd();

	glEndList();

	// 0 = cube with the bottom missing
	glNewList(displayLists+1,GL_COMPILE);

		glBegin(GL_QUADS);
			//Quad 1
			glNormal3f( 1.0f, 0.0f, 0.0f);
			glVertex3f( 1.0f, 1.0f, 1.0f);   //V2
			glVertex3f( 1.0f,-1.0f, 1.0f);   //V1
			glVertex3f( 1.0f,-1.0f,-1.0f);   //V3
			glVertex3f( 1.0f, 1.0f,-1.0f);   //V4
			//Quad 2
			glNormal3f( 0.0f, 0.0f,-1.0f);
			glVertex3f( 1.0f, 1.0f,-1.0f);   //V4
			glVertex3f( 1.0f,-1.0f,-1.0f);   //V3
			glVertex3f(-1.0f,-1.0f,-1.0f);   //V5
			glVertex3f(-1.0f, 1.0f,-1.0f);   //V6
			//Quad 3
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(-1.0f, 1.0f,-1.0f);   //V6
			glVertex3f(-1.0f,-1.0f,-1.0f);   //V5
			glVertex3f(-1.0f,-1.0f, 1.0f);   //V7
			glVertex3f(-1.0f, 1.0f, 1.0f);   //V8
			//Quad 4
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glVertex3f(-1.0f, 1.0f, 1.0f);   //V8
			glVertex3f(-1.0f,-1.0f, 1.0f);   //V7
			glVertex3f( 1.0f,-1.0f, 1.0f);   //V1
			glVertex3f( 1.0f, 1.0f, 1.0f);   //V2
			//Quad 5
			glNormal3f( 0.0f, 1.0f, 0.0f);
			glVertex3f(-1.0f, 1.0f,-1.0f);   //V6
			glVertex3f(-1.0f, 1.0f, 1.0f);   //V8
			glVertex3f( 1.0f, 1.0f, 1.0f);   //V2
			glVertex3f( 1.0f, 1.0f,-1.0f);   //V4
			//Quad 6
			glNormal3f(0.0f, -1.0f, 0.0f);
			glVertex3f( 1.0f,-1.0f,-1.0f);   //V4
			glVertex3f( 1.0f,-1.0f, 1.0f);   //V2
			glVertex3f(-1.0f,-1.0f, 1.0f);   //V8
			glVertex3f(-1.0f,-1.0f,-1.0f);   //V6
		glEnd();

	glEndList();

/*	// 1 = floor
	glNewList(displayLists+2,GL_COMPILE);

		glColor4f( 0.0f, 0.0f, 1.0f, 0.0f );
		glBegin(GL_QUADS);
			glVertex3f( 0.0f, 0.0f, 0.0f);
			glVertex3f( 0.0f, 0.0f, 1.0f);
			glVertex3f( 1.0f, 0.0f, 1.0f);
			glVertex3f( 1.0f, 0.0f, 0.0f);
		glEnd();

	glEndList();*/
}
