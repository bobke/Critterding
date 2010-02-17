#ifndef BODY_H
#define BODY_H

// #include "../../utils/timer.h"
// #include "../../utils/randgen.h"
// #include "../../utils/parser.h"
// #include "../../utils/settings.h"
#include "bodyarch.h"
#include "bodypart.h"
#include "constraint.h"
#include "mouth.h"
#include "GL/gl.h"
// #include <cmath>
#include <vector>
#include <iostream>
// #include <sstream>
#include "btBulletDynamicsCommon.h"

using namespace std;

class Body
{
	public:
		Body();
		~Body();

		void			wireArch(BodyArch* bodyArch, void* owner, btDynamicsWorld* ownerWorld, const btVector3& startOffset);
		vector<Bodypart*>	bodyparts;
// 		void			addBodyPart_Capsule(void* owner, float width, float height, float weight, btTransform& offset, btTransform& transform);
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

		btDynamicsWorld* 	m_ownerWorld;
		float			totalWeight;
	private:
};
#endif
