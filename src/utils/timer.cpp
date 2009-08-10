#include "timer.h"

Timer* Timer::Instance () 
{
	static Timer t;
	return &t; // _instance isn't needed in this case
}

Timer::Timer()
{
	// calc lasttime for first time
	gettimeofday(&lasttime, &timer_tz);

	bullet_m_Time = 0.0f;
}

void Timer::mark()
{
	// get now
	timeval now;
	gettimeofday(&now, &timer_tz);
	
	// calc diff between now and lasttime
	elapsed = timediff(now, lasttime);
	//cerr << elapsed << endl;

// 	bullet_ms = 1000000.f / (1/Timer::Instance()->elapsed);
	bullet_ms = 1000000.f / Timer::Instance()->elapsed;
// 	if (bullet_ms > 16666.6666f)
// 		bullet_ms = 16666.6666f;

	bullet_m_Time += bullet_ms;

	lasttime = now;
}

float Timer::timediff(struct timeval& now, struct timeval& lasttime)
{
	return ( (float)((now.tv_sec - lasttime.tv_sec) * 1000000 + (now.tv_usec - lasttime.tv_usec)) / 1000000);
}
