#ifndef CRITTERB_H
#define CRITTERB_H

#include "../../utils/parser.h"
#include "../../utils/randgen.h"
//#include "../../brain/brain.h"
#include "../../brainz/brainz.h"
#include "vector3f.h"

#include "GL/gl.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class CritterB
{
	public:
		CritterB();
		CritterB(CritterB &other);
		CritterB(string &critterstring);
		~CritterB();

//		Brain			brain;
		Brainz			brain;

		unsigned int		adamdist;
		unsigned int		frameWidth;
		unsigned int		frameHeight;

		unsigned int		retinasperrow;

		float			size;
		float			halfsize;
		float			speedfactor;

		Vector3f		position;
		Vector3f		newposition;

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
		bool			moved;
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
		void			process();
		void			resize(float newsize);

		void			calcFramePos(unsigned int pos, unsigned int cretinasperrow);
		void			calcCamPos();
		void			printVision();
		void			setup();
		void			mutate(unsigned int maxMutateRuns);

		void			moveForward();
		void			moveBackward();
		void			moveRight();
		void			moveLeft();
		void 			rotateRight();
		void			rotateLeft();
		void			prepNewPoss();
		void			moveToNewPoss();

		void			loadCritterB(string &content);
		string			saveCritterB();


	private:

		Parser			parseH;


		// frame capturing options
		unsigned int		components;
		unsigned int		framePosX;
		unsigned int		framePosY;

		unsigned int		visionDivider;
		unsigned int		colorDivider;


		unsigned int		visionPosition;

		unsigned int		motorneuronsfired;

		GLfloat 		vertices[27];
		GLubyte			indices[20];
		GLubyte			tindices[3];

		RandGen			randgen;

		void			initConst();
		void			procInputNeurons();
		void			procOutputNeurons();
		void			createInputOutputNeurons();
};

#endif
