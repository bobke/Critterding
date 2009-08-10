#ifndef CRITTERB_H
#define CRITTERB_H

#include "btBulletDynamicsCommon.h"
#include "GL/gl.h"

#include "../../utils/parser.h"
#include "../../utils/randgen.h"
#include "../../brainz/brainz.h"
#include "../../utils/settings.h"
#include "../../utils/displaylists.h"
#include "vector3f.h"
#include "body.h"
#include "food.h"
// #include <cmath>
// #include <vector>
// #include <iostream>
// #include <sstream>

using namespace std;

class CritterB
{
	public:
		CritterB(btDynamicsWorld* btWorld, long unsigned int id, const btVector3& startPos, unsigned char* retinap);
		CritterB(CritterB &other, long unsigned int id, const btVector3& startPos, bool mutant);
		CritterB(string &critterstring, btDynamicsWorld* btWorld, const btVector3& startPos, unsigned char* retinap);
		~CritterB();

		unsigned int		type;
		Brainz			brain;
		Body			body;
// 		void			createBodyOld(btDynamicsWorld* m_dynamicsWorld, const btVector3& startOffset);
// 		void			createArchBody();
// 		void			createBody(const btVector3& startOffset);
		inline void		registerBrainInputOutputs();
		void			draw(bool drawFaces);
		void			move();
		
		unsigned long		critterID;

		unsigned int		adamdist;
		btScalar		position[16];

		float			color[3];
		float			speciescolor[3];
		float			colorTrim;

// 		unsigned int		lifetime;
		float			energyLevel;
		float			energyUsed;
		unsigned int		totalFrames;

		// Inputs
		bool			canProcreate;
		bool			touchingFood;
		Food*			touchedFoodID;

		// Motor Func
 		bool			eat;
  		bool			procreate;

		unsigned int		procreateTimeCount;
		unsigned int		procreateTimeTrigger;

		void			process();

		void			loadCritterB(string &content);
		string			saveCritterB();

		// Vision
		unsigned int		retinasize;
// 		float			sightrange;
		float			straal;
		unsigned char		*retina;
		unsigned int		items;
		Vector3f		cameraposition;
		void			place();
		void			calcFramePos(unsigned int pos);
		bool			isWithinSight(Vector3f& point);

	private:

		Settings		*settings;

// 		unsigned int		motorneuronsfired;
		unsigned int		movementsmade;

		btDynamicsWorld*	btDynWorld;

		inline void		initConst();
		inline void		procInputNeurons();
		inline void		createInputOutputNeurons();

		inline void		mutateBody();
		inline void		mutateBrain();

		// Vision
			unsigned int		components;
			unsigned int		framePosX;
			unsigned int		framePosY;
			unsigned int		retinaColumnStart;
			unsigned int		retinaRowStart;
			unsigned int		retinaRowLength;
			unsigned int		visionPosition;

};

#endif
