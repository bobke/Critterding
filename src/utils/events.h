#ifndef EVENTS_H
#define EVENTS_H

#include <SDL/SDL.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "timer.h"

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
	long unsigned int 	bindkey;
	float			responsetime;
	float			fresponsetime;		// floating responsetime
	float			minfresponsetime;	// minimum floating responsetime
	float			fresponseinterval;	// floating degredation interval
	float			elapsed;
	
	bool			timerisshared;
	sharedTimer*		stimer;
};

class Events
{
	public:
		static Events*		Instance();

		sharedTimer*		registerSharedtimer(float responsetime);

		void			registerEvent(SDLKey key, const string& name, unsigned int responsetime, unsigned int minfresponsetime, unsigned int fresponseinterval);
		void			registerEvent(SDLKey key, const string& name, sharedTimer* stimer);

		void			activateEvent(const long unsigned int key);
		void			deactivateEvent(const long unsigned int key);
		void			processSharedTimers();
		bool			isActive(const string& name);
	protected:
		Events();
	private:
		static Events*		_instance;

		vector<event>		events;
		vector<sharedTimer>	sharedtimers;
};

#endif
