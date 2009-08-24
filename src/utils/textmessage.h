#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include <string>
#include <vector>
#include "fps.h"
#include "textprinter.h"

using namespace std;

struct msg
{
	string str;
	struct timeval	appeartime;
};

class Textmessage
{
	public:
		static Textmessage* Instance();

		void		add(const stringstream& streamptr);
/*		stringstream&	operator<<(stringstream& streamptr);
		ostream& 	operator<<(ostream& streamptr);
		stringstream&	operator<<(const char* streamptr);*/
		void		draw();
		unsigned int	maxMessages;
		float		msgLifetime;

		float		vpadding;
		float		hpadding;

	protected:
		Textmessage();
	private:
		static Textmessage* _instance;
		vector<msg*>	messages;

		float		longestLength;
		void		getLongestMsg();

		void		deleteExpiredMsg();
};

#endif
