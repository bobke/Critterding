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

struct keyevent
{
	string			name;
	bool			active;
	long unsigned int 	bindkey;
};

struct modifierevent
{
	string			name;
	bool			active;
	long unsigned int 	bindkey;
};

struct event
{
	string			name;
	bool			active;
	bool			bindbystring;
// 	keyevent*		bindkey; // FIXME GODDAMNED
	long unsigned int 	bindkey;
// 	modifierevent*	 	bindmkey;
	long unsigned int 	bindmkey;
	string			bindstring;

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
		~Events();

		void			registerModifierEvent(const long unsigned int key);
		void			registerKeyEvent(const long unsigned int key);

		void			registerEvent(const long unsigned int key, const string& name, const cmdsettings& cmd, sharedTimer* stimer);
		void			registerEvent(const long unsigned int key, const string& name, const cmdsettings& cmd, unsigned int responsetime, unsigned int minfresponsetime, unsigned int fresponseinterval);
		void			registerEvent(SDLKey mkey, const long unsigned int key, const string& name, const cmdsettings& cmd, unsigned int responsetime, unsigned int minfresponsetime, unsigned int fresponseinterval);
		void			registerEvent(const string& name, const cmdsettings& cmd, unsigned int responsetime, unsigned int minfresponsetime, unsigned int fresponseinterval);

		void			activateEvent(const long unsigned int key);
		void			activateEvent(const string& key);
		void			deactivateEvent(const long unsigned int key);
		void			deactivateEvent(const string& key);

		sharedTimer*		registerSharedtimer(unsigned int responsetime);
		void			processSharedTimers();
		void			handlecommands();
	protected:
		Events();
	private:
		static Events*		_instance;
		Commands* cmd;

		vector<event>		events;

		vector<modifierevent>	modifierevents;
		vector<keyevent>	keyevents;

		vector<sharedTimer>	sharedtimers;
		void 			checkEventActs();
		keyevent* 		getKeyEventP(const long unsigned int key);
		modifierevent* 		getMKeyEventP(const long unsigned int key);
};

#endif
