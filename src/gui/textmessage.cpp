#include "textmessage.h"

Textmessage* Textmessage::Instance () 
{
	static Textmessage t;
	return &t; // _instance isn't needed in this case
}

Textmessage::Textmessage()
{
	maxMessages = 5;
	msgLifetime = 3.0f;
	longestLength = 0;

	vpadding = 10.0f;
	hpadding = 10.0f;
}

void Textmessage::add(const stringstream& streamptr)
{
	msg *Msg = new msg;
	Msg->str = streamptr.str();
	Msg->appeartime = Timer::Instance()->lasttime;
	messages.push_back(Msg);

	//getLongestMsg();
	FTPoint bbox = Textprinter::Instance()->getBBox( messages[messages.size()-1]->str );
	if ( bbox.X() > longestLength )
		longestLength = bbox.X();

	// to prevent overfilling:
	deleteExpiredMsg();
}

void Textmessage::getLongestMsg()
{
	longestLength = 0;
	for ( unsigned int i = 0; i < messages.size(); i++ )
	{
		FTPoint bbox = Textprinter::Instance()->getBBox(messages[i]->str);
		if ( bbox.X() > longestLength )
			longestLength = bbox.X();
	}
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
			delete messages[0];
			messages.erase(messages.begin()+0);

			getLongestMsg();
		}
	}
}

void Textmessage::draw()
{
	deleteExpiredMsg();

	if ( !messages.empty() )
	{
		FTPoint bbox = Textprinter::Instance()->getBBox(messages[0]->str);

		position.x = 10;
		v_width = longestLength + ( hpadding*2 );

		position.y = 50;
		v_height = (15 * (messages.size()-1)) + bbox.Y() + ( vpadding*2 );
		
	// draw background box and border
		drawBackground();
		drawBorders();

	// render text
		glColor3f(1.0f, 1.0f, 1.0f);
		for ( unsigned int i = 0; i < messages.size(); i++ )
			Textprinter::Instance()->print(position.x + hpadding, position.y + bbox.Y() + (i*15.0f) + vpadding, messages[i]->str);
	}
}
