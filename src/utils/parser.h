#ifndef PARSER_H
#define PARSER_H

#include <string>

using namespace std;

class Parser
{
	public:
		Parser();
		~Parser();

		string		returnUntillStrip(string stop, string &line);
		string		returnUntill(string stop, string &line);

		bool		beginMatches(string stop, string &line);
		bool		beginMatchesStrip(string stop, string &line);

		bool		endMatches(string stop, string &line);
};

#endif
