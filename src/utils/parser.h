#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>

using namespace std;

class Parser
{
	public:
		static Parser* Instance();

		string		returnUntillStrip(string stop, string &line);
		string		returnUntill(string stop, string &line);

		bool		beginMatches(string stop, string &line);
		bool		beginMatchesStrip(string stop, string &line);

		bool		endMatches(string stop, string &line);
		bool		endMatchesStrip(string stop, string &line);
		bool		contains(string stop, string &line);

	protected:
		Parser();
	private:
		static Parser* _instance;
};

#endif
