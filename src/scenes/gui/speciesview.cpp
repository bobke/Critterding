#include "speciesview.h"

Speciesview::Speciesview()
{
	genotypes = Genotypes::Instance();
	colormode = Settings::Instance()->getCVarPtr("colormode");

	v_width = 200;
	v_height = 300;
	
	active = false;
	isMovable = true;

	titlebar = 25;
	v_space = -10 + titlebar;
	rowspacer = 4;
	qwidth = 25;
	qheight = 10;
	
	titlePos = "#";
	titleColor = "Color";
	titleNum = "Population";
	titleAd = "Adam Distance";
	titleNeurons = "Neurons";
	titleSynapses = "Synapses";
	titleBodyparts = "Bodyparts";
	
	titlePosW = textprinter->getWidth( titlePos );
	titleColorW = textprinter->getWidth( titleColor );
	titleNumW = textprinter->getWidth( titleNum );
	titleAdW = textprinter->getWidth( titleAd );
	titleNeuronsW = textprinter->getWidth( titleNeurons );
	titleSynapsesW = textprinter->getWidth( titleSynapses );
	titleBodypartsW = textprinter->getWidth( titleBodyparts );
}

void Speciesview::draw()
{
	if (active)
	{
		unsigned int highestCount = 0;
		unsigned int highestAD = 0;
		unsigned int highestNeurons = 0;
		unsigned int highestSynapses = 0;
		unsigned int highestBodyparts = 0;

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
			if ( genotypes->list[i]->brainzArch->ArchNeurons.size() > highestNeurons )
				highestNeurons = genotypes->list[i]->brainzArch->ArchNeurons.size();
			// calc total syns
			unsigned int totalSyns = 0;
			for ( unsigned int j = 0; j < genotypes->list[i]->brainzArch->ArchNeurons.size(); j++ )
				totalSyns += genotypes->list[i]->brainzArch->ArchNeurons[j].ArchSynapses.size();
			if ( totalSyns > highestSynapses )
				highestSynapses = totalSyns;
			if ( genotypes->list[i]->bodyArch->archBodyparts.size() > highestNeurons )
				highestNeurons = genotypes->list[i]->bodyArch->archBodyparts.size();
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
	
		int titleNumWH = textprinter->getWidth( highestCount );
		int titleColorWH = qwidth;
		int titlePosWH = textprinter->getWidth( genotypes->list.size() );
		int titleAdWH = textprinter->getWidth( highestAD );
		int titleNeuronsWH = textprinter->getWidth( highestNeurons );
		int titleSynapsesWH = textprinter->getWidth( highestSynapses );
		int titleBodypartsWH = textprinter->getWidth( highestBodyparts );
		
		int colw1 = titlePosW;
		if ( colw1 < titlePosWH ) colw1 = titlePosWH;
		int colw2 = titleColorW;
		if ( colw2 < titleColorWH ) colw2 = titleColorWH;
		int colw3 = titleNumW;
		if ( colw3 < titleNumWH ) colw3 = titleNumWH;
		int colw4 = titleAdW;
		if ( colw4 < titleAdWH ) colw4 = titleAdWH;
		int colw5 = titleNeuronsW;
		if ( colw5 < titleNeuronsWH ) colw5 = titleNeuronsWH;
		int colw6 = titleSynapsesW;
		if ( colw6 < titleSynapsesWH ) colw6 = titleSynapsesWH;
		int colw7 = titleBodypartsW;
		if ( colw7 < titleBodypartsWH ) colw7 = titleBodypartsWH;

		int colspacer = 15;
		int col1 = colspacer;
		int col2 = col1+colspacer + colw1;
		int col3 = col2+colspacer + colw2;
		int col4 = col3+colspacer + colw3;
		int col5 = col4+colspacer + colw4;
		int col6 = col5+colspacer + colw5;
		int col7 = col6+colspacer + colw6;
		int col8 = col7+colspacer + colw7;

		v_space = -10 + titlebar;

		v_height = (genotypes->list.size() * (qheight+rowspacer)) + rowspacer + titlebar;
		v_width = col8;
		drawBackground();
		drawBorders();
		drawChildren();

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		textprinter->print( absPosition.x+col1, absPosition.y+19, titlePos );
		textprinter->print( absPosition.x+col2, absPosition.y+19, titleColor );
		textprinter->print( absPosition.x+col3, absPosition.y+19, titleNum );
		textprinter->print( absPosition.x+col4, absPosition.y+19, titleAd );
		textprinter->print( absPosition.x+col5, absPosition.y+19, titleNeurons );
		textprinter->print( absPosition.x+col6, absPosition.y+19, titleSynapses );
		textprinter->print( absPosition.x+col7, absPosition.y+19, titleBodyparts );
		
		
		for ( unsigned int i=0; i < genotypes->list.size(); i++  )
		{
			v_space += qheight + rowspacer; 

			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			textprinter->print( absPosition.x+col1, absPosition.y+v_space+9, i+1 );
			textprinter->print( absPosition.x+col3, absPosition.y+v_space+9, genotypes->list[indices[i]]->count );
			textprinter->print( absPosition.x+col4, absPosition.y+v_space+9, genotypes->list[indices[i]]->adamdist );
			textprinter->print( absPosition.x+col5, absPosition.y+v_space+9, genotypes->list[i]->brainzArch->ArchNeurons.size() );
			// total syns
			unsigned int totalSyns = 0;
			for ( unsigned int j = 0; j < genotypes->list[i]->brainzArch->ArchNeurons.size(); j++ )
				totalSyns += genotypes->list[i]->brainzArch->ArchNeurons[j].ArchSynapses.size();
			textprinter->print( absPosition.x+col6, absPosition.y+v_space+9, totalSyns );
			textprinter->print( absPosition.x+col7, absPosition.y+v_space+9, genotypes->list[i]->bodyArch->archBodyparts.size() );

			if ( *colormode )
				glColor4f(genotypes->list[indices[i]]->speciescolor.r, genotypes->list[indices[i]]->speciescolor.g, genotypes->list[indices[i]]->speciescolor.b, genotypes->list[indices[i]]->speciescolor.a);
			else
				glColor4f(genotypes->list[indices[i]]->bodyArch->color.r, genotypes->list[indices[i]]->bodyArch->color.g, genotypes->list[indices[i]]->bodyArch->color.b, genotypes->list[indices[i]]->bodyArch->color.a);

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
