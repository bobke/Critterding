#include "file.h"

File::File()
{
}

void File::save(string &filename, string &content)
{
	fstream file_op(filename.c_str(),ios::out);
	file_op << content;
	file_op.close();
}

void File::save(string &filename, string* content)
{
	fstream file_op(filename.c_str(),ios::out);
	file_op << *content;
	file_op.close();
}

void File::open(string &filename, string &content)
{
	content.clear();
	string str;

	fstream file_op(filename.c_str(),ios::in);
	while ( file_op >> str )
	{
		content.append(str);
		content.append("\n");
	}
	file_op.close();
}

File::~File()
{
}


