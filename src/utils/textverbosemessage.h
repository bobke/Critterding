#ifndef TEXTVERBOSEMESSAGE_H
#define TEXTVERBOSEMESSAGE_H

#include <string>
#include <vector>
#include "fps.h"
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
		void		draw(unsigned int posX);
		unsigned int	maxMessages;
		float		msgLifetime;

		float		vpadding;
		float		hpadding;

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
