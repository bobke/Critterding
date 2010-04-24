#include "events.h"

Events* Events::Instance() 
{
	static Events t;
	return &t;
}

Events::Events()
{
	cmd = Commands::Instance();
}

sharedTimer* Events::registerSharedtimer(unsigned int responsetime)
{
	// create a new event and a pointer to it
	sharedtimers.push_back(sharedTimer());
	sharedTimer* t = &sharedtimers[sharedtimers.size() - 1];

	t->responsetime = responsetime;
	t->elapsed = 0;
	return t;
}

void Events::registerModifierEvent(const long unsigned int key)
{
	// create a new event and a pointer to it
	bool found = false;
	for ( unsigned int i = 0; i < modifierevents.size(); i++ )
		if ( modifierevents[i].bindkey == key )
			found = true;
	
	if ( !found )
	{
		modifierevents.push_back(modifierevent());
		modifierevent* e = &modifierevents[modifierevents.size() - 1];

		// set up default values of event
		e->active = false;
		e->bindkey = key;
	}
}

void Events::registerKeyEvent(const long unsigned int key)
{
	// create a new event and a pointer to it
	bool found = false;
	for ( unsigned int i = 0; i < keyevents.size(); i++ )
		if ( keyevents[i].bindkey == key )
			found = true;
	
	if ( !found )
	{
		keyevents.push_back(keyevent());
		keyevent* e = &keyevents[keyevents.size() - 1];

		// set up default values of event
		e->active = false;
		e->bindkey = key;
	}
}

keyevent* Events::getKeyEventP(const long unsigned int key)
{
	for ( unsigned int i = 0; i < keyevents.size(); i++ )
		if ( keyevents[i].bindkey == key )
			return &keyevents[i];
}

modifierevent* Events::getMKeyEventP(const long unsigned int key)
{
	for ( unsigned int i = 0; i < modifierevents.size(); i++ )
		if ( modifierevents[i].bindkey == key )
			return &modifierevents[i];
}

void Events::registerEvent(const long unsigned int key, const string& name, const cmdsettings& cmd, sharedTimer* stimer)
{
	registerKeyEvent(key);

	// create a new event and a pointer to it
	events.push_back(event());
	event* e = &events[events.size() - 1];

	// set up default values of event
	e->active = false;
	e->name = name;
	e->bindkey = key;
	e->bindmkey = 0;
	e->bindbystring = false;
	e->command = cmd;

	e->timerisshared = true;
	e->stimer = stimer;
}

void Events::registerEvent(const long unsigned int key, const string& name, const cmdsettings& cmd, unsigned int responsetime, unsigned int minfresponsetime, unsigned int fresponseinterval)
{
	registerKeyEvent(key);

	// create a new event and a pointer to it
	events.push_back(event());
	event* e = &events[events.size() - 1];

	// set up default values of event
	e->active = false;
	e->name = name;
	e->bindkey = key;
	e->bindmkey = 0;
	e->bindbystring = false;
	e->command = cmd;

	e->responsetime = responsetime;
	e->minfresponsetime = minfresponsetime;
	e->fresponseinterval = fresponseinterval;

	e->timerisshared = false;
}

void Events::registerEvent(SDLKey mkey, const long unsigned int key, const string& name, const cmdsettings& cmd, unsigned int responsetime, unsigned int minfresponsetime, unsigned int fresponseinterval)
{
	registerModifierEvent(mkey);
	registerKeyEvent(key);
  
	// create a new event and a pointer to it
	events.push_back(event());
	event* e = &events[events.size() - 1];

	// set up default values of event
	e->active = false;
	e->name = name;
	e->bindkey = key;
	e->bindmkey = mkey;
	e->bindbystring = false;
	e->command = cmd;

	e->responsetime = responsetime;
	e->minfresponsetime = minfresponsetime;
	e->fresponseinterval = fresponseinterval;

	e->timerisshared = false;
}

void Events::registerEvent(const string& name, const cmdsettings& cmd, unsigned int responsetime, unsigned int minfresponsetime, unsigned int fresponseinterval)
{
	// create a new event and a pointer to it
	events.push_back(event());
	event* e = &events[events.size() - 1];

	// set up default values of event
	e->active = false;
	e->name = name;
	e->bindstring = name;
	e->bindbystring = true;
	e->command = cmd;

	e->responsetime = responsetime;
	e->minfresponsetime = minfresponsetime;
	e->fresponseinterval = fresponseinterval;

	e->timerisshared = false;
}

void Events::activateEvent(const long unsigned int key)
{
// 	cerr << "key pressed " << key << endl;
	for ( unsigned int i=0; i < modifierevents.size(); i++ )
		if ( modifierevents[i].bindkey == key )
		{
// 			cerr << "activated " << key << endl;
			modifierevents[i].active = true;
			break;
		}

	for ( unsigned int i=0; i < keyevents.size(); i++ )
		if ( keyevents[i].bindkey == key )
		{
// 			cerr << "activated " << key << endl;
			keyevents[i].active = true;
			break;
		}

	checkEventActs();
}

void Events::activateEvent(const string& key)
{
	for ( unsigned int i=0; i < events.size(); i++ )
	{
		if ( events[i].bindbystring && events[i].bindstring == key )
		{
			if ( !events[i].timerisshared )
				cmd->execCmd( events[i].command );
			if ( events[i].responsetime > 0 || events[i].timerisshared )
			{
				events[i].active = true;
// 				events[i].elapsed = events[i].responsetime;
				events[i].elapsed = 0;
				events[i].fresponsetime = events[i].responsetime;
	// 			cerr << "activated " << events[i].name << " rt: " << events[i].elapsed << endl;
			}
			return;
		}
	}
}

void Events::deactivateEvent(const long unsigned int key)
{
	for ( unsigned int i=0; i < modifierevents.size(); i++ )
	{
		if ( modifierevents[i].bindkey == key )
		{
// 			cerr << "deactivated " << key << endl;
			modifierevents[i].active = false;
			break;
		}
	}

	for ( unsigned int i=0; i < keyevents.size(); i++ )
	{
		if ( keyevents[i].bindkey == key )
		{
// 			cerr << "deactivated " << key << endl;
			keyevents[i].active = false;
			break;
		}
	}
	checkEventActs();
}

void Events::deactivateEvent(const string& key)
{
	for ( unsigned int i=0; i < events.size(); i++ )
	{
		if ( events[i].bindbystring && events[i].bindstring == key )
		{
// 			cerr << "deactivating " << events[i].name << endl;
			events[i].active = false;
			return;
		}
	}
}

void Events::checkEventActs()
{
	// activate & deactivate, examine ALL events
	for ( unsigned int i=0; i < events.size(); i++ )
	{
		if ( !events[i].bindbystring )
		{
			// get key & mkey states
			bool keystate = false;
			for ( unsigned int j=0; j < keyevents.size(); j++ )
				if ( keyevents[j].bindkey == events[i].bindkey )
				{
					if ( keyevents[j].active )
						keystate = true;
					break;
				}

			// if the key is not active, so is not the event
			if ( !keystate )
				events[i].active = false;
			else
			{
				bool match = false;
				bool found = false;
				if ( events[i].bindmkey == 0 )
				{
					// all modifiers must be false
					for ( unsigned int j=0; j < modifierevents.size() && !found; j++ )
						if ( modifierevents[j].active )
							found = true;
					if ( !found )
						match = true;
				}
				else 
				{
					for ( unsigned int j=0; j < modifierevents.size() && !found; j++ )
						if ( modifierevents[j].bindkey == events[i].bindmkey )
						{
							found = true;
							if ( modifierevents[j].active )
								match = true;
						}
				}

				if ( match )
				{
					if ( !events[i].timerisshared )
					{
						// execute & deactive if no timer 
						cmd->execCmd( events[i].command );
						if ( events[i].responsetime == 0 )
							deactivateEvent(events[i].bindkey);
					}
					if ( (events[i].responsetime > 0 || events[i].timerisshared) && !events[i].active )
					{
				  if ( events[i].bindkey == 1027 )
				  cerr << "match" << endl;
						events[i].active = true;
						events[i].elapsed = 0;
						events[i].fresponsetime = events[i].responsetime;
// 						cmd->execCmd( events[i].command );
					}
				}
				else
				{
					events[i].active = false;
				}
			}
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

void Events::handlecommands()
{
	processSharedTimers();
  
	for ( unsigned int i=0; i < events.size(); i++ )
	{
		event* e = &events[i];
		if ( e->active )
		{
			// event uses a shared timer
				if ( e->timerisshared )
				{
					if ( e->stimer->active )
						cmd->execCmd( e->command );
				}
			// event has it's own timer
				else
				{
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
						cmd->execCmd( e->command );
					}
				}
		}
	}
}

Events::~Events()
{
}
