#ifdef _WIN32
	#include <unistd.h>
#endif
#include "timer.h"

Timer* Timer::Instance () 
{
	static Timer t;
	return &t; // _instance isn't needed in this case
}

Timer::Timer()
{
	// calc lasttime for first time
// 	gettimeofday(&lasttime, &timer_tz);
	sdl_lasttime = 0;
}

void Timer::mark()
{
	// get now
// 	gettimeofday(&lasttime, &timer_tz);
	sdl_now = SDL_GetTicks();

	// calc diff between now and lasttime
	elapsed = sdl_now - sdl_lasttime;
// 	while ( elapsed == 0)
// 	{
// 		usleep(100);
// 		sdl_now = SDL_GetTicks();
// 		elapsed = sdl_now - sdl_lasttime;
// 		// cerr << sdl_now << " frame missed" << endl;
// 	}

	if ( elapsed > 0 )
		bullet_ms = 1000.f / elapsed;
	else
		bullet_ms = 0;

	sdl_lasttime = sdl_now;
}

// float Timer::timediff(const struct timeval& now, const struct timeval& lasttime)
// {
// 	return ( (float)((now.tv_sec - lasttime.tv_sec) * 1000000 + (now.tv_usec - lasttime.tv_usec)) / 1000000);
// }
