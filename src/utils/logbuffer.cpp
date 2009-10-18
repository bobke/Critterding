#include "logbuffer.h"

Logbuffer* Logbuffer::Instance () 
{
	static Logbuffer t;
	return &t; // _instance isn't needed in this case
}

Logbuffer::Logbuffer()
{
	maxMessages = 5;
	msgLifetime = 3.0f;
}

void Logbuffer::add(const stringstream& streamptr)
{
	msg *Msg = new msg;
	Msg->str = streamptr.str();
	Msg->appeartime = Timer::Instance()->lasttime;
	messages.push_back(Msg);

	// to prevent overfilling:
	deleteExpiredMsg();
}

void Logbuffer::deleteExpiredMsg()
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
		}
	}
}
