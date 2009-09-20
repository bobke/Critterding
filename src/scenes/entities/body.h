#ifndef BODY_H
#define BODY_H

#include "../../utils/timer.h"
#include "../../utils/randgen.h"
#include "../../utils/parser.h"
#include "../../utils/settings.h"
#include "archbodypart.h"
#include "bodypart.h"
#include "archconstraint.h"
#include "constraint.h"
#include "archmouth.h"
#include "mouth.h"
#include "GL/gl.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <sstream>
#include "btBulletDynamicsCommon.h"

using namespace std;

class Body
{
	public:
		Body();
		~Body();

		vector<Bodypart*>	bodyparts;
		void			addBodyPart_Capsule(void* owner, float width, float height, float weight, btTransform& offset, btTransform& transform);
		void			addBodyPart_Box(void* owner, float x, float y, float z, float weight, btTransform& offset, btTransform& transform);

		vector<Mouth*>		mouths;
		void			addMouth(void* owner, float x, float y, float z, float weight, btTransform& offset, btTransform& transform);
		
		vector<Constraint*>	constraints;
		void			addConstraint(unsigned int bodypartID1, unsigned int bodypartID2, btTransform& localA, btTransform& localB, double limitA, double limitB);
		void			addConeTwistConstraint(unsigned int bodypartID1, unsigned int bodypartID2, btTransform& localA, btTransform& localB, double limitA, double limitB, double limitC);
		void			add6DConstraint(unsigned int bodypartID1, unsigned int bodypartID2, btTransform& localA, btTransform& localB, const btVector3& lowerLimit, const btVector3& upperLimit);
		void			addMouthConstraint(unsigned int mouthID, unsigned int bodypartID, btTransform& localA, btTransform& localB, double limitA, double limitB);

		void 			motorateExpand(unsigned int constraintID);
		void 			motorateContract(unsigned int constraintID);

		// load save architecture (serialize)
		void			buildArch();
		void			setArch(string* content);
		string*			getArch();
		void			copyFrom(const Body& otherBody);
		void			wireArch(void* owner, btDynamicsWorld* ownerWorld, const btVector3& startOffset);
		void			mutate(unsigned int runs);

		vector<archBodypart>	archBodyparts;
		vector<archConstraint>	archConstraints;
		vector<archMouth>	archMouths;

		btDynamicsWorld* 	m_ownerWorld;
		float			totalWeight;

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
		int			findBodypart(unsigned int id);
		int			findMouth( unsigned int id );

		string			archBuffer;
};
#endif
