#include "file.h"

File::File()
{
}

bool File::exists(string &file)
{
	fstream file_op(file.c_str(),ios::in);
	if (file_op)
	{
		file_op.close();
		return true;
	}
	else return false;
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

bool File::open(string &filename, string &content)
{
	content.clear();
	char str[2000];
//	string str;

	fstream file_op(filename.c_str(),ios::in);
	if (file_op)
	{
		while ( !file_op.eof() )
		{
			file_op.getline(str,2000);
			content.append(str);
			content.append("\n");
		}
		file_op.close();
		return true;
	}
	else return false;
}

bool File::open(char* filename, string &content)
{
	content.clear();
	char str[2000];

	fstream file_op(filename,ios::in);
	if (file_op)
	{
		while ( !file_op.eof() )
		{
			file_op.getline(str,2000);
			content.append(str);
			content.append("\n");
		}
		file_op.close();
		return true;
	}
	else return false;
}

File::~File()
{
}


