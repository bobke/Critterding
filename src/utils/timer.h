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
	protected:
		Timer();
	private:
		static Timer* _instance;
		struct timezone	timer_tz;
		struct timeval	lasttime;
};

// class Timer
// {
// 	public:
// 		Timer();
// 		~Timer();
// 
// 		float elapsed;
// 		void mark();
// 
// 	private:
// 
// 		struct timezone	timer_tz;
// 		struct timeval	lasttime;
// };

#endif
