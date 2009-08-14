#ifndef EVENTS_H
#define EVENTS_H

#include <SDL/SDL.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "timer.h"

using namespace std;

struct event
{
	string			name;
	bool			active;
	long unsigned int 	bindkey;
	float			responsetime;
	float			fresponsetime;		// floating responsetime
	float			minfresponsetime;	// minimum floating responsetime
	float			fresponseinterval;	// minimum floating responsetime
	float			elapsed;
};

class Events
{
	public:
		static Events* Instance();

		void registerEvent(SDLKey key, const string& name, float responsetime, float minfresponsetime, float fresponseinterval);

		void activateEvent(const long unsigned int key);
		void deactivateEvent(const long unsigned int key);
		bool isActive(const string& name);
	protected:
		Events();
	private:
		static Events* _instance;

		vector<event>	events;
};

#endif
