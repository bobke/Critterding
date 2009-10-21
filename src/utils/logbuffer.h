#ifndef LOGBUFFER_H
#define LOGBUFFER_H

#include <sstream>
#include <vector>
#include "timer.h"
#include "../gui/textprinter.h"

using namespace std;

struct msg
{
	string str;
	unsigned int len;
	struct timeval	appeartime;
};

class Logbuffer
{
	public:
		static Logbuffer* Instance();

		void		add(const stringstream& streamptr);
		unsigned int	maxMessages;
		float		msgLifetime;

		unsigned int	longestLength;

		vector<msg*>	messages;
		void		deleteExpiredMsg();
	protected:
		Logbuffer();

	private:
		static Logbuffer* _instance;
		void getLongest();

};

#endif
