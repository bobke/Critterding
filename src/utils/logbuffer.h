#ifndef LOGBUFFER_H
#define LOGBUFFER_H

#include <sstream>
#include <vector>
#include "timer.h"

using namespace std;

struct msg
{
	string str;
	struct timeval	appeartime;
};

class Logbuffer
{
	public:
		static Logbuffer* Instance();

		void		add(const stringstream& streamptr);
		unsigned int	maxMessages;
		float		msgLifetime;

		int		vpadding;
		int		hpadding;

		vector<msg*>	messages;
		void		deleteExpiredMsg();
	protected:
		Logbuffer();

	private:
		static Logbuffer* _instance;

};

#endif
