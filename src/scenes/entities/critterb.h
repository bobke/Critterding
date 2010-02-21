#ifndef CRITTERB_H
#define CRITTERB_H

#include "btBulletDynamicsCommon.h"
#include "GL/gl.h"

#include "../../utils/parser.h"
#include "../../brainz/brainz.h"
#include "../../utils/settings.h"
#include "../../utils/displaylists.h"
#include "../../utils/raycast.h"
#include "../../utils/color.h"
#include "genotypes.h"
#include "entity.h"
#include "body.h"

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
		Genotype*		genotype;
		inline void		registerBrainInputOutputs();
		void			draw(bool drawFaces);
		void			move();
		
		bool			eaten;
		
		unsigned long		critterID;

// 		unsigned int		adamdist;
		btScalar		position[16];

// 		float			speciescolor[3];
// 		float			colorTrim;

		float			energyLevel;
		float			energyUsed;
		unsigned int		totalFrames;

		// Inputs
		bool			canProcreate;
		bool			touchingFood;
		bool			touchingCritter;
		Entity*			touchedEntity;

		// Motor Func
 		bool			eat;
  		bool			procreate;

		unsigned int		procreateTimeCount;
		unsigned int		procreateTimeTrigger;

		void			process();

		// Vision
// 		unsigned int		components;
		float			straal;
		unsigned char		*retina;
		unsigned int		items;
		void			place();
		void			calcFramePos(unsigned int pos);
		void			printVision();
		
		float			fitness_index;

		vector<unsigned int>	crittersWithinRange;
		
	private:

		Settings*		settings;
		Genotypes*		genotypes;
		Raycast*		raycast;
		castResult		mouseRay;

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
