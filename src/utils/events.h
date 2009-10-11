#ifndef EVENTS_H
#define EVENTS_H

#include <SDL/SDL.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "timer.h"
#include "commands.h"
#include "execcmd.h"

using namespace std;

struct sharedTimer
{
	bool			active;
	unsigned int		responsetime;
	unsigned int		elapsed;
};

struct event
{
	string			name;
	bool			active;
	bool			bindbystring;
	long unsigned int 	bindkey;
	string			bindstring;

	bool			isNewEvent;

	cmdsettings		command;

	// private timer
	unsigned int		responsetime;
	int			fresponsetime;
	unsigned int		minfresponsetime;
	unsigned int		fresponseinterval;	// degredation interval
	unsigned int		elapsed;

	// shared timer
	bool			timerisshared;
	sharedTimer*		stimer;
};

class Events
{
	public:
		static Events*		Instance();

		sharedTimer*		registerSharedtimer(unsigned int responsetime);

		void			registerEvent(SDLKey key, const string& name, unsigned int responsetime, unsigned int minfresponsetime, unsigned int fresponseinterval);
		void			registerEvent(SDLKey key, const string& name, const cmdsettings& cmd, unsigned int responsetime, unsigned int minfresponsetime, unsigned int fresponseinterval);
		void			registerEvent(const string& name, const cmdsettings& cmd, unsigned int responsetime, unsigned int minfresponsetime, unsigned int fresponseinterval);
		void			registerEvent(SDLKey key, const string& name, sharedTimer* stimer);

		void			activateEvent(const long unsigned int key);
		void			activateEvent(const string& key);
		void			deactivateEvent(const long unsigned int key);
		void			deactivateEvent(const string& key);

		void			processSharedTimers();
		void			handlecommands();

		bool			isActive(const string& name);
	protected:
		Events();
	private:
		static Events*		_instance;
		Commands* cmd;

		vector<event>		events;
		vector<sharedTimer>	sharedtimers;
};

#endif
