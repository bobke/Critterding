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
}

void Timer::mark()
{
	// get now
	timeval now;
	gettimeofday(&now, &timer_tz);
	
	// calc diff between now and lasttime
	elapsed = timediff(now, lasttime);
	//cerr << elapsed << endl;

	if ( elapsed > 0.0f )
		bullet_ms = 1000000.f / elapsed;
	else
		bullet_ms = 1000000.f;

	lasttime = now;
}

#ifdef _WIN32
int Timer::gettimeofday(struct timeval *tv, struct timezone *tz)
{
	FILETIME ft;
	unsigned __int64 tmpres = 0;
	static int tzflag;
 
	if (NULL != tv)
	{
		GetSystemTimeAsFileTime(&ft);

		tmpres |= ft.dwHighDateTime;
		tmpres <<= 32;
		tmpres |= ft.dwLowDateTime;

		/*converting file time to unix epoch*/
		tmpres /= 10;  /*convert into microseconds*/
		tmpres -= DELTA_EPOCH_IN_MICROSECS; 
		tv->tv_sec = (long)(tmpres / 1000000UL);
		tv->tv_usec = (long)(tmpres % 1000000UL);
	}

	if (NULL != tz)
	{
		if (!tzflag)
		{
			_tzset();
			tzflag++;
		}
		tz->tz_minuteswest = _timezone / 60;
		tz->tz_dsttime = _daylight;
	}
	cerr << "yeah" << endl;
	return 0;
}
#endif

float Timer::timediff(const struct timeval& now, const struct timeval& lasttime)
{
	return ( (float)((now.tv_sec - lasttime.tv_sec) * 1000000 + (now.tv_usec - lasttime.tv_usec)) / 1000000);
}
