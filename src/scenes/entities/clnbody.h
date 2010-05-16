#ifndef CLNBODY_H
#define CLNBODY_H

#include "../../cl/clcontext.h"

#include "../../utils/dir.h"
#include "../../utils/file.h"
#include "../../utils/dirlayout.h"
#include "../../utils/randgen.h"

using namespace std;

class CLNBody
{
	public:
		CLNBody();
		~CLNBody();
		void		process();
		void		draw();

	private:
		CLContext*		cl;
		cl_kernel kernel;

		int numBodies;
		cl_int numParticles;
		cl_float* initPos;                  /**< initial position */
		cl_float* initVel;                  /**< initial velocity */
		cl_float* pos;                      /**< Output position */
		cl_float* vel;                      /**< Output velocity */
		cl_float delT;                      /**< dT (timestep) */
		cl_float espSqr;                    /**< Softening Factor*/
		cl_mem updatedPos;                  /**< Position of particles */
		cl_mem updatedVel;                  /**< Velocity of particles */
		cl_float* refPos;                   /**< Reference position */
		cl_float* refVel;                   /**< Reference velocity */

		RandGen*		randgen;
};

#endif
