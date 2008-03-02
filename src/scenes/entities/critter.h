#ifndef CRITTER_H
#define CRITTER_H

#include "../../utils/parser.h"
#include "../../utils/randgen.h"
#include "vector3f.h"
#include "../../brain/brain.h"

//#include "brain/neuronsensor.h"
//#include "brain/neuroninter.h"
//#include "brain/archneuron.h"

#include "GL/gl.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class Critter
{
	public:
		Critter();
		Critter(Critter &other);
		Critter(string &critterstring);
		~Critter();

		Brain			brain;

		unsigned int		adamdist;
		unsigned int		frameWidth;
		unsigned int		frameHeight;

		int			drawEvery;
		int			drawedAgo;

		float			size;
		float			halfsize;
		float			volume;

		Vector3f		position;
		Vector3f		newposition;
		pthread_mutex_t		position_mutex;

		float			rotation;
		float			color[4];
		float			maxEnergyLevel;
		float			energyLevel;
		float			energyUsed;

		unsigned int		totalFrames;
		unsigned int		maxtotalFrames;

		unsigned int		procreateTimeCount;
		unsigned int		procreateTimeTrigger;
		float			minprocenergyLevel;

		unsigned int		fireTimeCount;
		unsigned int		fireTimeTrigger;
		float			minfireenergyLevel;

		bool			eat;
		bool			touchingFood;
		unsigned int		touchedFoodID;
		bool			fire;
		bool			canFire;
		bool			procreate;
		bool			canProcreate;
		bool			wasShot;
		unsigned char		*retina;
		unsigned int		items;
		Vector3f		cameraposition;

		void			draw();
		void			place();
		void			procFrame();
		void			process();
		void			resize(float newsize);

		void			calcFramePos(unsigned int pos);
		void			calcCamPos();
		void			printVision();
		void			setup();
		void			mutate();

		void			moveForward();
		void			moveBackward();
		void			moveRight();
		void			moveLeft();
		void 			rotateRight();
		void			rotateLeft();
		void			prepNewPoss();
		void			moveToNewPoss();

		void			loadCritter(string &content);
		string			saveCritter();


	private:

		Parser			parseH;

		// frame capturing options
		float			maxSize;
		float			speedfactor;
		unsigned int		components;
		unsigned int		framePosX;
		unsigned int		framePosY;

		unsigned int		visionDivider;

		bool			moved;
		unsigned int		motorneuronsfired;

		GLfloat 		vertices[27];
		GLubyte			indices[20];
		GLubyte			tindices[3];

		RandGen			randgen;

		void			initConst();
		void			initInputOutputs();
		void			procInputNeurons();
		void			procOutputNeurons();
		void			createInputOutputNeurons();
};

#endif
