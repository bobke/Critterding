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

void Textprinter::print(float x, float y, const char *fmt, ...)
{
	glPushMatrix();

		glTranslatef(x, y, 0);
		glRotatef(180, 1.0f, 0.0f, 0.0f);

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
void Textprinter::print(float x, float y, const string& str)
{
	glPushMatrix();

		glTranslatef(x, y, 0);
		glRotatef(180, 1.0f, 0.0f, 0.0f);

		const char *text = str.c_str();
		fonts[0]->Render(text);

	glPopMatrix();
}

void Textprinter::print(const Vector2i& pos, const string& str)
{
	glPushMatrix();

		glTranslatef(pos.x, pos.y, 0);
		glRotatef(180, 1.0f, 0.0f, 0.0f);

		const char *text = str.c_str();
		fonts[0]->Render(text);

	glPopMatrix();
}

void Textprinter::print(const Vector2i& pos, const unsigned int* num)
{
	glPushMatrix();

		glTranslatef(pos.x, pos.y, 0);
		glRotatef(180, 1.0f, 0.0f, 0.0f);

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
	char const *fontFilePath;
	//fontFilePath = "fonts/helvetica_3.ttf";
	fontFilePath = "fonts/verdana.ttf";

	// Allocate an array to hold all fonts
	fonts = new FTFont *[1];

	if ( !file.exists(fontFilePath) )
	{
		fontFilePath = "../fonts/verdana.ttf";
		if ( !file.exists(fontFilePath) )
		{
			cerr << "Count not find font " << fontFilePath << endl;
			exit(1);
		}
	}

	fonts[0] = new FTTextureFont(fontFilePath);

	if(!fonts[0]->FaceSize(11))
	{
		cerr << "Failed to set size" << endl;
		exit(1);
	}

	fonts[0]->Depth(20);
	fonts[0]->CharMap(ft_encoding_unicode);
}
