#include "textmessage.h"

Textmessage::Textmessage()
{
	isMovable = true;
	
	vpadding = 10;
	hpadding = 10;

	position.x = 10;
	position.y = 50;

// 	v_width = 300;

// 	v_width = 200 + ( hpadding*2 );
// 	v_height = (15 * (messages.size()-1)) + 20 + ( vpadding*2 );
}

void Textmessage::draw()
{
	Logbuffer::Instance()->deleteExpiredMsg();
	if ( !Logbuffer::Instance()->messages.empty() )
	{
		active = true;
		
		unsigned int height = 5;

		v_width = Logbuffer::Instance()->longestLength + ( hpadding*2 );
		v_height = (15 * (Logbuffer::Instance()->messages.size()-1)) + height + ( vpadding*2 );
		
	// draw background box and border
		drawBackground();
		drawBorders();

	// render text
		glColor3f(1.0f, 1.0f, 1.0f);
		for ( unsigned int i = 0; i < Logbuffer::Instance()->messages.size(); i++ )
			Textprinter::Instance()->print(position.x + hpadding, position.y + height + (i*15.0f) + vpadding, Logbuffer::Instance()->messages[i]->str);
	}
	else
		active = false;
}

Textmessage::~Textmessage()
{
}