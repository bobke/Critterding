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

FTPoint Textprinter::getBBox(const char *fmt, ...)
{
		va_list ap;     /* our argument pointer */
		char text[256];
		va_start(ap, fmt);  /* make ap point to first unnamed arg */
		/* FIXME: we *should* do boundschecking or something to prevent buffer
		* overflows/segmentations faults
		*/
		vsprintf(text, fmt, ap);

		FTBBox test = fonts[0]->BBox(text);
		return test.Upper();
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


FTPoint Textprinter::getBBox(string& str)
{
	const char *text = str.c_str();

	FTBBox test = fonts[0]->BBox(text);
	return test.Upper();
}


void Textprinter::print(float x, float y, string& str)
{
	glPushMatrix();

		glTranslatef(x, y, 0);
		glRotatef(180, 1.0f, 0.0f, 0.0f);

		const char *text = str.c_str();
		fonts[0]->Render(text);

	glPopMatrix();
}

void Textprinter::printR(float x, float y, const char *fmt, ...)
{
	va_list ap;     /* our argument pointer */
	char text[256];
	va_start(ap, fmt);  /* make ap point to first unnamed arg */
	/* FIXME: we *should* do boundschecking or something to prevent buffer
	* overflows/segmentations faults
	*/
	vsprintf(text, fmt, ap);

	string str(text);

	FTPoint bbox = getBBox(str);
	print(x - bbox.X(), y, str);
}

void Textprinter::setUpFonts()
{
	char const *fontFilePath;
	//fontFilePath = "fonts/helvetica_3.ttf";
	fontFilePath = "fonts/verdana.ttf";

	// Allocate an array to hold all fonts
	fonts = new FTFont *[1];

	fonts[0] = new FTTextureFont(fontFilePath);

	if(fonts[0]->Error())
	{
		cerr << "Failed to open font %s\n" << endl;;
		exit(1);
	}

	if(!fonts[0]->FaceSize(11))
	{
		cerr << "Failed to set size" << endl;
		exit(1);
	}

	fonts[0]->Depth(20);
	fonts[0]->CharMap(ft_encoding_unicode);
}
