#ifndef TIMER_H
#define TIMER_H

#ifndef _WIN32
	#include <sys/time.h>
#else
	#include <time.h>
	#include <windows.h>
	#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
	#define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
	#else
	#define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
	#endif
	struct timezone 
	{
		int  tz_minuteswest;
		int  tz_dsttime;
	};
#endif

#include <iostream>

using std::cerr;
using std::endl;

class Timer
{
	public:
		static Timer* Instance();
		float elapsed;
		void mark();

		struct timeval lasttime;

		float timediff(const struct timeval& now, const struct timeval& lasttime);
		
		float bullet_ms;
// 		float bullet_m_Time;
		#ifdef _WIN32
			int gettimeofday(struct timeval *tv, struct timezone *tz);
		#endif
	protected:
		Timer();
	private:
		static Timer* _instance;
		struct timezone timer_tz;
};

#endif
