#ifndef CRITTERB_H
#define CRITTERB_H

#include "../../utils/parser.h"
#include "../../utils/randgen.h"
#include "../../brainz/brainz.h"
#include "vector3f.h"
#include "food.h"
#include "corpse.h"
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

		Brainz			brain;

		unsigned int		crittertype;

		unsigned int		adamdist;
		unsigned int		retinasize;

		unsigned int		colorNeurons;

		unsigned int		retinasperrow;

		float			size;
		float			halfsize;
		float			speedfactor;

		void			moveForward();
		void			moveBackward();
		void			moveRight();
		void			moveLeft();
		void 			rotateRight();
		void			rotateLeft();

		Vector3f		position;
		Vector3f		newposition;

		void			prepNewPoss();
		void			moveToNewPoss();
		void			calcFrustrumTriangle();

		float			rotation;
		void			calcRotSinCos();
		float			reuseRotSinX;
		float			reuseRotSinY;
		float			reuseRotCosX;
		float			reuseRotCosY;

		float			color[4];
		float			colorTrim;
		float			maxEnergyLevel;
		float			energyLevel;
		float			energyUsed;

		unsigned int		totalFrames;
		unsigned int		maxtotalFrames;

		bool			moved;
		bool			touchingFood;
		unsigned int		touchedFoodID;
		bool			touchingCorpse;
		unsigned int		touchedCorpseID;

		bool			carrydrop;

		bool			carriesFood;
		Food*			foodBeingCarried;

		bool			carriesCorpse;
		Corpse*			corpseBeingCarried;

		bool			procreate;
		bool			canProcreate;
		unsigned int		procreateTimeCount;
		unsigned int		procreateTimeTrigger;
		float			minprocenergyLevel;

		bool			fire;
		bool			canFire;
		unsigned int		fireTimeCount;
		unsigned int		fireTimeTrigger;
		float			minfireenergyLevel;
		bool			wasShot;

		unsigned char		*retina;
		unsigned int		items;
		Vector3f		cameraposition;

		float			sightrange;

		// 3 vectors for frustrum culling
		Vector3f		frustCullTriangle1;
		Vector3f		frustCullTriangle2;
		Vector3f		frustCullTriangle3;

		void			place();
		void			process();
		void			resize(float newsize);

		void			calcFramePos(unsigned int pos, unsigned int cretinasperrow);
		void			calcCamPos();
		void			printVision();
		void			calcInputOutputNeurons();
		void			setup();
		void			mutate(unsigned int maxMutateRuns, unsigned int percentChangeType);

		bool			eat;

		// variables used as caching for checking if withing sight
		float			v1x;
		float			v1z;
		float			v2x;
		float			v2z;
		float			denom;
		bool			isWithinSight(Vector3f& point);


		void			loadCritterB(string &content);
		string			saveCritterB();


	private:

		Parser			parseH;

		// frame capturing options
		unsigned int		components;
		unsigned int		framePosX;
		unsigned int		framePosY;

		float			colorDivider;
		unsigned int		retinaColumnStart;
		unsigned int		retinaRowStart;
		unsigned int		retinaRowLength;


		unsigned int		visionPosition;

		unsigned int		motorneuronsfired;

		RandGen			randgen;

		void			initConst();
		void			procInputNeurons();
		void			procOutputNeurons();
		void			createInputOutputNeurons();
};

#endif
