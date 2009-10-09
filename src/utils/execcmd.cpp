#include "execcmd.h"

Execcmd::Execcmd()
{
}

cmdsettings Execcmd::gen(const string& name)
{
	cmdsettings c;
	c.name = name;
	c.argtype = A_NOARG;
	return c;
}

cmdsettings Execcmd::gen(const string& name, const string& str)
{
	cmdsettings c;
	c.name = name;
	c.argtype = A_STRING;
	c.args = str;
	return c;
}

Execcmd::~Execcmd()
{
}
