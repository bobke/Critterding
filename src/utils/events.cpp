#include "events.h"

Events* Events::Instance () 
{
	static Events t;
	return &t;
}

Events::Events()
{
}

void Events::registerEvent(SDLKey key, const string& name, float responsetime, float minfresponsetime, float fresponseinterval)
{
	// create a new event and a pointer to it
	events.push_back(event());
	event* e = &events[events.size() - 1];

	// set up default values of event
	e->active = false;
	e->name = name;
	e->bindkey = key;
	e->responsetime = responsetime;
	e->fresponsetime = responsetime;
	e->minfresponsetime = minfresponsetime;
	e->fresponseinterval = fresponseinterval;
	e->elapsed = responsetime;
}

void Events::activateEvent(const long unsigned int key)
{
	bool notfound = true;
	for ( unsigned int i=0; notfound && i < events.size(); i++ )
	{
		if ( events[i].bindkey == key )
		{
// 			cerr << "activating " << events[i].name << endl;
			events[i].active = true;
			notfound = false;
			events[i].elapsed = events[i].responsetime;
			events[i].fresponsetime = events[i].responsetime;
		}
	}
}

void Events::deactivateEvent(const long unsigned int key)
{
	bool notfound = true;
	for ( unsigned int i=0; notfound && i < events.size(); i++ )
	{
		if ( events[i].bindkey == key )
		{
// 			cerr << "deactivating " << events[i].name << endl;
			events[i].active = false;
			notfound = false;
		}
	}
}

bool Events::isActive(const string& name)
{
	bool notfound = true;
	for ( unsigned int i=0; notfound && i < events.size(); i++ )
	{
		if ( events[i].name == name )
		{
			event* e = &events[i];
			notfound = false;
			if ( e->active )
			{
				if ( e->responsetime > 0.0f )
				{
					e->elapsed += Timer::Instance()->elapsed;
					if ( e->elapsed >= e->fresponsetime )
					{
						e->fresponsetime -= e->fresponseinterval;
						if ( e->fresponsetime < e->minfresponsetime )
							e->fresponsetime = 0.01f;
						e->elapsed = 0.0f;
						return true;
					}
				}
			}
		}
	}
	return false;
}

