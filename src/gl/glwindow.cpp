#include "glwindow.h"


GLWindow::GLWindow()
{
}



void GLWindow::create(const char* title, int width, int height, int bpp, BOOL fsflag)
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
	int dpyWidth, dpyHeight;
	int i;
	int vidModeMajorVersion, vidModeMinorVersion;
	XF86VidModeModeInfo **modes;
	int modeNum;
	int bestMode;
	Atom wmDelete;
	Window winDummy;
	unsigned int borderDummy;

	GLWin.fs = fsflag;
	bestMode = 0;

	GLWin.dpy = XOpenDisplay(0);
	GLWin.screen = DefaultScreen(GLWin.dpy);
	XF86VidModeQueryVersion(GLWin.dpy, &vidModeMajorVersion, &vidModeMinorVersion);

	XF86VidModeGetAllModeLines(GLWin.dpy, GLWin.screen, &modeNum, &modes);

	GLWin.deskMode = *modes[0];

	GLWin.owidth=width; GLWin.oheight=height;

	for (i = 0; i < modeNum; i++)
	{
		if ((modes[i]->hdisplay == width) && (modes[i]->vdisplay == height))
		{
			bestMode = i;
		}
	}

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

	if(GLWin.fs)
	{
		cerr << " Running: Fullscreen" << endl;
		XF86VidModeSwitchToMode(GLWin.dpy, GLWin.screen, modes[bestMode]);
		XF86VidModeSetViewPort(GLWin.dpy, GLWin.screen, 0, 0);
		dpyWidth = modes[bestMode]->hdisplay;
		dpyHeight = modes[bestMode]->vdisplay;
		XFree(modes);
		GLWin.attr.override_redirect = True;
		GLWin.attr.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask;
		GLWin.win = XCreateWindow(GLWin.dpy, RootWindow(GLWin.dpy, vi->screen),
			0, 0, dpyWidth, dpyHeight, 0, vi->depth, InputOutput, vi->visual,
			CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect,
			&GLWin.attr);
		XWarpPointer(GLWin.dpy, None, GLWin.win, 0, 0, 0, 0, 0, 0);
		XMapRaised(GLWin.dpy, GLWin.win);
		XGrabKeyboard(GLWin.dpy, GLWin.win, True, GrabModeAsync,GrabModeAsync, CurrentTime);
		XGrabPointer(GLWin.dpy, GLWin.win, True, ButtonPressMask,
			GrabModeAsync, GrabModeAsync, GLWin.win, None, CurrentTime);
	}
	else
	{
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
	}

	glXMakeCurrent(GLWin.dpy, GLWin.win, GLWin.ctx);
	XGetGeometry(GLWin.dpy, GLWin.win, &winDummy, &GLWin.x, &GLWin.y,
		&GLWin.width, &GLWin.height, &borderDummy, &GLWin.bpp);

	if (glXIsDirect(GLWin.dpy, GLWin.ctx))
		cerr << " Direct Rendering: True" << endl;
	else
		cerr << " Direct Rendering: False" << endl;

	resize();
}


void GLWindow::destroy()
{
//	printf("Exiting\n");

	glXMakeCurrent(GLWin.dpy, None, NULL);
	glXDestroyContext(GLWin.dpy, GLWin.ctx);
	XDestroyWindow(GLWin.dpy, GLWin.win);
	XCloseDisplay(GLWin.dpy);

/*	if(GLWin.ctx)
	{
		if(!glXMakeCurrent(GLWin.dpy, None, NULL))
		{
			printf("Error releasing drawing context : GLWindow::destroy\n");
		}
		glXDestroyContext(GLWin.dpy, GLWin.ctx);
		GLWin.ctx = NULL;
	}

	if(GLWin.fs)
	{
		XF86VidModeSwitchToMode(GLWin.dpy, GLWin.screen, &GLWin.deskMode);
		XF86VidModeSetViewPort(GLWin.dpy, GLWin.screen, 0, 0);
	}
	XCloseDisplay(GLWin.dpy);*/
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

//	glscene.init();
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
							if (GLWin.fs) {
								destroy();
								GLWin.fs = !GLWin.fs;
								create("", GLWin.owidth, GLWin.oheight, GLWin.bpp, GLWin.fs);
							}
							else running = 0;
						break;
/*						case XK_F1:			// Switch Fullscreen/Windowed mode

							destroy();

							GLWin.fs = !GLWin.fs;
							create("", GLWin.owidth, GLWin.oheight, GLWin.bpp, GLWin.fs);
						break;*/
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

	//glscene.clean();

}


GLWindow::~GLWindow()
{

}


