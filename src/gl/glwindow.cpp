#include "glwindow.h"

GLWindow::GLWindow()
{
}

void GLWindow::create(const char* title, int width, int height, int bpp)
{

	if( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		cerr << "Video initialization failed: " << SDL_GetError() << endl;
		exit(1);
	}
	vidInfo = SDL_GetVideoInfo();
	
	w_bpp = vidInfo->vfmt->BitsPerPixel;
// 	w_bpp = 8;
	
	if ( !vidInfo )
	{
		cerr << "Cannot get video information: " <<  SDL_GetError() << endl;
		exit(1);
	}

	vidFlags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE;

	hwaccel = false;
	if( vidInfo->hw_available != 0 )
	{
		hwaccel = true;
		vidFlags |= SDL_HWSURFACE;
	}
	else
		vidFlags |= SDL_SWSURFACE;

        if( vidInfo->blit_hw != 0 )
                vidFlags |= SDL_HWACCEL;

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 4);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 4);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 4);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 4);
// 	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_WM_SetCaption(title, 0);

	w_width = width;
	w_height = height;

	n_width = width;
	n_height = height;

	Settings::Instance()->winWidth = &w_width;
	Settings::Instance()->winHeight = &w_height;

	settingsfs = Settings::Instance()->getCVarPtr("fullscreen");

	fs = *settingsfs;

	surface=0;
	resize();

	cerr << "SDL: subsystem initalized\n";
// 	cerr << "Video " << front.width() << "x" << front.height() << "x" << int(front.getSurface()->format->BitsPerPixel) << "\n";
	cerr << "Render Mode: " <<  ((hwaccel) ? "Direct Rendering" : "Software Rendering")   << "\n";
	cerr << "Hardware Blit Acceleration: " << ((vidInfo->blit_hw) ? "Yes": "No") << "\n";
}

void GLWindow::resize()
{
	if ( w_height == 0 ) w_height = 1;
	if ( w_width == 0 ) w_width = 1;

	if ( fs )
	{
		SDL_FreeSurface(surface);
		n_width = w_width;
		n_height = w_height;
		w_width = Settings::Instance()->getCVar("fsX");
		w_height = Settings::Instance()->getCVar("fsY");

		surface = SDL_SetVideoMode( w_width, w_height, w_bpp, vidFlags | SDL_FULLSCREEN );
/*		surface = SDL_SetVideoMode( w_width, w_height, w_bpp, SDL_OPENGL | SDL_DOUBLEBUF | SDL_ANYFORMAT | SDL_FULLSCREEN );*/
	}
	else
	{
#ifdef _WIN32
		if ( surface != 0 )
		{
			SDL_Init(SDL_INIT_VIDEO);

			SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 4);
			SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 4);
			SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 4);
			SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 4);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		}
		else
			surface = SDL_SetVideoMode( w_width, w_height, w_bpp, SDL_OPENGL | SDL_RESIZABLE | SDL_DOUBLEBUF | SDL_ANYFORMAT );
#else
		SDL_FreeSurface(surface);
		surface = SDL_SetVideoMode( w_width, w_height, w_bpp, vidFlags | SDL_RESIZABLE );
// 		surface = SDL_SetVideoMode( w_width, w_height, w_bpp, SDL_OPENGL | SDL_RESIZABLE | SDL_DOUBLEBUF | SDL_ANYFORMAT );
#endif
	}


}

void GLWindow::runGLScene(GLScene* glscene)
{
	SDL_Event event;
	bool stop = false;

	while(!stop)
	{
		int x, y;
		while(SDL_PollEvent(&event))
		{
                        if(event.type == SDL_VIDEORESIZE)
			{
				w_width = event.resize.w;
				w_height = event.resize.h;
                                resize();
			}

			else if(event.type == SDL_QUIT)
				stop = true;

			else if(event.type == SDL_KEYDOWN)
			{
// 				switch( event.key.keysym.sym )
// 				{
// 					case SDLK_ESCAPE:
// 						stop = true;
// 					break;
// 					default:
						glscene->handlekeyPressed( event.key.keysym.sym );
// 					break;
// 				}

				// fullscreen change
				if ( fs != *settingsfs )
				{
					fs = *settingsfs;
					
					if ( !fs )
					{
						w_width = n_width;
						w_height = n_height;
					}
					resize();
				}

			}
			else if(event.type == SDL_KEYUP)
				glscene->handlekeyReleased( event.key.keysym.sym );

			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				SDL_GetMouseState(&x, &y);
				glscene->handlemousebuttonPressed( x, y, event.button.button );
			}
			else if (event.type == SDL_MOUSEBUTTONUP)
			{
				SDL_GetMouseState(&x, &y);
				glscene->handlemousebuttonReleased( x, y, event.button.button );
			}
			else if(event.type == SDL_MOUSEMOTION)
			{
				glscene->handleMouseMotionRel( event.motion.xrel, event.motion.yrel );
				glscene->handleMouseMotionAbs( event.motion.x, event.motion.y );
			}
		}

		glscene->draw();
	}
        SDL_Quit();
}


GLWindow::~GLWindow()
{

}


