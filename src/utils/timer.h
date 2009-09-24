#ifndef TIMER_H
#define TIMER_H
#include <SDL/SDL.h>
#include <sys/time.h>

#include <iostream>

using std::cerr;
using std::endl;

class Timer
{
	public:
		static Timer* Instance();
		int elapsed;
		void mark();

		int sdl_now;
		int sdl_lasttime;

		struct timeval lasttime;
		float timediff(const struct timeval& now, const struct timeval& lasttime);
		
		float bullet_ms;
	protected:
		Timer();
	private:
		static Timer* _instance;
		struct timezone timer_tz;
};

#endif
