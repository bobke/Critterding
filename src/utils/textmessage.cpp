#include "textmessage.h"

Textmessage* Textmessage::Instance () 
{
	static Textmessage t;
	return &t; // _instance isn't needed in this case
}

Textmessage::Textmessage()
{
	maxMessages = 5;
	msgLifetime = 5.0f;
	longestLength = 0;

	vpadding = 5.0f;
	hpadding = 5.0f;
}

void Textmessage::add(stringstream& streamptr)
{
	msg *Msg = new msg;
	Msg->str = streamptr.str();
	Msg->appeartime = Timer::Instance()->lasttime;
	messages.push_back(Msg);

	//getLongestMsg();
	if ( messages[messages.size()-1]->str.length() > longestLength )
		longestLength = messages[messages.size()-1]->str.length();

	// to prevent overfilling:
	deleteExpiredMsg();
}

void Textmessage::getLongestMsg()
{
	longestLength = 0;
	for ( unsigned int i = 0; i < messages.size(); i++ )
		if ( messages[i]->str.length() > longestLength )
			longestLength = messages[i]->str.length();
}

void Textmessage::deleteExpiredMsg()
{
	if ( !messages.empty() )
	{
		if (
			messages.size() > maxMessages
			|| ( msgLifetime > 0.0f && Timer::Instance()->timediff( Timer::Instance()->lasttime, messages[0]->appeartime ) > msgLifetime )
		)
		{
			// backup it's length
			unsigned int length = messages[0]->str.length();

			delete messages[0];
			messages.erase(messages.begin()+0);

			if ( length == longestLength )
				getLongestMsg();
		}
	}
}

void Textmessage::draw()
{
	deleteExpiredMsg();

	if ( !messages.empty() )
	{
		float xstart = 5.0f;
		float xstop = 5.0f + (2.0f*hpadding) + (7.0f * longestLength);

		float ystart = 50.0f;
		float ystop = 50.0f + (2.0f*hpadding) + (15.0f * messages.size());

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
			glVertex2f(xstart, ystop);
			glVertex2f(xstart, ystart);

			glVertex2f(xstart, ystart);
			glVertex2f(xstop, ystart);

			glVertex2f(xstop, ystart);
			glVertex2f(xstop, ystop);

			glVertex2f(xstop, ystop);
			glVertex2f(xstart, ystop);
		glEnd();

	// render text
		glEnable(GL_TEXTURE_2D);

		glColor3f(1.0, 1.0, 1.0);
		for ( unsigned int i = 0; i < messages.size(); i++ )
		{
			Textprinter::Instance()->print(7.0f + hpadding, 60.0f + vpadding + (i*15.0f), &messages[i]->str);
		}

		glDisable(GL_TEXTURE_2D);
	}
}
