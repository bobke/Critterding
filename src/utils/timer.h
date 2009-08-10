#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <sys/time.h>

using std::cerr;
using std::endl;

class Timer
{
	public:
		static Timer* Instance();
		float elapsed;
		void mark();
		struct timeval lasttime;
		float timediff(struct timeval& now, struct timeval& lasttime);
		
		float bullet_ms;
		float bullet_m_Time;
	protected:
		Timer();
	private:
		static Timer* _instance;
		struct timezone	timer_tz;
};

#endif
