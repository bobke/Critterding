#ifndef TEXTVERBOSEMESSAGE_H
#define TEXTVERBOSEMESSAGE_H

#include "../../utils/timer.h" // FIXME howso this is here?
#include "../../gui/panel.h"

using namespace std;

struct vmsg
{
	string str;
	unsigned int	appeartime;
};

class Textverbosemessage : public Panel
{
	public:
		static Textverbosemessage* Instance();

		void		draw();

		void		addBirth(stringstream& streamptr);
		void		addDeath(stringstream& streamptr);
		unsigned int	maxMessages;
		unsigned int	msgLifetime;

		void swap();

	protected:
		Textverbosemessage();
	private:
		static Textverbosemessage* _instance;

		vector<vmsg*>	births;
		vector<vmsg*>	deaths;

// 		float		longestLength;
		void		getLongestMsg();

		void		deleteExpiredMsg();
		
		unsigned int	col2;
};

#endif
