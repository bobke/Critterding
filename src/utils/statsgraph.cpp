#include "statsgraph.h"

Statsgraph::Statsgraph()
{
	active = true;

	statsBuffer = Statsbuffer::Instance();
	settings = Settings::Instance();

	barheight = 100;
}

void Statsgraph::draw( unsigned int posY )
{
	if (active)
	{
		boxwidth = *settings->winWidth;
		boxheight = 100;

		unsigned int x1 = 0;
		unsigned int x2 = x1 + boxwidth;
		unsigned int y1 = posY;
		unsigned int y2 = y1 + barheight;

	// draw background box and border
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glColor4f(0.05f, 0.05f, 0.05f, 0.9f);
		glBegin(GL_QUADS);
			glVertex2f(x1, y2);
			glVertex2f(x1, y1);
			glVertex2f(x2, y1);
			glVertex2f(x2, y2);
		glEnd();
		glDisable(GL_BLEND);

		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
// 			glVertex2f(x1, y2);
// 			glVertex2f(x1, y1);

			glVertex2f(x1, y1);
			glVertex2f(x2, y1);

// 			glVertex2f(x2, y1);
// 			glVertex2f(x2, y2);

			glVertex2f(x2, y2);
			glVertex2f(x1, y2);
		glEnd();

		unsigned int number = statsBuffer->snapshots.size();
		
		if ( number > 0 )
		{
			unsigned int start = 0;
			if ( number > boxwidth )
				start = number - boxwidth;
			
		// find the highest value in the stats vector
			unsigned int highest = 0;
			for ( unsigned int i=start; i < number; i++ )
			{
				unsigned int sum = statsBuffer->snapshots[i].food + statsBuffer->snapshots[i].critters;
				if ( sum > highest )
					highest = sum;
			}
// 			cerr << highest << endl;

			if ( highest > 0 )
			{

				// so,  highest ~ boxheight
				// and, number ~ boxwidth
			
			// draw the number of critters graph

				glColor3f(0.0f, 1.0f, 0.0f);
				glBegin(GL_POINTS);
					for ( unsigned int i=start; i < number; i++ )
					{
						glVertex2f( x1+i-start, y2-((float)boxheight/highest)*statsBuffer->snapshots[i].food );
					}
				glEnd();
				glColor3f(1.0f, 0.0f, 0.0f);
				glBegin(GL_POINTS);
					for ( unsigned int i=start; i < number; i++ )
					{
						glVertex2f( x1+i-start, y2-((float)boxheight/highest)*statsBuffer->snapshots[i].critters );
					}
				glEnd();
			}
		}
		
	}
}

void Statsgraph::swap()
{
	active = !active;
}

unsigned int Statsgraph::height()
{
	if ( active )
		return barheight;
	else
		return 0;
}

Statsgraph::~Statsgraph()
{
}
