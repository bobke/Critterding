#include "speciesview.h"

Speciesview::Speciesview()
{
	genotypes = Genotypes::Instance();

	v_width = 200;
	v_height = 300;
	
	active = false;
	isMovable = true;
}

void Speciesview::draw()
{
	if (active)
	{
		unsigned int highestCount = 0;
		unsigned int highestAD = 0;
	
	// initialize sort indices
	// at the same time find the highest Counts for all columns
		vector<int> indices ( genotypes->list.size(), 0 );
		for ( unsigned int i = 0; i < genotypes->list.size(); i++ )
		{
			indices[i] = i;
			
			if ( genotypes->list[i]->count > highestCount )
				highestCount = genotypes->list[i]->count;
			if ( genotypes->list[i]->adamdist > highestAD )
				highestAD = genotypes->list[i]->adamdist;
		}

	// sort results
		for ( int i = genotypes->list.size(); i>0; i--  )
			for ( int j = 0; j < i-1; j++  )
				if ( genotypes->list[indices[j]]->count < genotypes->list[indices[j+1]]->count )
				{
					unsigned keepI	= indices[j];
					indices[j]	= indices[j+1];
					indices[j+1]	= keepI;
				}
	
		int titlebar = 25;
		int v_space = -10 + titlebar;
		int rowspacer = 4;
		int qwidth = 25;
		int qheight = 10;
		
		int colspacer = 10;
		int col1 = colspacer;
		int col2 = col1+colspacer + textprinter->getWidth( genotypes->list.size() );
		int col3 = col2+colspacer + qwidth;
		int col4 = col3+colspacer + textprinter->getWidth( highestCount );
		int col5 = col4+colspacer + textprinter->getWidth( highestAD );

		v_height = (genotypes->list.size() * (qheight+rowspacer)) + rowspacer + titlebar;
		v_width = col5;
		drawBackground();
		drawBorders();
		drawChildren();

		for ( unsigned int i=0; i < genotypes->list.size(); i++  )
		{
			v_space += qheight + rowspacer; 

			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			textprinter->print( absPosition.x+col1, absPosition.y+v_space+9, i+1 );
			textprinter->print( absPosition.x+col3, absPosition.y+v_space+9, genotypes->list[indices[i]]->count );
			textprinter->print( absPosition.x+col4, absPosition.y+v_space+9, genotypes->list[indices[i]]->adamdist );

			glColor4f(genotypes->list[indices[i]]->speciescolor.r, genotypes->list[indices[i]]->speciescolor.g, genotypes->list[indices[i]]->speciescolor.b, genotypes->list[indices[i]]->speciescolor.a);
			glBegin(GL_QUADS);
				glVertex2f(absPosition.x+col2,         absPosition.y+v_space+qheight);
				glVertex2f(absPosition.x+col2,         absPosition.y+v_space);
				glVertex2f(absPosition.x+col2+qwidth,  absPosition.y+v_space);
				glVertex2f(absPosition.x+col2+qwidth,  absPosition.y+v_space+qheight);
			glEnd();
			
			glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
			glBegin(GL_LINES);
				glVertex2f(absPosition.x+col2,         absPosition.y+v_space+qheight);
				glVertex2f(absPosition.x+col2,         absPosition.y+v_space);

				glVertex2f(absPosition.x+col2,         absPosition.y+v_space);
				glVertex2f(absPosition.x+col2+qwidth,  absPosition.y+v_space);

				glVertex2f(absPosition.x+col2+qwidth,  absPosition.y+v_space);
				glVertex2f(absPosition.x+col2+qwidth,  absPosition.y+v_space+qheight);

				glVertex2f(absPosition.x+col2+qwidth,  absPosition.y+v_space+qheight);
				glVertex2f(absPosition.x+col2,         absPosition.y+v_space+qheight);
			glEnd();
		}

	}
}

Speciesview::~Speciesview()
{
}
