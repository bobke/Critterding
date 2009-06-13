#ifndef CRITTERB_H
#define CRITTERB_H

#include "../../utils/parser.h"
#include "../../utils/randgen.h"
#include "../../brainz/brain.h"
#include "../../brainz/brainz.h"
#include "../../utils/settings.h"
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

		unsigned long		critterID;

		unsigned int		crittertype;

		unsigned int		adamdist;
		unsigned int		retinasize;

		float			sightrange;

		float			size;
		float			halfsize;
		float			straal;
		float			speedfactor;
		Vector3f		position;
		Vector3f		newposition;

		float			color[3];
		float			nosecolor[3];
		float			speciescolor[3];
		float			colorTrim;

		unsigned int		lifetime;
		float			energyLevel;
		float			energyUsed;
		unsigned int		totalFrames;

		// Inputs
		bool			touchingFood;
		bool			touchingCorpse;
		bool			carriesFood;
		bool			carriesCorpse;
		bool			canProcreate;
		bool			canFire;

		// Motor Func
		void			moveForward();
		void			moveBackward();
		void			moveRight();
		void			moveLeft();
		void 			rotateRight();
		void			rotateLeft();
		bool			eat;
		bool			procreate;
		bool			carrydrop;
		bool			fire;

		void			prepNewPoss();
		void			moveToNewPoss();
		void			calcFrustrumTriangle();

		float			rotation;
		void			calcRotSinCos();
		float			reuseRotSinX;
		float			reuseRotSinY;
		float			reuseRotCosX;
		float			reuseRotCosY;

		bool			moved;
		unsigned int		touchedFoodID;
		unsigned int		touchedCorpseID;
		Food*			foodBeingCarried;
		Corpse*			corpseBeingCarried;

		unsigned int		procreateTimeCount;
		unsigned int		procreateTimeTrigger;

		unsigned int		fireTimeCount;
		unsigned int		fireTimeTrigger;
		bool			wasShot;

		unsigned char		*retina;
		unsigned int		items;
		Vector3f		cameraposition;

		void			place();
		void			process();
		void			resize(float newsize);

		void			setRotation(unsigned int r);
		void			calcFramePos(unsigned int pos);
		void			calcCamPos();
		void			printVision();
		void			mutate();

		// 3 vectors for frustrum culling
		Vector3f		frustCullTriangle1;
		Vector3f		frustCullTriangle2;
		Vector3f		frustCullTriangle3;

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

		Settings		*settings;
		Parser			*parseH;
		RandGen			*randgen;
		//RandGen			randgen;

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
		unsigned int		movementsmade;

		void			initConst();
		void			procInputNeurons();
		void			procOutputNeurons();
		void			createInputOutputNeurons();
		void			determineNoseColor();
};

#endif
