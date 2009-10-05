#include "helpinfo.h"

Helpinfo::Helpinfo()
{
	active = false;

	v_width = 420;
	v_height = 520;
	
	halfboxwidth = 210;
	halfboxheight = 260;
}

void Helpinfo::draw()
{
	if (active)
	{
		// deduce position from window width and height
		position.x = *settings->winWidth/2 - halfboxwidth;
		position.y = *settings->winHeight/2 - halfboxheight;

		drawBackground();
		drawBorders();

	// print text
		glEnable(GL_TEXTURE_2D);

		float widthpos1 = position.x + 20.0f;
		float widthpos2 = position.x + 100.0f;
		float heightpos = position.y + 25;
		float vspace = 13.0f;

		printInfoLine(heightpos, widthpos1, widthpos2, "World / Engine operations", "");

		//glColor4f(0.7f, 0.7f, 0.7f, 0.0f);
		glColor3f(0.7f, 0.7f, 0.7f);

		heightpos += vspace + 5.0f;
		printInfoLine(heightpos, widthpos1, widthpos2, "F1", "show/hide this screen");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "F2", "show/hide information bar");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "F3", "show/hide critter statistics");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "F4", "show/hide birth and death events");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "F5/F6", "dec/inc minimum critters");

//		heightpos += vspace;
//		printInfoLine(heightpos, widthpos1, widthpos2, "F5/F6", "adjust energy in the system (by 25 units)");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "F7/F8", "dec/inc kill half of population trigger");

// 		heightpos += vspace;
// 		printInfoLine(heightpos, widthpos1, widthpos2, "F8", "toggle timed food inserts");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "F9/F10", "dec/inc max mutations per brain mutant");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "F11/F12", "dec/inc brain mutation rate (%)");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "shift F9/F10", "dec/inc max mutations per body mutant");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "shift F11/F12", "dec/inc body mutation rate (%)");

// 		heightpos += vspace;
// 		printInfoLine(heightpos, widthpos1, widthpos2, "tab", "show/hide critter statistics");

/*		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "insert", "insert adam");
*/
		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "keypad +/-", "dec/inc energy in the system by 1 food unit");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "c", "switch critter color mode");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "f", "toggle fullscreen");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "i", "insert adam");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "l", "toggle fps limiter (30 fps)");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "m", "toggle mouse mode");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "p", "pause");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "s", "save profile to ./");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "k", "kill half of critters");

// 		heightpos += vspace;
// 		printInfoLine(heightpos, widthpos1, widthpos2, "w", "activate/toggle wall types");

// 		heightpos += vspace;
// 		printInfoLine(heightpos, widthpos1, widthpos2, "x", "deactivate wall");

// 		heightpos += vspace;
// 		printInfoLine(heightpos, widthpos1, widthpos2, "v", "toggle verbosity");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "PgUp", "load all critters from \"~/.critterding/load\"");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "PgDn", "save all critters into \"~/.critterding/save/(timestamp)\"");

		glColor3f(1.0f, 1.0f, 1.0f);

		heightpos += vspace + 5.0f;
		printInfoLine(heightpos, widthpos1, widthpos2, "Camera Operations", "");

		glColor3f(0.7f, 0.7f, 0.7f);

		heightpos += vspace + 5.0f;
		printInfoLine(heightpos, widthpos1, widthpos2, "backspace", "reset camera");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "arrow up", "move camera forward");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "arrow down", "move camera backwards");

		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "Arrow Left", "strafe left");
		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "Arrow Right", "strafe right");
		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "Home", "move up");
		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "End", "move down");
		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "NumKey 2", "look up");
		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "NumKey 8", "look down");
		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "NumKey 4", "look left");
		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "NumKey 6", "look right");
		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "keypad /", "dec camera sensitivity");
		heightpos += vspace;
		printInfoLine(heightpos, widthpos1, widthpos2, "keypad *", "inc camera sensitivity");


		glDisable(GL_TEXTURE_2D);
	}
}

void Helpinfo::printInfoLine(float heightpos, float widthpos1, float widthpos2, const char* key, const char* expl)
{
	Textprinter::Instance()->print(widthpos1, heightpos, key);
	Textprinter::Instance()->print(widthpos2, heightpos, expl);
}

Helpinfo::~Helpinfo()
{
}
