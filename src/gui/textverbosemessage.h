#ifndef TEXTVERBOSEMESSAGE_H
#define TEXTVERBOSEMESSAGE_H

#include <string>
#include <vector>
#include "../utils/fps.h" // FIXME howso this is here?
#include "textprinter.h"

using namespace std;

struct vmsg
{
	string str;
	struct timeval	appeartime;
};

class Textverbosemessage
{
	public:
		static Textverbosemessage* Instance();

		void		addBirth(stringstream& streamptr);
		void		addDeath(stringstream& streamptr);
		void		draw(unsigned int posY);
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
		bool		active;

};

#endif
