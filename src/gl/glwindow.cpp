#include "glwindow.h"

GLWindow::GLWindow()
{
}

void GLWindow::create(const char* title, int width, int height)
{

	if( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		cerr << "Video initialization failed: " << SDL_GetError() << endl;
		exit(1);
	}
	vidInfo = SDL_GetVideoInfo();
	
	w_bpp = vidInfo->vfmt->BitsPerPixel;
	
	if ( !vidInfo )
	{
		cerr << "Cannot get video information: " <<  SDL_GetError() << endl;
		exit(1);
	}

	vidFlags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE;

	hwaccel = false;
	if( vidInfo->hw_available )
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
// 	SDL_WM_SetIcon(SDL_LoadBMP("other files/critterding icon.png"), 0);
// 	SDL_WM_SetIcon(SDL_LoadBMP("other files/cd.bmp"), 0);
	string pixmappath = Settings::Instance()->binarypath;
	pixmappath.append( "../share/critterding/pixmaps/cd.bmp" );
	SDL_WM_SetIcon(SDL_LoadBMP(pixmappath.c_str()), 0);
// 	SDL_WM_SetIcon(SDL_LoadBMP("/projects/lessons/lesson20/data/image2.bmp"), 0);

	w_width = width;
	w_height = height;
	n_width = width;
	n_height = height;

	Settings::Instance()->winWidth = &w_width;
	Settings::Instance()->winHeight = &w_height;

	settingsfs = Settings::Instance()->getCVarPtr("fullscreen");

	fs = *settingsfs;

	if ( fs == 1 )
		surface = SDL_SetVideoMode( w_width, w_height, w_bpp, vidFlags | SDL_FULLSCREEN );
	else
		surface = SDL_SetVideoMode( w_width, w_height, w_bpp, vidFlags | SDL_RESIZABLE );

	cerr << "SDL: subsystem initialized\n";
// 	cerr << "Video " << front.width() << "x" << front.height() << "x" << int(front.getSurface()->format->BitsPerPixel) << "\n";
// 	cerr << "Render Mode: " <<  ((hwaccel) ? "Direct Rendering" : "Software Rendering")   << "\n";
// 	cerr << "Hardware Blit Acceleration: " << ((vidInfo->blit_hw) ? "Yes": "No") << "\n";
}

void GLWindow::resize()
{
	if ( w_height == 0 ) w_height = 1;
	if ( w_width == 0 ) w_width = 1;

#ifndef _WIN32
	SDL_FreeSurface(surface);
	surface = SDL_SetVideoMode( w_width, w_height, w_bpp, vidFlags | SDL_RESIZABLE );
#endif
}

void GLWindow::toggleFs()
{
	if ( fs )
	{
		if ( w_height == 0 ) w_height = 1;
		if ( w_width == 0 ) w_width = 1;

		SDL_FreeSurface(surface);
		n_width = w_width;
		n_height = w_height;
		w_width = Settings::Instance()->getCVar("fsX");
		w_height = Settings::Instance()->getCVar("fsY");

		surface = SDL_SetVideoMode( w_width, w_height, w_bpp, vidFlags | SDL_FULLSCREEN );
		Displaylists::Instance()->generateList();
		Textprinter::Instance()->setUpFonts();
	}
	else
	{
		SDL_FreeSurface(surface);
		w_width = n_width;
		w_height = n_height;

		surface = SDL_SetVideoMode( w_width, w_height, w_bpp, vidFlags | SDL_RESIZABLE );

		Displaylists::Instance()->generateList();
		Textprinter::Instance()->setUpFonts();
	}
}

void GLWindow::runGLScene(GLScene* glscene)
{
	bool stop = false;

	while(!stop)
	{
		if ( fs != *settingsfs )
		{
			fs = *settingsfs;
			toggleFs();
		}

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
				glscene->handlekeyPressed( event.key.keysym.sym );

			else if(event.type == SDL_KEYUP)
				glscene->handlekeyReleased( event.key.keysym.sym );

			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
// 				SDL_GetMouseState(&mousex, &mousex);
				glscene->handlemousebuttonPressed( event.button.button );
			}

			else if (event.type == SDL_MOUSEBUTTONUP)
			{
// 				SDL_GetMouseState(&mousex, &mousex);
				glscene->handlemousebuttonReleased( event.button.button );
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
	exit(0);
}


GLWindow::~GLWindow()
{

}


