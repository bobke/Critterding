#include "glwindow.h"

GLWindow::GLWindow()
{
}

void GLWindow::create(const char* title, int width, int height, int bpp)
{
	w_bpp = bpp;
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 4);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 4);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 4);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 4);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_WM_SetCaption(title, 0);

	w_width = width;
	w_height = height;

	Settings::Instance()->winWidth = &w_width;
	Settings::Instance()->winHeight = &w_height;

	resize();
}

void GLWindow::resize()
{
	if ( w_height == 0 ) w_height = 1;
	if ( w_width == 0 ) w_width = 1;
	SDL_SetVideoMode(w_width, w_height, w_bpp, SDL_OPENGL | SDL_RESIZABLE | SDL_DOUBLEBUF);
}

void GLWindow::runGLScene(GLScene &glscene)
{
	SDL_Event event;
	bool stop = false;

	while(!stop)
	{
// 		while(XPending(GLWin.dpy) > 0)
// 		{
// 			XNextEvent(GLWin.dpy, &event);
// 			switch(event.type)
// 			{
// 				case Expose:
// 					if (event.xexpose.count != 0)
// 						break;
// 					break;
// 				case ConfigureNotify:
// 					if ((event.xconfigure.width != (int)GLWin.width) || (event.xconfigure.height != (int)GLWin.height))
// 					{
// 						GLWin.width = event.xconfigure.width;
// 						GLWin.height = event.xconfigure.height;
// 						resize();
// 					}
// 					break;
// 				case KeyPress:
// 					switch(XLookupKeysym(&event.xkey,0))
// 					{
//  						case XK_Escape:			// Quit if windowed, windowed if fullscreen
// 							running = 0;
// 						break;
//  						default:			// TODO ELSE pass event to the scene
// 							glscene.handlekey(XLookupKeysym(&event.xkey,0));
// 						break;
// 					}
// 					break;
// 				case KeyRelease:
// 					break;
// 				case ClientMessage:
// 					if (*XGetAtomName(GLWin.dpy, event.xclient.message_type) == *"WM_PROTOCOLS")
// 					{
// 						running = 0;
// 					}
// 					break;
// 				default:
// 					break;
// 			}
// 		}
		/* Handle events with SDL. */
		if(SDL_PollEvent(&event))
		{
                        if(event.type == SDL_VIDEORESIZE)
			{
				w_width = event.resize.w;
				w_height = event.resize.h;
                                resize();
			}

			else if(event.type == SDL_QUIT)
				break;

			else if(event.type == SDL_KEYDOWN)
			{
				switch( event.key.keysym.sym )
				{
					case SDLK_ESCAPE:
						stop = true;
					break;
					default:			// TODO ELSE pass event to the scene
						glscene.handlekeyPressed( event.key.keysym.sym );
					break;
				}
			}

			else if(event.type == SDL_KEYUP)
					glscene.handlekeyReleased( event.key.keysym.sym );

			else if(event.type == SDL_MOUSEMOTION)
					glscene.handleMouseMotion( event.motion );
			
		}
		glscene.draw();
	}
        SDL_Quit();
}


GLWindow::~GLWindow()
{

}


