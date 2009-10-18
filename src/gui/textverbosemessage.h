#ifndef TEXTVERBOSEMESSAGE_H
#define TEXTVERBOSEMESSAGE_H

#include "../utils/fps.h" // FIXME howso this is here?
#include "panel.h"

using namespace std;

struct vmsg
{
	string str;
	struct timeval	appeartime;
};

class Textverbosemessage : public Panel
{
	public:
		static Textverbosemessage* Instance();

		void		draw();

		void		addBirth(stringstream& streamptr);
		void		addDeath(stringstream& streamptr);
		unsigned int	maxMessages;
		float		msgLifetime;

		void swap();

	protected:
		Textverbosemessage();
	private:
		static Textverbosemessage* _instance;

		vector<vmsg*>	births;
		vector<vmsg*>	deaths;

		float		longestLength;
		void		getLongestMsg();

		void		deleteExpiredMsg();
};

#endif
