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

	isMovable = true;
	
	vpadding = 10;
	hpadding = 10;

	position.x = 10;
	position.y = 50;

// 	v_width = 200 + ( hpadding*2 );
// 	v_height = (15 * (messages.size()-1)) + 20 + ( vpadding*2 );
}

void Textmessage::add(const stringstream& streamptr)
{
	msg *Msg = new msg;
	Msg->str = streamptr.str();
	Msg->appeartime = Timer::Instance()->lasttime;
	messages.push_back(Msg);

	//getLongestMsg();
	int width = Textprinter::Instance()->getWidth( messages[messages.size()-1]->str );
	if ( width > longestLength )
		longestLength = width;

	// to prevent overfilling:
	deleteExpiredMsg();
}

void Textmessage::getLongestMsg()
{
	longestLength = 0;
	for ( unsigned int i = 0; i < messages.size(); i++ )
	{
		int width = Textprinter::Instance()->getWidth(messages[i]->str);
		if ( width > longestLength )
			longestLength = width;
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
		active = true;
		
		unsigned int height = 5;

		v_width = longestLength + ( hpadding*2 );
		v_height = (15 * (messages.size()-1)) + height + ( vpadding*2 );
		
	// draw background box and border
// 		updateAbsPosition();
		drawBackground();
		drawBorders();

	// render text
		glColor3f(1.0f, 1.0f, 1.0f);
		for ( unsigned int i = 0; i < messages.size(); i++ )
			Textprinter::Instance()->print(position.x + hpadding, position.y + height + (i*15.0f) + vpadding, messages[i]->str);
	}
	else
		active = false;
}
