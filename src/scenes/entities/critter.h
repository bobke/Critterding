#ifndef CRITTER_H
#define CRITTER_H

#include "../../utils/parser.h"
#include "vector3f.h"
#include "randgen.h"
#include "neuronsensor.h"
#include "neuroninter.h"
#include "archneuron.h"

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
		~Critter();

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
		vector<ArchNeuron*>	NeuronArch;
		unsigned int		totalneurons;
		unsigned int		totalconnections;
		unsigned char		*outputImage;
		unsigned int		items;

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
		void			randomArchitecture();
		void			prepNewPoss();
		void			moveToNewPoss();

		void			setArch(string &content);
		string			getArch();
		void			doNeuronConnCount();


	private:

		Parser			parseH;

		// frame capturing options
		float			maxSize;
		float			speedfactor;
		unsigned int		components;
		unsigned int		framePosX;
		unsigned int		framePosY;
		unsigned int		percentSensoryConns;
		unsigned int		percentMotor;
		unsigned int		absmaxneurons;
		unsigned int		absmaxconns;
		unsigned int		minneurons;
		unsigned int		maxneurons;
		unsigned int		minconns;
		unsigned int		maxconns;
		unsigned int		mutatepercent;
		unsigned int		itemsPerRow;

		unsigned int		visionDivider;
		Vector3f		cameraposition;

		bool			moved;

		GLfloat 		vertices[27];
		GLubyte			indices[24];
		GLubyte			tindices[3];

		vector<NeuronSensor*>	SensorNeurons;
		vector<NeuronInter*>	Neurons;

		RandGen			randgen;
		unsigned int		addRandomArchConnection(unsigned int parentneuron);
		unsigned int		addRandomArchNeuron();
		
		void			procSensorNeurons();
		void			procNeurons();
		void			setupSensors();
		void			setupArchitecture();
		void			resizeByArch();


};

#endif
