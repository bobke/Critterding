#include "textverbosemessage.h"

Textverbosemessage* Textverbosemessage::Instance () 
{
	static Textverbosemessage t;
	return &t; // _instance isn't needed in this case
}

Textverbosemessage::Textverbosemessage()
{
	position.x = 10;
	position.y = 50;
	
	v_width = 500;
	v_height = 86;

	active = false;
	isMovable = true;
	
	maxMessages = 5;
	msgLifetime = 0.0f;
	longestLength = 0;
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

void Textverbosemessage::draw()
{
	if ( active )
	{
		deleteExpiredMsg();

		drawBackground();
		drawBorders();

		glColor3f(0.7f, 0.7f, 0.7f);
		glBegin(GL_LINES);
			glVertex2f(position.x+((float)v_width/4)*3, position.y);
			glVertex2f(position.x+((float)v_width/4)*3, position.y+v_height);
		glEnd();

		if ( !births.empty() )
		{
		// render text
// 			glEnable(GL_TEXTURE_2D);

			glColor3f(1.0f, 1.0f, 1.0f);

			for ( unsigned int i = 0; i < births.size(); i++ )
				Textprinter::Instance()->print(position.x+10, position.y + 13 + 1 + (i*13), births[i]->str);

// 			glDisable(GL_TEXTURE_2D);
		}

		if ( !deaths.empty() )
		{
		// render text
// 			glEnable(GL_TEXTURE_2D);

			glColor3f(1.0f, 1.0f, 1.0f);

			for ( unsigned int i = 0; i < deaths.size(); i++ )
				Textprinter::Instance()->print(position.x+((float)v_width/4)*3 + 10, (position.y + 13) + 1 + (i*13), deaths[i]->str);

// 			glDisable(GL_TEXTURE_2D);
		}
	}
}

void Textverbosemessage::swap()
{
	active = !active;
}
