#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include <string>
#include <vector>
#include "../utils/fps.h" // FIXME howso this is here?
#include "textprinter.h"
#include "panel.h"

using namespace std;

struct msg
{
	string str;
	struct timeval	appeartime;
};

class Textmessage : public Panel
{
	public:
		static Textmessage* Instance();

		void		add(const stringstream& streamptr);
		void		draw();
		unsigned int	maxMessages;
		float		msgLifetime;

		int		vpadding;
		int		hpadding;

	protected:
		Textmessage();
	private:
		static Textmessage* _instance;
		vector<msg*>	messages;

		int		longestLength;
		void		getLongestMsg();

		void		deleteExpiredMsg();
};

#endif
