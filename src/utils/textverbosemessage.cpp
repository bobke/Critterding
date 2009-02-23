#include "textverbosemessage.h"

Textverbosemessage* Textverbosemessage::Instance () 
{
	static Textverbosemessage t;
	return &t; // _instance isn't needed in this case
}

Textverbosemessage::Textverbosemessage()
{
	maxMessages = 5;
	msgLifetime = 0.0f;
	longestLength = 0;

	vpadding = 10.0f;
	hpadding = 10.0f;
}

void Textverbosemessage::addBirth(stringstream& streamptr)
{
	vmsg *Msg = new vmsg;
	Msg->str = streamptr.str();
	Msg->appeartime = Timer::Instance()->lasttime;
	births.push_back(Msg);

	// to prevent overfilling:
	deleteExpiredMsg();
}

void Textverbosemessage::addDeath(stringstream& streamptr)
{
	vmsg *Msg = new vmsg;
	Msg->str = streamptr.str();
	Msg->appeartime = Timer::Instance()->lasttime;
	deaths.push_back(Msg);

	// to prevent overfilling:
	deleteExpiredMsg();
}

void Textverbosemessage::deleteExpiredMsg()
{
	if ( !births.empty() )
	{
		if (
			births.size() > maxMessages
			|| ( msgLifetime > 0.0f && Timer::Instance()->timediff( Timer::Instance()->lasttime, births[0]->appeartime ) > msgLifetime )
		)
		{
			delete births[0];
			births.erase(births.begin()+0);
		}
	}
	if ( !deaths.empty() )
	{
		if (
			deaths.size() > maxMessages
			|| ( msgLifetime > 0.0f && Timer::Instance()->timediff( Timer::Instance()->lasttime, deaths[0]->appeartime ) > msgLifetime )
		)
		{
			delete deaths[0];
			deaths.erase(deaths.begin()+0);
		}
	}
}

void Textverbosemessage::draw( unsigned int posX )
{
	deleteExpiredMsg();

	FTPoint bbox = Textprinter::Instance()->getBBox("a");

	float xstart = 0.0f;
	float xstop = *Settings::Instance()->winWidth;

	float ystart = posX;
	float ystop = posX + (15.0f * (maxMessages-1)) + bbox.Y() + ( vpadding*2.0f );

	// draw background box and border
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(0.05f, 0.05f, 0.05f, 0.9f);
	glBegin(GL_QUADS);
		glVertex2f(xstart, ystop);
		glVertex2f(xstart, ystart);
		glVertex2f(xstop, ystart);
		glVertex2f(xstop, ystop);
	glEnd();
	glDisable(GL_BLEND);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex2f(xstop, ystop);
		glVertex2f(xstart, ystop);

		glVertex2f((*Settings::Instance()->winWidth/4)*3, ystart);
		glVertex2f((*Settings::Instance()->winWidth/4)*3, ystop);
	glEnd();

	if ( !births.empty() )
	{
	// render text
		glEnable(GL_TEXTURE_2D);

		glColor3f(1.0f, 1.0f, 1.0f);

		for ( unsigned int i = 0; i < births.size(); i++ )
		{
			Textprinter::Instance()->print(xstart + hpadding, ystart + bbox.Y() + (i*15.0f) + vpadding, births[i]->str);
		}

		glDisable(GL_TEXTURE_2D);
	}

	if ( !deaths.empty() )
	{
	// render text
		glEnable(GL_TEXTURE_2D);

		glColor3f(1.0f, 1.0f, 1.0f);

		for ( unsigned int i = 0; i < deaths.size(); i++ )
		{
			Textprinter::Instance()->print((*Settings::Instance()->winWidth/4)*3 + 20, ystart + bbox.Y() + (i*15.0f) + vpadding, deaths[i]->str);
		}

		glDisable(GL_TEXTURE_2D);
	}
}
