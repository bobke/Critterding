#include "statsgraph.h"

Statsgraph::Statsgraph()
{
	active = false;
	isMovable = true;

	statsBuffer = Statsbuffer::Instance();

	v_width = 300;
	v_height = 100;
	
	position.x = 10;
	position.y = 50;
}

void Statsgraph::draw()
{
	if (active)
	{
		drawBackground();
		drawBorders();

		int number = statsBuffer->snapshots.size();
		
		if ( number > 0 )
		{
			int start = 0;
			if ( number > (int)v_width )
				start = number - v_width;
			
		// find the highest value in the stats vector
			unsigned int highest = 0;
			for ( int i=start; i < number; i++ )
			{
				unsigned int sum = statsBuffer->snapshots[i].food + statsBuffer->snapshots[i].critters;
				if ( sum > highest )
					highest = sum;
			}
// 			cerr << highest << endl;

			if ( highest > 0 )
			{
				// so,  highest ~ v_height
				// and, number ~ boxwidth
				float heightratio = ((float)v_height/highest);
			
			// draw the number of critters graph
				glColor3f(0.0f, 1.0f, 0.0f);
				glBegin(GL_LINES);
					for ( int i=start; i < number-1; i++ )
					{
						glVertex2f( position.x+i-start, position.y+v_height-(heightratio*statsBuffer->snapshots[i].food) );
						glVertex2f( position.x+i+1-start, position.y+v_height-(heightratio*statsBuffer->snapshots[i+1].food) );
					}
// 				glEnd();

				glColor3f(1.0f, 0.0f, 0.0f);
// 				glBegin(GL_LINES);
					for ( int i=start; i < number-1; i++ )
					{
						glVertex2f( position.x+i-start, position.y+v_height-(heightratio*statsBuffer->snapshots[i].critters) );
						glVertex2f( position.x+i+1-start, position.y+v_height-(heightratio*statsBuffer->snapshots[i+1].critters) );
					}
				glEnd();
			}
		}
		
	}
}

Statsgraph::~Statsgraph()
{
}
