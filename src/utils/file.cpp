#include "file.h"

File::File()
{
}

bool File::exists(string &file)
{
	return exists( file.c_str() );
}

bool File::exists(const char* file)
{
	fstream file_op(file,ios::in);
	if (file_op.is_open())
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

bool File::open(const char* filename, string &content)
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


