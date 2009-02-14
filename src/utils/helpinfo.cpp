#include "helpinfo.h"

Helpinfo::Helpinfo()
{
	active = false;
}

void Helpinfo::draw()
{
	if (active)
	{
		glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0, *Settings::Instance()->winWidth, *Settings::Instance()->winHeight, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
			glHint(GL_FOG_HINT, GL_FASTEST);
			glDisable(GL_COLOR_MATERIAL);
			glDisable(GL_DITHER);
			glDisable(GL_POLYGON_SMOOTH);
			glDisable(GL_DEPTH_TEST);
			glDisable (GL_LIGHTING);

			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);

			float halfwidth = (*Settings::Instance()->winWidth/2.0f);
			float halfheight = (*Settings::Instance()->winHeight/2.0f);

			float halfboxwidth = 230.0f;
			float halfboxheight = 250.0f;

			// draw background box and border
				glColor4f(0.0f, 0.0f, 0.0f, 0.9f);
				glBegin(GL_QUADS);
					glVertex2f(halfwidth-halfboxwidth, halfheight+halfboxheight);
					glVertex2f(halfwidth-halfboxwidth, halfheight-halfboxheight);
					glVertex2f(halfwidth+halfboxwidth, halfheight-halfboxheight);
					glVertex2f(halfwidth+halfboxwidth, halfheight+halfboxheight);
				glEnd();

				glDisable(GL_BLEND);

				glColor4f(1.0f, 1.0f, 1.0f, 0.0f);

				glBegin(GL_LINES);
					glVertex2f(halfwidth-halfboxwidth, halfheight+halfboxheight);
					glVertex2f(halfwidth-halfboxwidth, halfheight-halfboxheight);

					glVertex2f(halfwidth-halfboxwidth, halfheight-halfboxheight);
					glVertex2f(halfwidth+halfboxwidth, halfheight-halfboxheight);

					glVertex2f(halfwidth+halfboxwidth, halfheight-halfboxheight);
					glVertex2f(halfwidth+halfboxwidth, halfheight+halfboxheight);

					glVertex2f(halfwidth+halfboxwidth, halfheight+halfboxheight);
					glVertex2f(halfwidth-halfboxwidth, halfheight+halfboxheight);
				glEnd();

			// print text
				glPushAttrib(GL_LIST_BIT);

				float widthpos1 = halfwidth-(halfboxwidth-20.0f);
				float widthpos2 = halfwidth-(halfboxwidth-100.0f);
				float heightpos = halfheight-(halfboxheight-25.0f);
				float vspace = 14.0f;

				printInfoLine(heightpos, widthpos1, widthpos2, "World / Engine operations", "");

				glColor4f(0.7f, 0.7f, 0.7f, 0.0f);

				heightpos += vspace + 5.0f;
				printInfoLine(heightpos, widthpos1, widthpos2, "F1", "show/hide this screen");

				heightpos += vspace;
				printInfoLine(heightpos, widthpos1, widthpos2, "F2", "show/hide information bar");

				heightpos += vspace;
				printInfoLine(heightpos, widthpos1, widthpos2, "F3/F4", "decrease/increase minimum critters");

				heightpos += vspace;
				printInfoLine(heightpos, widthpos1, widthpos2, "F5/F6", "adjust energy in the system (by 25 units)");

				heightpos += vspace;
				printInfoLine(heightpos, widthpos1, widthpos2, "keypad +/-", "adjust energy in the system (by 1 unit)");

				heightpos += vspace;
				printInfoLine(heightpos, widthpos1, widthpos2, "F7", "insert new critter (adam)");

				heightpos += vspace;
				printInfoLine(heightpos, widthpos1, widthpos2, "F8", "toggle timed food inserts");

				heightpos += vspace;
				printInfoLine(heightpos, widthpos1, widthpos2, "F9/F10", "adjust max mutations per mutant");

				heightpos += vspace;
				printInfoLine(heightpos, widthpos1, widthpos2, "F11/F12", "adjust mutation rate (%)");

				heightpos += vspace;
				printInfoLine(heightpos, widthpos1, widthpos2, "insert", "toggle hide critter retinas");

				heightpos += vspace;
				printInfoLine(heightpos, widthpos1, widthpos2, "w", "activate/toggle wall types");

				heightpos += vspace;
				printInfoLine(heightpos, widthpos1, widthpos2, "x", "deactivate wall");

				heightpos += vspace;
				printInfoLine(heightpos, widthpos1, widthpos2, "v", "toggle verbosity");

				heightpos += vspace;
				printInfoLine(heightpos, widthpos1, widthpos2, "f", "toggle critterview");

				heightpos += vspace;
				printInfoLine(heightpos, widthpos1, widthpos2, "PgUp", "load all critters from \"~/.critterding/load\"");

				heightpos += vspace;
				printInfoLine(heightpos, widthpos1, widthpos2, "PgDn", "save all critters into \"~/.critterding/save/(timestamp)\"");

				heightpos += vspace;
				printInfoLine(heightpos, widthpos1, widthpos2, "p", "pause");

				glColor4f(1.0f, 1.0f, 1.0f, 0.0f);

				heightpos += vspace + 5.0f;
				printInfoLine(heightpos, widthpos1, widthpos2, "Camera Operations", "");

				glColor4f(0.7f, 0.7f, 0.7f, 0.0f);

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
				printInfoLine(heightpos, widthpos1, widthpos2, "keypad /", "decrease camera sensitivity");
				heightpos += vspace;
				printInfoLine(heightpos, widthpos1, widthpos2, "keypad *", "increase camera sensitivity");




	// 		glRasterPos2f(10.0f, 75.0f);
	// 		printGLf("Energy in system: %3.0f", (settings->freeEnergyInfo / settings->food_maxenergy));

	/*		glRasterPos2f(10.0f, 90.0f);
			printGLf("Free Energy: %3.0f", world.freeEnergy);*/
			glPopAttrib();
			
		glPopMatrix();
	}
}

void Helpinfo::printInfoLine(float heightpos, float widthpos1, float widthpos2, const char* key, const char* expl)
{
	glRasterPos2f(widthpos1, heightpos);
	printGLf(key);
		glRasterPos2f(widthpos2, heightpos);
		printGLf(expl);
}

void Helpinfo::printGLf(const char *fmt, ...)
{
    va_list ap;     /* our argument pointer */
    char text[256];
    if (fmt == NULL)
        return;
    va_start(ap, fmt);  /* make ap point to first unnamed arg */
    /* FIXME: we *should* do boundschecking or something to prevent buffer
     * overflows/segmentations faults
     */
//vprintf(fmt, ap);
    vsprintf(text, fmt, ap);
    va_end(ap);
    glListBase(Settings::Instance()->fontbase - 32);
    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
}

void Helpinfo::swap()
{
	active = !active;
	//fps.swap();
}

Helpinfo::~Helpinfo()
{
}
