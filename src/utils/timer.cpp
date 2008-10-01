#include "timer.h"

Timer* Timer::Instance () 
{
	static Timer t;
	return &t; // _instance isn't needed in this case
}

Timer::Timer()
{
	// calc lasttiem for first time
	gettimeofday(&lasttime, &timer_tz);
}

void Timer::mark()
{
	// get now
	timeval now;
	gettimeofday(&now, &timer_tz);
	
	// calc diff between now and lasttime
	elapsed = ( (float)((now.tv_sec - lasttime.tv_sec) * 1000000 + (now.tv_usec - lasttime.tv_usec)) / 1000000);
	//cerr << elapsed << endl;
	
	lasttime = now;
}
