#include "textprinter.h"

Textprinter* Textprinter::Instance () 
{
	static Textprinter t;
	return &t;
}

Textprinter::Textprinter()
{
	setUpFonts();
}

void Textprinter::print(int x, int y, const char *fmt, ...)
{
	glPushMatrix();

		glTranslatef(x, y, 0);
// 		glRotatef(180, 1.0f, 0.0f, 0.0f);
		glScalef(1,-1,1);

		va_list ap;     /* our argument pointer */
		char text[256];
		if (fmt == NULL)
		return;
		va_start(ap, fmt);  /* make ap point to first unnamed arg */
		/* FIXME: we *should* do boundschecking or something to prevent buffer
		* overflows/segmentations faults
		*/
		vsprintf(text, fmt, ap);

		fonts[0]->Render(text);

	glPopMatrix();
}

string Textprinter::getFormattedString(const char *fmt, ...)
{

	va_list ap;     /* our argument pointer */
	char text[256];
	va_start(ap, fmt);  /* make ap point to first unnamed arg */
	/* FIXME: we *should* do boundschecking or something to prevent buffer
	* overflows/segmentations faults
	*/
	vsprintf(text, fmt, ap);

	string a(text);
	return a;
}

unsigned int Textprinter::getWidth(const char *fmt, ...)
{
	va_list ap;     /* our argument pointer */
	char text[256];
	va_start(ap, fmt);  /* make ap point to first unnamed arg */
	/* FIXME: we *should* do boundschecking or something to prevent buffer
	* overflows/segmentations faults
	*/
	vsprintf(text, fmt, ap);

	FTBBox test = fonts[0]->BBox(text);
	return test.Upper().X();
}

unsigned int Textprinter::getWidth(const string& str)
{
	const char *text = str.c_str();

	FTBBox test = fonts[0]->BBox(text);
	return test.Upper().X();
}

unsigned int Textprinter::getWidth(const int& number)
{
	stringstream sstream;
	sstream << number;
	const char *text = sstream.str().c_str();

	FTBBox test = fonts[0]->BBox(text);
	return test.Upper().X();
}

Vector2i Textprinter::getDimensions(const string& str)
{
	const char *text = str.c_str();

	FTBBox test = fonts[0]->BBox(text);
	Vector2i v(test.Upper().X(), test.Upper().Y());
	return v;
}

// FTPoint Textprinter::getBBox(const char *fmt, ...)
// {
// 		va_list ap;     /* our argument pointer */
// 		char text[256];
// 		va_start(ap, fmt);  /* make ap point to first unnamed arg */
// 		/* FIXME: we *should* do boundschecking or something to prevent buffer
// 		* overflows/segmentations faults
// 		*/
// 		vsprintf(text, fmt, ap);
// 
// 		FTBBox test = fonts[0]->BBox(text);
// 		return test.Upper();
// }

// // FIXME if we get rid of this ftbbox shit here, we can cleanup the makefile
// FTPoint Textprinter::getBBox(const string& str)
// {
// 	const char *text = str.c_str();
// 
// 	FTBBox test = fonts[0]->BBox(text);
// 	return test.Upper();
// }

// FIXME get rid of this
void Textprinter::print(int x, int y, const string& str)
{
	glPushMatrix();

		glTranslatef(x, y, 0);
		glScalef(1,-1,1);
		const char *text = str.c_str();
		fonts[0]->Render(text);

	glPopMatrix();
}

void Textprinter::print(int x, int y, const long unsigned int& longuint)
{
	stringstream sstream;
	sstream << longuint;
	print(x, y, sstream.str());
}

void Textprinter::print(const Vector2i& pos, const string& str)
{
	glPushMatrix();

		glTranslatef(pos.x, pos.y, 0);
		glScalef(1,-1,1);
// 		glRotatef(180, 1.0f, 0.0f, 0.0f);

		const char *text = str.c_str();
		fonts[0]->Render(text);

	glPopMatrix();
}

void Textprinter::print(const Vector2i& pos, const unsigned int* num)
{
	glPushMatrix();

		glTranslatef(pos.x, pos.y, 0);
		glScalef(1,-1,1);
// 		glRotatef(180, 1.0f, 0.0f, 0.0f);

		stringstream str;
		str << *num;
		fonts[0]->Render(str.str().c_str());

	glPopMatrix();
}

void Textprinter::printR(float x, float y, const char *fmt, ...)
{
	va_start(ap, fmt);
	vsprintf(text, fmt, ap);
	string str(text);
	print(x - getWidth(str), y, str);
}

void Textprinter::setUpFonts()
{
	// clear if exists
	if ( fonts )
	{
		delete fonts[0];
		delete fonts;
	}
	
	// Allocate an array to hold all fonts
	fonts = new FTFont *[1];
	char const *fontFilePath;

	string fontpath = Settings::Instance()->binarypath;
	string defaultf = "../share/critterding/font.ttf";
	string systemf = "/usr/share/fonts/TTF/DejaVuSans.ttf";

	string usepath = fontpath;
	usepath.append(defaultf);
	
	if ( !file.exists(usepath.c_str()) )
	{
		usepath = systemf;
		if ( !file.exists(usepath.c_str()) )
		{
			cerr << "Count not find font " << usepath << endl;
			exit(1);
		}
	}

// 	fontFilePath = "fonts/DejaVuSans.ttf";
// 	if ( !file.exists(fontFilePath) )
// 	{
// 		fontFilePath = "../fonts/DejaVuSans.ttf";
// 		if ( !file.exists(fontFilePath) )
// 		{
// 			fontFilePath = "/usr/share/fonts/TTF/DejaVuSans.ttf";
// 			if ( !file.exists(fontFilePath) )
// 			{
// 				cerr << "Count not find font " << fontFilePath << endl;
// 				exit(1);
// 			}
// 		}
// 	}

	fonts[0] = new FTTextureFont(usepath.c_str());
	fonts[0]->UseDisplayList(true);

	if(!fonts[0]->FaceSize(11))
	{
		cerr << "Failed to set size" << endl;
		exit(1);
	}

// 	fonts[0]->Depth(32);
	fonts[0]->CharMap(ft_encoding_unicode);
}
