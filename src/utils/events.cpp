#include "events.h"

Events* Events::Instance () 
{
	static Events t;
	return &t;
}

Events::Events()
{
}

sharedTimer* Events::registerSharedtimer(unsigned int responsetime)
{
	// create a new event and a pointer to it
	sharedtimers.push_back(sharedTimer());
	sharedTimer* t = &sharedtimers[sharedtimers.size() - 1];

	t->responsetime = responsetime;
	return t;
}

void Events::registerEvent(SDLKey key, const string& name, sharedTimer* stimer)
{
	// create a new event and a pointer to it
	events.push_back(event());
	event* e = &events[events.size() - 1];

	// set up default values of event
	e->active = false;
	e->name = name;
	e->bindkey = key;
	
	e->timerisshared = true;
	e->stimer = stimer;
}

void Events::registerEvent(SDLKey key, const string& name, unsigned int responsetime, unsigned int minfresponsetime, unsigned int fresponseinterval)
{
	// create a new event and a pointer to it
	events.push_back(event());
	event* e = &events[events.size() - 1];

	// set up default values of event
	e->active = false;
	e->name = name;
	e->bindkey = key;
	e->responsetime = responsetime;
// 	e->fresponsetime = responsetime;
	e->minfresponsetime = minfresponsetime;
	e->fresponseinterval = fresponseinterval;
// 	e->elapsed = responsetime;
	e->timerisshared = false;
}

void Events::activateEvent(const long unsigned int key)
{
	for ( unsigned int i=0; i < events.size(); i++ )
	{
		if ( events[i].bindkey == key )
		{
			events[i].active = true;
			events[i].elapsed = events[i].responsetime;
			events[i].fresponsetime = events[i].responsetime;
// 			cerr << "activated " << events[i].name << " rt: " << events[i].elapsed << endl;
			return;
		}
	}
}

void Events::deactivateEvent(const long unsigned int key)
{
	for ( unsigned int i=0; i < events.size(); i++ )
	{
		if ( events[i].bindkey == key )
		{
// 			cerr << "deactivating " << events[i].name << endl;
			events[i].active = false;
			return;
		}
	}
}

void Events::processSharedTimers()
{
	for ( unsigned int i=0; i < sharedtimers.size(); i++ )
	{
		sharedTimer* t = &sharedtimers[i];
		t->elapsed += Timer::Instance()->elapsed;
		if ( t->elapsed >= t->responsetime )
		{
			t->elapsed = 0;
			t->active = true;
		}
		else
			t->active = false;
	}
}

bool Events::isActive(const string& name)
{
	bool notfound = true;
	for ( unsigned int i=0; notfound && i < events.size(); i++ )
	{
		if ( events[i].name == name )
		{
			notfound = false;

			event* e = &events[i];
			
			if ( e->active )
			{
				// event uses a shared timer
					if ( e->timerisshared )
					{
						if ( e->stimer->active )
							return e->active;
					}
				// event does not use a timer
					else if ( e->responsetime == 0 )
						return e->active;

				// event has it's own timer
					e->elapsed += Timer::Instance()->elapsed;
					if ( (int)e->elapsed >= e->fresponsetime )
					{
						if ( e->responsetime > e->minfresponsetime )
						{
							e->fresponsetime -= e->fresponseinterval;
							if ( e->fresponsetime < (int)e->minfresponsetime )
								e->fresponsetime = e->minfresponsetime;
						}
						e->elapsed = 0;
						return true;
					}
			}
		}
	}
	return false;
}

