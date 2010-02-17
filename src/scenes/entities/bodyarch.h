#ifndef BODYARCH_H
#define BODYARCH_H

#include "../../utils/randgen.h"
#include "../../utils/parser.h"
#include "../../utils/settings.h"
#include "archbodypart.h"
// #include "bodypart.h"
#include "archconstraint.h"
// #include "constraint.h"
#include "archmouth.h"
// #include "mouth.h"
// #include "GL/gl.h"
// #include <cmath>
#include <vector>
#include <iostream>
#include <sstream>
// #include "btBulletDynamicsCommon.h"

using namespace std;

class BodyArch
{
	public:
		BodyArch();
		~BodyArch();

		// load save architecture (serialize)
		void			buildArch();
		void			setArch(string* content);
		string*			getArch();
		void			copyFrom(const BodyArch* otherBody);
		void			mutate(unsigned int runs);

		vector<archBodypart>	archBodyparts;
		vector<archConstraint>	archConstraints;
		vector<archMouth>	archMouths;

		float			totalWeight;

		int			findBodypart(unsigned int id);
		int			findMouth( unsigned int id );
	private:
		Parser			*parseH;
		RandGen			*randgen;
		Settings		*settings;

		float			bodypartspacer;
		void			repositiontoConstraints( archBodypart* bp );
		void			repositiontoConstraints( archMouth* bp );
		// mutation helpers
		void			addRandomMouth();
		void			addRandomBodypart();
		void			addRandomConstraint(unsigned int connID1, unsigned int connID2, bool isMouth);
		void			removeBodypart(unsigned int id);
		void			removeMouth(unsigned int id);
		void			randomConstraintPosition(archConstraint* co, unsigned int OneOrTwo, unsigned int connID);

		unsigned int		getUniqueBodypartID();
		unsigned int		getUniqueConstraintID();

		string			archBuffer;
};
#endif
