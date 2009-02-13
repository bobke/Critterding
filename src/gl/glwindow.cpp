#include "glwindow.h"

GLWindow::GLWindow()
{
}

void GLWindow::create(const char* title, int width, int height, int bpp)
{
	int attrListSgl[] = {GLX_RGBA, GLX_RED_SIZE, 4,
				GLX_GREEN_SIZE, 4,
				GLX_BLUE_SIZE, 4,
				GLX_ALPHA_SIZE, 4,
				GLX_DEPTH_SIZE, 16,
				None};

	int attrListDbl[] = {GLX_RGBA, GLX_DOUBLEBUFFER,
				GLX_RED_SIZE, 4,
				GLX_GREEN_SIZE, 4,
				GLX_BLUE_SIZE, 4,
				GLX_ALPHA_SIZE, 4,
				GLX_DEPTH_SIZE, 16,
				None};

	XVisualInfo *vi;
	Colormap cmap;
	Atom wmDelete;
	Window winDummy;
	unsigned int borderDummy;

	GLWin.dpy = XOpenDisplay(0);
	GLWin.screen = DefaultScreen(GLWin.dpy);
	cerr << GLWin.dpy << endl;

	GLWin.owidth=width; GLWin.oheight=height;

	vi = glXChooseVisual(GLWin.dpy, GLWin.screen, attrListDbl);
	if(NULL == vi)
	{
		vi = glXChooseVisual(GLWin.dpy, GLWin.screen, attrListSgl);
		cerr << " Buffering: Singlebuffered" << endl;
	}
	else
	{
		cerr << " Buffering: Doublebuffered" << endl;
	}

	GLWin.ctx = glXCreateContext(GLWin.dpy, vi, 0, GL_TRUE);

	cmap = XCreateColormap(GLWin.dpy, RootWindow(GLWin.dpy, vi->screen),vi->visual, AllocNone);
	GLWin.attr.colormap = cmap;
	GLWin.attr.border_pixel = 0;

		//cerr << " Running: Windowed" << endl;
		GLWin.attr.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask;
		GLWin.win = XCreateWindow(GLWin.dpy, RootWindow(GLWin.dpy, vi->screen),
			  0, 0, width, height, 0, vi->depth, InputOutput, vi->visual,
			  CWBorderPixel | CWColormap | CWEventMask, &GLWin.attr);
		wmDelete = XInternAtom(GLWin.dpy, "WM_DELETE_WINDOW", True);
		XSetWMProtocols(GLWin.dpy, GLWin.win, &wmDelete, 1);
		XSetStandardProperties(GLWin.dpy, GLWin.win, title,
			title, None, NULL, 0, NULL);
		XMapRaised(GLWin.dpy, GLWin.win);

	glXMakeCurrent(GLWin.dpy, GLWin.win, GLWin.ctx);
	XGetGeometry(GLWin.dpy, GLWin.win, &winDummy, &GLWin.x, &GLWin.y,
		&GLWin.width, &GLWin.height, &borderDummy, &GLWin.bpp);

	if (glXIsDirect(GLWin.dpy, GLWin.ctx))
		cerr << " Direct Rendering: True" << endl;
	else
		cerr << " Direct Rendering: False" << endl;

	resize();



	// build font
	XFontStruct *font;

	Settings::Instance()->fontbase = glGenLists(96);      /* storage for 96 characters */
	/* load a font with a specific name in "Host Portable Character Encoding" */

// 	     font = XLoadQueryFont(GLWin.dpy,"-*-helvetica-medium-r-normal--12-*-*-*-p-*-iso8859-1");
	//      font = XLoadQueryFont(GLWin.dpy,"-*-times-medium-r-normal--10-100-75-75-p-54-iso8859-1");
	//      font = XLoadQueryFont(GLWin.dpy,"-*-times-medium-r-normal--24-240-75-75-p-124-iso8859-1");
	//font = XLoadQueryFont(GLWin.dpy,"-*-misc-fixed-medium-r-normal--13-*-*-*-C-*-iso8859-1"); // best performance till now
// 	font = XLoadQueryFont(GLWin.dpy,"-*-screen-fixed-medium-r-normal--16-*-*-*-C-*-iso8859-1");
	font = XLoadQueryFont(GLWin.dpy,"-*-courier-medium-r-normal--14-*-*-*-p-*-iso8859-1");



	if (font == NULL)
	{
		/* this really *should* be available on every X Window System...*/
		font = XLoadQueryFont(GLWin.dpy, "fixed");
		if (font == NULL)
		{
			printf("Problems loading fonts :-(\n");
			exit(1);
		}
	}

// 	for ( unsigned int i=0; i <= 96; i++ )
// 	{
// 		cerr << "compiling" << i << endl;
// 		glNewList(Settings::Instance()->fontbase+i, GL_COMPILE);
// 	}

	/* build 96 display lists out of our font starting at char 32 */
	glXUseXFont(font->fid, 32, 96, Settings::Instance()->fontbase);
	/* free our XFontStruct since we have our display lists */
	XFreeFont(GLWin.dpy, font);
}

void GLWindow::destroy()
{
	glXMakeCurrent(GLWin.dpy, None, NULL);
	glXDestroyContext(GLWin.dpy, GLWin.ctx);
	XDestroyWindow(GLWin.dpy, GLWin.win);
	XCloseDisplay(GLWin.dpy);
}

void GLWindow::resize()
{
	if ( GLWin.height == 0 ) GLWin.height = 1;
	if ( GLWin.width == 0 ) GLWin.width = 1;
}

void GLWindow::runGLScene(GLScene &glscene)
{
	XEvent event;
	int running = 1;

	Settings::Instance()->winWidth = &GLWin.width;
	Settings::Instance()->winHeight = &GLWin.height;

	while(running)
	{
		while(XPending(GLWin.dpy) > 0)
		{
			XNextEvent(GLWin.dpy, &event);
			switch(event.type)
			{
				case Expose:
					if (event.xexpose.count != 0)
						break;
					break;
				case ConfigureNotify:
					if ((event.xconfigure.width != (int)GLWin.width) || (event.xconfigure.height != (int)GLWin.height))
					{
						GLWin.width = event.xconfigure.width;
						GLWin.height = event.xconfigure.height;
						resize();
					}
					break;
				case KeyPress:
					switch(XLookupKeysym(&event.xkey,0))
					{
 						case XK_Escape:			// Quit if windowed, windowed if fullscreen
							running = 0;
						break;
 						default:			// TODO ELSE pass event to the scene
							glscene.handlekey(XLookupKeysym(&event.xkey,0));
						break;
					}
					break;
				case KeyRelease:
					break;
				case ClientMessage:
					if (*XGetAtomName(GLWin.dpy, event.xclient.message_type) == *"WM_PROTOCOLS")
					{
						running = 0;
					}
					break;
				default:
					break;
			}
		}

		glscene.draw();
		glXSwapBuffers(GLWin.dpy, GLWin.win);
	}
}


GLWindow::~GLWindow()
{

}


