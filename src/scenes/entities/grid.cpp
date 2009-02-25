#include "grid.h"

Grid::Grid()
{
// 	gridsize	= 0;
// 	gridsizeX	= 0;
// 	gridsizeY	= 0;
	resolution	= 1.0f;
//	resize(gridsize);

	color[0]	= 0.0f;
	color[1]	= 0.0f;
	color[2]	= 1.0f;
	color[3]	= 0.0f;
}

void Grid::draw()
{
	glColor4f( color[0], color[1], color[2], color[3] );
	glPushMatrix();
		glBegin(GL_LINES);
			for( unsigned int i=0; i < vertices.size(); i++)
			{
				//cout << vertices[i].x() << " " << vertices[i].y() << " " << vertices[i].z() << endl;
				glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
			}
		glEnd();
	glPopMatrix();
}

void Grid::resize(unsigned int X, unsigned int Y)
{
	gridsizeX = X;
	gridsizeY = Y;

	int totalstepsX	= int(gridsizeX / resolution);
	int totalstepsY	= int(gridsizeY / resolution);

	vertices.clear();
	for ( int i = 0; i <= totalstepsX; i++ )
	{
		// horizontal lines
			vertices.push_back( Vector3f( (float)(resolution * i), 0.0f, 0.0f ) );
			vertices.push_back( Vector3f( (float)(resolution * i), 0.0f, gridsizeY ) );

/*		// vertical lines
			vertices.push_back( Vector3f(0.0f, 0.0f, resolution * i) );
			vertices.push_back( Vector3f(gridsize, 0.0f, resolution * i) );*/
	}

	for ( int i = 0; i <= totalstepsY; i++ )
	{
// 		// horizontal lines
// 			vertices.push_back( Vector3f( (float)(resolution * i), 0.0f, 0.0f ) );
// 			vertices.push_back( Vector3f( (float)(resolution * i), 0.0f, gridsize ) );

		// vertical lines
			vertices.push_back( Vector3f(0.0f, 0.0f, resolution * i) );
			vertices.push_back( Vector3f(gridsizeX, 0.0f, resolution * i) );
	}
}

Grid::~Grid()
{
}


