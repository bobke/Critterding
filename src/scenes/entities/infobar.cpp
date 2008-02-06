#include "infobar.h"

Infobar* Infobar::trueSelf = NULL;

Infobar* Infobar::instance()
{
	if (trueSelf == NULL) trueSelf = new Infobar();
	return trueSelf;
};


void Infobar::draw(string text)
{
		cerr << "DIEEEE" << text << endl;

//		cerr << text << endl;

// 		// Move back to the origin (for the text, below).
// 		glLoadIdentity();
// 
// 		// We need to change the projection matrix for the text rendering.
// 		glMatrixMode(GL_PROJECTION);
// 
// 		// But we like our current view too; so we save it here.
// 		glPushMatrix();
// 
// 		// Now we set up a new projection for the text.
// 		glLoadIdentity();
// 		glOrtho(0,400,0,50,-1.0,1.0);
// 
// 		glDisable(GL_DEPTH_TEST);
// 
// 		glTranslatef( 1.0f, 50-18, 0.0f);
// 
// 		glColor4f(0.9,0.2,0.2,.75);
// 		glRasterPos2i(5,1);

}
