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

	active = false;
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

void Textverbosemessage::draw( unsigned int posY )
{
	if ( active )
	{
		deleteExpiredMsg();

		unsigned int xstart = 0.0f;
		unsigned int xstop = *Settings::Instance()->winWidth;

		unsigned int ystart = posY + 13;
		unsigned int ystop = posY + (13 * (maxMessages) + 10);

		// draw background box and border
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glColor4f(0.05f, 0.05f, 0.05f, 0.9f);
		glBegin(GL_QUADS);
			glVertex2f(xstart, ystop);
			glVertex2f(xstart, posY);
			glVertex2f(xstop, posY);
			glVertex2f(xstop, ystop);
		glEnd();
		glDisable(GL_BLEND);

		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
			glVertex2f(xstop, ystop);
			glVertex2f(xstart, ystop);

			glVertex2f((*Settings::Instance()->winWidth/4)*3, posY);
			glVertex2f((*Settings::Instance()->winWidth/4)*3, ystop);
		glEnd();

		if ( !births.empty() )
		{
		// render text
			glEnable(GL_TEXTURE_2D);

			glColor3f(1.0f, 1.0f, 1.0f);

			for ( unsigned int i = 0; i < births.size(); i++ )
			{
				Textprinter::Instance()->print(10.0f, ystart + 1 + (i*13), births[i]->str);
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
				Textprinter::Instance()->print(((float)*Settings::Instance()->winWidth/4)*3 + 10, ystart + 1 + (i*13), deaths[i]->str);
			}

			glDisable(GL_TEXTURE_2D);
		}
	}
}

void Textverbosemessage::swap()
{
	active = !active;
}
