#ifndef CRITTERB_H
#define CRITTERB_H

#include "btBulletDynamicsCommon.h"
#include "GL/gl.h"

#include "../../utils/parser.h"
#include "../../utils/randgen.h"
#include "../../brainz/brainz.h"
#include "../../utils/settings.h"
#include "../../utils/displaylists.h"
#include "../../utils/raycast.h"
#include "entity.h"
#include "body.h"
#include "food.h"
// #include <cmath>
// #include <vector>
// #include <iostream>
// #include <sstream>

using namespace std;

class CritterB : public Entity
{
	public:
		CritterB(btDynamicsWorld* btWorld, long unsigned int id, const btVector3& startPos, unsigned char* retinap);
		CritterB(CritterB& , long unsigned int id, const btVector3& startPos, bool brainmutant, bool bodymutant);
		CritterB(string &critterstring, btDynamicsWorld* btWorld, const btVector3& startPos, unsigned char* retinap);
		~CritterB();

		Brainz			brain;
		Body			body;
		inline void		registerBrainInputOutputs();
		void			draw(bool drawFaces);
		void			move();
		
		bool			eaten;
		
		unsigned long		critterID;

		unsigned int		adamdist;
		btScalar		position[16];

/*		float			color[3];*/
		float			speciescolor[3];
		float			colorTrim;

// 		unsigned int		lifetime;
		float			energyLevel;
		float			energyUsed;
		unsigned int		totalFrames;

		// Inputs
		bool			canProcreate;
		bool			touchingFood;
// 		Food*			touchedFoodID;
		bool			touchingCritter;
// 		CritterB*		touchedCritterID;
		Entity*			touchedEntity;

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
		unsigned int		components;
// 		float			sightrange;
		float			straal;
		unsigned char		*retina;
		unsigned int		items;
		void			place();
		void			calcFramePos(unsigned int pos);
		void			printVision();
		
		float			fitness_index;

	private:

		Settings		*settings;
		Raycast*		raycast;
		castResult		mouseRay;

// 		unsigned int		motorneuronsfired;
		unsigned int		movementsmade;

		btDynamicsWorld*	btDynWorld;

		btVector3 getScreenDirection(const int& x, const int& y);

		inline void		initConst();
		inline void		procInputNeurons();
		inline void		createInputOutputNeurons();

		inline void		mutateBody();
		inline void		mutateBrain();

		// Vision
			unsigned int		framePosX;
			unsigned int		framePosY;
			unsigned int		retinaColumnStart;
			unsigned int		retinaRowStart;
			unsigned int		retinaRowLength;
			unsigned int		visionPosition;

		// Settings pointers.. performance
			const unsigned int*	retinasperrow;
			const unsigned int*	critter_maxlifetime;
			const unsigned int*	critter_maxenergy;
			const unsigned int*	critter_sightrange;
			const unsigned int*	critter_procinterval;
			const unsigned int*	critter_minenergyproc;
			const unsigned int*	critter_raycastvision;

			const unsigned int*	brain_costhavingneuron;
			const unsigned int*	brain_costfiringneuron;
			const unsigned int*	brain_costfiringmotorneuron;
			const unsigned int*	brain_costhavingsynapse;
};

#endif
