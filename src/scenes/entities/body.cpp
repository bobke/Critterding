#include "body.h"

Body::Body()
{
	settings = Settings::Instance();
	totalWeight = 0.0f;
	bodypartspacer = 2.2f;
}

void Body::addBodyPart_Capsule(void* owner, float width, float height, float weight, btTransform& offset, btTransform& transform)
{
/*	Bodypart *b = new Bodypart(m_ownerWorld);
	bodyparts.push_back( b );

	b->shape = new btCapsuleShape(width, height);

	btVector3 localInertia(0,0,0);
	if (weight != 0.f) // weight of non zero = dynamic
		b->shape->calculateLocalInertia(weight,localInertia);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(offset*transform);
	
	btRigidBody::btRigidBodyConstructionInfo rbInfo(weight,myMotionState,b->shape,localInertia);
	b->body = new btRigidBody(rbInfo);

	m_ownerWorld->addRigidBody(b->body);

 	b->body->setUserPointer(owner);
	b->body->setDamping(0.05, 0.85);
	b->body->setDeactivationTime(0.001);
	b->body->setSleepingThresholds(1.6, 2.5);*/
}

void Body::addBodyPart_Box(void* owner, float x, float y, float z, float weight, btTransform& offset, btTransform& transform)
{
	totalWeight += weight;
	Bodypart *b = new Bodypart(
		m_ownerWorld,
		owner,
		btVector3( x, y, z ),
		weight,
		offset,
		transform
	);
	bodyparts.push_back( b );
}

void Body::addMouth(void* owner, float x, float y, float z, float weight, btTransform& offset, btTransform& transform)
{
	totalWeight += weight;

	Mouth *m = new Mouth(
		m_ownerWorld,
		owner,
		btVector3( x, y, z ),
		weight,
		offset,
		transform
	);
	mouths.push_back( m );

	// connect mouth and body, for some reason this segfaults in the constructor
	m->connectMouthAndBody();
}

void Body::addConstraint(unsigned int bodypartID1, unsigned int bodypartID2, btTransform& localA, btTransform& localB, double limitA, double limitB)
{
	Constraint *c = new Constraint(
		m_ownerWorld,
		*bodyparts[bodypartID1]->body,
		*bodyparts[bodypartID2]->body,
		localA, localB,
		limitA, limitB
	);
	constraints.push_back( c );
}

void Body::addMouthConstraint(unsigned int bodypartID, unsigned int mouthID, btTransform& localA, btTransform& localB, double limitA, double limitB)
{
	Constraint *c = new Constraint(m_ownerWorld,
		*bodyparts[bodypartID]->body,
		*mouths[mouthID]->body,
		localA, localB,
		limitA, limitB
	);
	constraints.push_back( c );
}


void Body::buildArch()
{
// 	string original;
// 	original.append("b 99999 box 0 75 75 200\n");
// 	original.append("b 99998 box 0 75 75 200\n");
// 	original.append("b 99997 box 0 75 75 200\n");
// 	original.append("m 99999 50, 50, 100\n");
// 	original.append("c 99999 99998 99999 1.5707 0 0 0 0 -0.25 -0.7853 99998 1.5707 0 0 0 0 0.25 0.7853\n");
// 	original.append("c 99997 99996 99998 1.5707 0 0 0 0 -0.25 -0.7853 99997 1.5707 0 0 0 0 0.25 0.7853\n");
// 	original.append("cm 99995 99994 99997 0 1.5707 0 0 0 -0.15 -0.7853 99999 0 1.5707 0 0 0 0.25 0.7853\n");
// 	setArch(&original);

// 	string fourlegged;
// 	// body
// 	fourlegged.append("b 99999 box 0 200 100 400\n");
// 	// 4 long legs
// 	fourlegged.append("b 99998 box 0 150 40 40\n");
// 	fourlegged.append("b 99997 box 0 150 40 40\n");
// 	fourlegged.append("b 99996 box 0 150 40 40\n");
// 	fourlegged.append("b 99995 box 0 150 40 40\n");
// 	// mouth
// 	fourlegged.append("m 99999 50, 50, 100\n");
// 	// connections
// 	fourlegged.append("c 99999 99998 99999 0 0 0.7853 -0.2 0 -0.325 -0.7853 99998 0 0 0 0.25 0 0 0.7853\n");
// 	fourlegged.append("c 99997 99996 99999 0 0 0.7853 -0.2 0 0.325 -0.7853 99997 0 0 0 0.25 0 0 0.7853\n");
// 	fourlegged.append("c 99995 99994 99999 0 0 -0.7853 0.2 0 -0.325 -0.7853 99996 0 0 0 -0.25 0 0 0.7853\n");
// 	fourlegged.append("c 99993 99992 99999 0 0 -0.7853 0.2 0 0.325 -0.7853 99995 0 0 0 -0.25 0 0 0.7853\n");
// 	fourlegged.append("cm 99991 99990 99999 1.5707 0 0 0 0 -0.15 -0.3926 99999 1.5707 0 0 0 0 0.45 0.3926\n");
// 	setArch(&fourlegged);



// 	string original;
// 	original.append("b 1000 box 0 200 200 200\n");
// 	original.append("b 1001 box 0 100 100 100\n");
// 	original.append("b 1002 box 0 100 100 100\n");
// 	original.append("b 1003 box 0 100 100 100\n");
// 	original.append("b 1004 box 0 100 100 100\n");
// 	original.append("m 99999 50, 50, 100\n");
// 
// 	-x
// 	original.append("c 1000 1001 1000 0.5707 1.3707 0.7707 -0.3 0 0 -0.7853 1001 1.1707 0.0707 0.5707 0.15 0 0 0.7853\n");
// 	-z
// 	original.append("c 1002 1003 1000 1.5707 1.5707 1.5707 0 0 -0.3 -0.7853 1002 1.5707 1.5707 1.5707 0 0 0.15 0.7853\n");
// 	+z
// 	original.append("c 1004 1005 1000 1.5707 0 0 0 0 0.3 -0.7853 1003 1.5707 0 0 0 0 -0.15 0.7853\n");
// 	+x
// 	original.append("c 1006 1007 1000 1.5707 0 0 0.3 0 0 -0.7853 1004 1.5707 0 0 -0.15 0 0 0.7853\n");
// 	setArch(&original);

	// Create a central body
		archBodyparts.push_back( archBodypart() );
		archBodypart *bp = &archBodyparts[archBodyparts.size()-1];
		bp->id		= 1000;
		bp->type	= 0;
		bp->materialID	= 0;
		bp->x		= randgen->Instance()->get( settings->getCVar("body_minbodypartsize"), settings->getCVar("body_maxbodypartsize") );
		bp->y		= randgen->Instance()->get( settings->getCVar("body_minbodypartsize"), settings->getCVar("body_maxbodypartsize") );
		bp->z		= randgen->Instance()->get( settings->getCVar("body_minbodypartsize"), settings->getCVar("body_maxbodypartsize") );

		unsigned int runs = randgen->Instance()->get( 0, settings->getCVar("body_maxbodypartsatbuildtime")-1 ); // -1 -> central bodypart
		for ( unsigned int i=0; i < runs; i++ )
			addRandomBodypart();

		addRandomMouth();
}

void Body::wireArch(void* owner, btDynamicsWorld* ownerWorld, const btVector3& startOffset)
{
	m_ownerWorld = ownerWorld;
	
	btTransform offset;
	offset.setIdentity();
	offset.setOrigin(startOffset);

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin( btVector3( 0.0f, 0.0f, 0.0f ) );

	for ( unsigned int i=0; i < archBodyparts.size(); i++ )
	{
		archBodypart *bp = &archBodyparts[i];

		// BOX
		if ( bp->type ==0 )
		{
			// calculate weight
			float weight = ((bp->x*bp->y*bp->z)/1000) * 0.001f; // FIXME 0.001 is density of material
			totalWeight += weight;
			Bodypart *b = new Bodypart(m_ownerWorld, owner, btVector3( bp->x/1000, bp->y/1000, bp->z/1000 ), weight, offset, transform);
			bodyparts.push_back( b );
		}
	}

	// 5 MOUTH-HEAD
	for ( unsigned int i=0; i < archMouths.size(); i++ )
	{
		archMouth *mo = &archMouths[i];
		// calculate weight
		float weight = ((mo->x*mo->y*mo->z)/1000) * 0.00025f; // FIXME 0.001 is density of material
		totalWeight += weight;
		addMouth(owner, mo->x/1000, mo->y/1000, mo->z/1000, weight, offset, transform);
	}

	btTransform localA;
	btTransform localB;
	for ( unsigned int i=0; i < archConstraints.size(); i++ )
	{
		archConstraint *co = &archConstraints[i];

		localA.setIdentity();
		localA.getBasis().setEulerZYX( co->rot_x_1, co->rot_y_1, co->rot_z_1 );
		localA.setOrigin( btVector3(co->pos_x_1, co->pos_y_1, co->pos_z_1) );

		localB.setIdentity();
		localB.getBasis().setEulerZYX( co->rot_x_2, co->rot_y_2, co->rot_z_2 );
		localB.setOrigin( btVector3(co->pos_x_2, co->pos_y_2, co->pos_z_2) );

		// find the ID's to connect
		int bpID_1 = findBodypart( co->id_1 );
		
		if ( co->isMouthConstraint )
		{
			int bpID_2 = findMouth( co->id_2 );
			if ( bpID_1 > -1 && bpID_2 > -1 )
				addMouthConstraint( (unsigned int)bpID_1, (unsigned int)bpID_2, localA, localB, co->limit_1, co->limit_2 );
		}
		else
		{
			int bpID_2 = findBodypart( co->id_2 );
			if ( bpID_1 > -1 && bpID_2 > -1 )
				addConstraint( (unsigned int)bpID_1, (unsigned int)bpID_2, localA, localB, co->limit_1, co->limit_2 );
		}
	}
}

void Body::removeBodypart(unsigned int id)
{
// 	cerr << "requested removal of bodypart id " << id << endl;
	
	// find constraints where this bodypart is id1, in order to remove connected bodyparts
	for ( unsigned int i = 0; i < archConstraints.size(); i++ )
	{
		archConstraint* c = &archConstraints[i];
		if ( c->id_1 == id )
		{
// 			cerr << " is connected to " << c->isMouthConstraint << " " << c->id_2 << endl;
			if ( c->isMouthConstraint )
				removeMouth( findMouth(c->id_2) );
			else
				removeBodypart( c->id_2 );
		}
	}

// 	cerr << "really removing " << id << " which is " << findBodypart( id ) << endl;
	archBodyparts.erase( archBodyparts.begin() + findBodypart(id) );
}

void Body::removeMouth(unsigned int id)
{
// 	cerr << "removing mouth " << id << endl;
	archMouths.erase(archMouths.begin()+id);
}

void Body::addRandomMouth()
{
	// Throw in a mouth
		archMouths.push_back( archMouth() );
		archMouth* mo = &archMouths[archMouths.size()-1];
		mo->id		= 1000;
		mo->x		= randgen->Instance()->get( settings->getCVar("body_minheadsize"), settings->getCVar("body_maxheadsize") );
		mo->y		= randgen->Instance()->get( settings->getCVar("body_minheadsize"), settings->getCVar("body_maxheadsize") );
		mo->z		= randgen->Instance()->get( settings->getCVar("body_minheadsize"), settings->getCVar("body_maxheadsize") );

	// Get it connected somehow

		unsigned int connID1 = randgen->Instance()->get( 0, archBodyparts.size()-1 );
		unsigned int connID2 = archMouths.size()-1;

		addRandomConstraint(connID1, connID2, true);
}

void Body::addRandomBodypart()
{
	// Throw in a bodypart
		archBodyparts.push_back( archBodypart() );
		archBodypart *bp = &archBodyparts[archBodyparts.size()-1];
		bp->id		= 0; // to avoid uninitialized id
		bp->id		= getUniqueBodypartID();
		bp->type	= 0;
		bp->materialID	= 0;
		bp->x		= randgen->Instance()->get( settings->getCVar("body_minbodypartsize"), settings->getCVar("body_maxbodypartsize") );
		bp->y		= randgen->Instance()->get( settings->getCVar("body_minbodypartsize"), settings->getCVar("body_maxbodypartsize") );
		bp->z		= randgen->Instance()->get( settings->getCVar("body_minbodypartsize"), settings->getCVar("body_maxbodypartsize") );

	// Get it connected somehow
		unsigned int connID1 = randgen->Instance()->get( 0, archBodyparts.size()-1 );
		unsigned int connID2 = archBodyparts.size()-1;
		while ( connID1 == connID2 )
			connID1 = randgen->Instance()->get( 0, archBodyparts.size()-1 );

		addRandomConstraint(connID1, connID2, false);
}

void Body::addRandomConstraint(unsigned int connID1, unsigned int connID2, bool isMouth)
{
		archConstraints.push_back( archConstraint() );
		archConstraint *co = &archConstraints[archConstraints.size()-1];

		co->isMouthConstraint	= isMouth;
		// first initialize constraint id's
		co->constraint_id1	= 0;
		co->constraint_id2	= 0;
		co->constraint_id1	= getUniqueConstraintID();
		co->constraint_id2	= getUniqueConstraintID();
		co->id_1		= archBodyparts[ connID1 ].id;
		if ( isMouth )
			co->id_2		= archMouths[ connID2 ].id;
		else
			co->id_2		= archBodyparts[ connID2 ].id;

		co->rot_x_1		= ((float)randgen->Instance()->get( 0, 1571 ) - 0) / 1000;
		co->rot_y_1		= ((float)randgen->Instance()->get( 0, 1571 ) - 0) / 1000;
		co->rot_z_1		= ((float)randgen->Instance()->get( 0, 1571 ) - 0) / 1000;

		co->rot_x_2		= ((float)randgen->Instance()->get( 0, 1571 ) - 0) / 1000;
		co->rot_y_2		= ((float)randgen->Instance()->get( 0, 1571 ) - 0) / 1000;
		co->rot_z_2		= ((float)randgen->Instance()->get( 0, 1571 ) - 0) / 1000;

		randomConstraintPosition(co, 1, connID1);
		randomConstraintPosition(co, 2, connID2);

		co->limit_1		= (float)randgen->Instance()->get( 0, 7853 ) / -10000;
		co->limit_2		= -1.0f * co->limit_1;
}

void Body::randomConstraintPosition(archConstraint* co, unsigned int OneOrTwo, unsigned int connID)
{
	if ( OneOrTwo == 1 )
	{
		co->XYZ = randgen->Instance()->get( 0, 2 );
		co->sign = randgen->Instance()->get( 0, 1 );
		if ( co->sign == 0 ) co->sign = -1;

	// now we know the plane to connect to, determine positions
		if ( co->XYZ == 0 ) // X
		{
			// ((x / 1000.0f)  / 2)  * 1.5f * co->sign = 
			co->pos_x_1 = (archBodyparts[connID].x / 2000.0f) * co->sign * bodypartspacer;
			co->pos_y_1 = ((float)randgen->Instance()->get( 0, (archBodyparts[connID].y)*2) - archBodyparts[connID].y) / 1000;
			co->pos_z_1 = ((float)randgen->Instance()->get( 0, (archBodyparts[connID].z)*2) - archBodyparts[connID].z) / 1000;
		}
		else if ( co->XYZ == 1 ) // Y
		{
			co->pos_x_1 = ((float)randgen->Instance()->get( 0, (archBodyparts[connID].x)*2) - archBodyparts[connID].x) / 1000;
			co->pos_y_1 = (archBodyparts[connID].y / 2000.0f) * co->sign * bodypartspacer;
			co->pos_z_1 = ((float)randgen->Instance()->get( 0, (archBodyparts[connID].z)*2) - archBodyparts[connID].z) / 1000;
		}
		else // Z
		{
			co->pos_x_1 = ((float)randgen->Instance()->get( 0, (archBodyparts[connID].x)*2) - archBodyparts[connID].x) / 1000;
			co->pos_y_1 = ((float)randgen->Instance()->get( 0, (archBodyparts[connID].y)*2) - archBodyparts[connID].y) / 1000;
			co->pos_z_1 = (archBodyparts[connID].z / 2000.0f) * co->sign * bodypartspacer;
		}
	}
	else
	{
		int othersign = -1 * co->sign;
		if ( !co->isMouthConstraint )
		{
			if ( co->XYZ == 0 ) // X
			{
				co->pos_x_2 = (archBodyparts[connID].x / 2000.0f) * othersign * bodypartspacer;
				co->pos_y_2 = ((float)randgen->Instance()->get( 0, (archBodyparts[connID].y)*2) - archBodyparts[connID].y) / 1000;
				co->pos_z_2 = ((float)randgen->Instance()->get( 0, (archBodyparts[connID].z)*2) - archBodyparts[connID].z) / 1000;
			}
			else if ( co->XYZ == 1 ) // Y
			{
				co->pos_x_2 = ((float)randgen->Instance()->get( 0, (archBodyparts[connID].x)*2) - archBodyparts[connID].x) / 1000;
				co->pos_y_2 = (archBodyparts[connID].y / 2000.0f) * othersign * bodypartspacer;
				co->pos_z_2 = ((float)randgen->Instance()->get( 0, (archBodyparts[connID].z)*2) - archBodyparts[connID].z) / 1000;
			}
			else // Z
			{
				co->pos_x_2 = ((float)randgen->Instance()->get( 0, (archBodyparts[connID].x)*2) - archBodyparts[connID].x) / 1000;
				co->pos_y_2 = ((float)randgen->Instance()->get( 0, (archBodyparts[connID].y)*2) - archBodyparts[connID].y) / 1000;
				co->pos_z_2 = (archBodyparts[connID].z / 2000.0f) * othersign * bodypartspacer;
			}
		}
		else
		{
			if ( co->XYZ == 0 ) // X
			{
				co->pos_x_2 = (archMouths[connID].x / 2000.0f) * othersign * bodypartspacer;
				co->pos_y_2 = ((float)randgen->Instance()->get( 0, (archMouths[connID].y)*2) - archMouths[connID].y) / 1000;
				co->pos_z_2 = ((float)randgen->Instance()->get( 0, (archMouths[connID].z)*2) - archMouths[connID].z) / 1000;
			}
			else if ( co->XYZ == 1 ) // Y
			{
				co->pos_x_2 = ((float)randgen->Instance()->get( 0, (archMouths[connID].x)*2) - archMouths[connID].x) / 1000;
				co->pos_y_2 = (archMouths[connID].y / 2000.0f) * othersign * bodypartspacer;
				co->pos_z_2 = ((float)randgen->Instance()->get( 0, (archMouths[connID].z)*2) - archMouths[connID].z) / 1000;
			}
			else // Z
			{
				co->pos_x_2 = ((float)randgen->Instance()->get( 0, (archMouths[connID].x)*2) - archMouths[connID].x) / 1000;
				co->pos_y_2 = ((float)randgen->Instance()->get( 0, (archMouths[connID].y)*2) - archMouths[connID].y) / 1000;
				co->pos_z_2 = (archMouths[connID].z / 2000.0f) * othersign * bodypartspacer;
			}
		}
	}
}

void Body::mutate(unsigned int runs)
{
	for ( unsigned int i=0; i < runs; i++ )
	{
		unsigned int mode = randgen->Instance()->get(1,100);
		
		// ADD BODYPART
			unsigned int modesum = settings->getCVar("body_percentmutateeffectaddbodypart");
			if ( mode <= modesum )
			{
				if ( archBodyparts.size() < settings->getCVar("body_maxbodyparts") )
				{
// 					cerr << "adding bodypart" << endl;
					addRandomBodypart();
// 					cerr << "done adding bodypart" << endl;
				}
				else
					runs++;
				continue;
			}

		// REMOVE BODYPART
			modesum += settings->getCVar("body_percentmutateeffectremovebodypart");
			if ( mode <= modesum )
			{
				if ( archBodyparts.size() > 2 )
				{
					// pick a random bodypart
					unsigned int bid = randgen->Instance()->get( 0, archBodyparts.size()-1 );

					// if not main body, remove it
					if ( archBodyparts[bid].id != 1000 )
					{
// 						cerr << "removing bodypart " << bid << " id " << archBodyparts[bid].id  << endl;

						removeBodypart( archBodyparts[bid].id );

// 						cerr << "removing obsolete constraints, expected errors:" << endl;
						for ( int i = 0; i < (int)archConstraints.size(); i++ )
						{
							archConstraint* c = &archConstraints[i];
							if ( findBodypart( c->id_1 ) == -1 )
							{
								archConstraints.erase(archConstraints.begin()+i);
								i--;
							}
							else if ( c->isMouthConstraint && findMouth( c->id_2 ) == -1 )
							{
								archConstraints.erase(archConstraints.begin()+i);
								i--;
							}
							else if ( !c->isMouthConstraint && findBodypart( c->id_2 ) == -1 )
							{
								archConstraints.erase(archConstraints.begin()+i);
								i--;
							}
						}
// 						cerr << "done removing obsolete constraints" << endl << endl;

// 						cerr << "done removing bodypart" << endl;

						// re add mouth if needed
						if ( archMouths.size() == 0 )
								addRandomMouth();
					}
					else
						runs++;

				}
				else
					runs++;
				continue;
			}

		// RESIZE BODYPART
			modesum += settings->getCVar("body_percentmutateeffectresizebodypart");
			if ( mode <= modesum )
			{
// 				cerr << "resize bodypart" << endl;

					// pick a random bodypart
					unsigned int bid = randgen->Instance()->get( 0, archBodyparts.size()-1 );
					archBodypart *bp = &archBodyparts[bid];
// 					archBodyparts.push_back( archBodypart() );
// 					archBodypart *bp = &archBodyparts[archBodyparts.size()-1];

// 					bp->id		= archBodyparts[bid].id;
// 					bp->type	= archBodyparts[bid].type;
// 					bp->materialID	= archBodyparts[bid].materialID;
// 					bp->x		= archBodyparts[bid].x;
// 					bp->y		= archBodyparts[bid].y;
// 					bp->z		= archBodyparts[bid].z;

					unsigned int axismode = randgen->Instance()->get(0,2);
					if ( axismode == 0 )
						bp->x = randgen->Instance()->get( settings->getCVar("body_minbodypartsize"), settings->getCVar("body_maxbodypartsize") );
					else if ( axismode == 1 )
						bp->y = randgen->Instance()->get( settings->getCVar("body_minbodypartsize"), settings->getCVar("body_maxbodypartsize") );
					else
						bp->z = randgen->Instance()->get( settings->getCVar("body_minbodypartsize"), settings->getCVar("body_maxbodypartsize") );

// 					archBodyparts.erase(archBodyparts.begin()+bid);

					// reposition the constraints back to the resized bodypart
					for ( int i = 0; i < (int)archConstraints.size(); i++ )
					{
						archConstraint* co = &archConstraints[i];
						if ( findBodypart( co->id_1 ) == (int)bp->id )
						{
							if ( co->XYZ == 0 ) // X
								co->pos_x_1 = (bp->x / 2000.0f) * co->sign * bodypartspacer;
							else if ( co->XYZ == 1 ) // Y
								co->pos_y_1 = (bp->y / 2000.0f) * co->sign * bodypartspacer;
							else if ( co->XYZ == 2 ) // Z
								co->pos_z_1 = (bp->z / 2000.0f) * co->sign * bodypartspacer;
						}
						else if ( !co->isMouthConstraint && findBodypart( co->id_2 ) == (int)bp->id )
						{
							int othersign = -1 * co->sign;
							if ( co->XYZ == 0 ) // X
								co->pos_x_2 = (bp->x / 2000.0f) * othersign * bodypartspacer;
							else if ( co->XYZ == 1 ) // Y
								co->pos_y_2 = (bp->y / 2000.0f) * othersign * bodypartspacer;
							else if ( co->XYZ == 2 ) // Z
								co->pos_z_2 = (bp->z / 2000.0f) * othersign * bodypartspacer;
						}
					}

// 				cerr << "done resize bodypart" << endl;
				continue;
			}

		// RESIZE BODYPART SLIGHTLY
			modesum += settings->getCVar("body_percentmutateeffectresizebodypart_slightly");
			if ( mode <= modesum )
			{
// 				cerr << "resize bodypart slightly" << endl;

					// pick a random bodypart
					unsigned int bid = randgen->Instance()->get( 0, archBodyparts.size()-1 );

					archBodyparts.push_back( archBodypart() );
					archBodypart *bp = &archBodyparts[archBodyparts.size()-1];

					bp->id		= archBodyparts[bid].id;
					bp->type	= archBodyparts[bid].type;
					bp->materialID	= archBodyparts[bid].materialID;
					bp->x		= archBodyparts[bid].x;
					bp->y		= archBodyparts[bid].y;
					bp->z		= archBodyparts[bid].z;

					unsigned int axismode = randgen->Instance()->get(0,2);
					unsigned int direction = randgen->Instance()->get(0,1);
					if ( axismode == 0 )
					{
						if ( direction == 0 )
							bp->x += randgen->Instance()->get( 1, settings->getCVar("body_maxbodypartsize") / 10 );
						else
							bp->x -= randgen->Instance()->get( 1, settings->getCVar("body_maxbodypartsize") / 10 );
					}
					else if ( axismode == 1 )
					{
						if ( direction == 0 )
							bp->y += randgen->Instance()->get( 1, settings->getCVar("body_maxbodypartsize") / 10 );
						else
							bp->y -= randgen->Instance()->get( 1, settings->getCVar("body_maxbodypartsize") / 10 );
					}
					else
					{
						if ( direction == 0 )
							bp->z += randgen->Instance()->get( 1, settings->getCVar("body_maxbodypartsize") / 10 );
						else
							bp->z -= randgen->Instance()->get( 1, settings->getCVar("body_maxbodypartsize") / 10 );
					}

					// see that they didn't go over their limits
					if ( bp->x < settings->getCVar("body_minbodypartsize") )
						bp->x = settings->getCVar("body_minbodypartsize");
					else if ( bp->x > settings->getCVar("body_maxbodypartsize") )
						bp->x = settings->getCVar("body_minbodypartsize");

					if ( bp->y < settings->getCVar("body_minbodypartsize") )
						bp->y = settings->getCVar("body_minbodypartsize");
					else if ( bp->y > settings->getCVar("body_maxbodypartsize") )
						bp->y = settings->getCVar("body_minbodypartsize");

					if ( bp->z < settings->getCVar("body_minbodypartsize") )
						bp->z = settings->getCVar("body_minbodypartsize");
					else if ( bp->z > settings->getCVar("body_maxbodypartsize") )
						bp->z = settings->getCVar("body_minbodypartsize");

					archBodyparts.erase(archBodyparts.begin()+bid);

					// reposition the constraints back to the resized bodypart
					for ( int i = 0; i < (int)archConstraints.size(); i++ )
					{
						archConstraint* co = &archConstraints[i];
						if ( findBodypart( co->id_1 ) == (int)bp->id )
						{
							if ( co->XYZ == 0 ) // X
								co->pos_x_1 = (bp->x / 2000.0f) * co->sign * bodypartspacer;
							else if ( co->XYZ == 1 ) // Y
								co->pos_y_1 = (bp->y / 2000.0f) * co->sign * bodypartspacer;
							else if ( co->XYZ == 2 ) // Z
								co->pos_z_1 = (bp->z / 2000.0f) * co->sign * bodypartspacer;
						}
						else if ( !co->isMouthConstraint && findBodypart( co->id_2 ) == (int)bp->id )
						{
							int othersign = -1 * co->sign;
							if ( co->XYZ == 0 ) // X
								co->pos_x_2 = (bp->x / 2000.0f) * othersign * bodypartspacer;
							else if ( co->XYZ == 1 ) // Y
								co->pos_y_2 = (bp->y / 2000.0f) * othersign * bodypartspacer;
							else if ( co->XYZ == 2 ) // Z
								co->pos_z_2 = (bp->z / 2000.0f) * othersign * bodypartspacer;
						}
					}

// 				cerr << "done resize bodypart" << endl;
				continue;
			}

		// CHANGE CONSTRAINT LIMITS
			modesum += settings->getCVar("body_percentmutateeffectchangeconstraintlimits");
			if ( mode <= modesum )
			{
// 				cerr << "changing constraint limits" << endl;

				unsigned int cid = randgen->Instance()->get( 0, archConstraints.size()-1 );
				archConstraint* co = &archConstraints[cid];
				co->limit_1		= (float)randgen->Instance()->get( 0, 7853 ) / -10000;
				co->limit_2		= -1.0f * co->limit_1;

// 				cerr << "done changing constraint limits" << endl;
				continue;
			}
	
		// CHANGE CONSTRAINT ANGLES
			modesum += settings->getCVar("body_percentmutateeffectchangeconstraintangles");
			if ( mode <= modesum )
			{
// 				cerr << "changing constraint angles" << endl;

				unsigned int cid = randgen->Instance()->get( 0, archConstraints.size()-1 );
				archConstraint* co = &archConstraints[cid];
				co->rot_x_1		= ((float)randgen->Instance()->get( 0, 3141 ) - 1571) / 1000;
				co->rot_z_1		= ((float)randgen->Instance()->get( 0, 3141 ) - 1571) / 1000;
				co->rot_y_1		= ((float)randgen->Instance()->get( 0, 3141 ) - 1571) / 1000;

				co->rot_x_2		= ((float)randgen->Instance()->get( 0, 3141 ) - 1571) / 1000;
				co->rot_y_2		= ((float)randgen->Instance()->get( 0, 3141 ) - 1571) / 1000;
				co->rot_z_2		= ((float)randgen->Instance()->get( 0, 3141 ) - 1571) / 1000;

// 				cerr << "done changing constraint angles" << endl;
				continue;
			}

		// REPOSITION A CONSTRAINT
			modesum += settings->getCVar("body_percentmutateeffectchangeconstraintposition");
			if ( mode <= modesum )
			{
// 				cerr << "changing constraint position" << endl;

				unsigned int cid = randgen->Instance()->get( 0, archConstraints.size()-1 );
				archConstraint* co = &archConstraints[cid];

				int connID1 = findBodypart(co->id_1);
				int connID2;

				if ( co->isMouthConstraint )
					connID2 = findMouth(co->id_2);
				else
					connID2 = findBodypart(co->id_2);

				// pick one of 2 bodies to reconnect
				unsigned int body = randgen->Instance()->get( 0, 1 );

				if ( body == 0 )
					randomConstraintPosition(co, 1, connID1);
				else
					randomConstraintPosition(co, 2, connID2);

// 				cerr << "done changing constraint position" << endl;
				continue;
			}

		// REMOVE AND ADD MOUTH
			modesum += settings->getCVar("body_percentmutateeffectrepositionmouth");
			if ( mode <= modesum )
			{
// 				cerr << "remove and add mouth" << endl;
				
				for ( int i = 0; i < (int)archConstraints.size(); i++ )
				{
					archConstraint* c = &archConstraints[i];
					if ( c->isMouthConstraint && c->id_2 == archMouths[0].id )
					{
						archConstraints.erase(archConstraints.begin()+i);
						i--;
					}
				}

				removeMouth(0);

				addRandomMouth();

// 				cerr << "done remove and add mouth" << endl;
				continue;
			}

		// if we reach here, none were processed, decrease runs by 1 to make sure we get a hit
			if ( modesum > 0 )
				runs++;
	}
}

int Body::findBodypart( unsigned int id )
{
	for ( unsigned int i=0; i < archBodyparts.size(); i++ )
	{
		if ( archBodyparts[i].id == id )
		{
			return i;
		}
	}
// 	cerr << " NOT GOOD: cannot find a bodypart for the id " << id << endl;
	return -1;
}

int Body::findMouth( unsigned int id )
{
	for ( unsigned int i=0; i < archMouths.size(); i++ )
	{
		if ( archMouths[i].id == id )
		{
			return i;
		}
	}
// 	cerr << " NOT GOOD " << endl;
// 	cerr << " NOT GOOD: cannot find a mouth for the id " << id << endl;
	return -1;
}

unsigned int Body::getUniqueBodypartID()
{
	unsigned int id = 1000;
	bool found = true;
	while ( found )
	{
		found = false;
		for ( unsigned int i = 0; i < archBodyparts.size() && !found; i++ )
			if ( archBodyparts[i].id == id )
			{
				found = true;
				id++;
			}
	}
	return id;
}

unsigned int Body::getUniqueConstraintID()
{
	unsigned int id = 1000;
	bool found = true;
	while ( found )
	{
		found = false;
		for ( unsigned int i = 0; i < archConstraints.size() && !found; i++ )
		{
			if ( archConstraints[i].constraint_id1 == id || archConstraints[i].constraint_id2 == id )
			{
				found = true;
				id++;
			}
		}
	}
	return id;
}

void Body::copyFrom(const Body& otherBody)
{
	for ( unsigned int i=0; i < otherBody.archBodyparts.size(); i++ )
	{
		const archBodypart *obp = &otherBody.archBodyparts[i];
		archBodyparts.push_back( archBodypart() );
		archBodypart *bp = &archBodyparts[archBodyparts.size()-1];
		
		bp->id		= obp->id;
		bp->type	= obp->type;
		bp->materialID	= obp->materialID;
		bp->x		= obp->x;
		bp->y		= obp->y;
		bp->z		= obp->z;
	}

	for ( unsigned int i=0; i < otherBody.archMouths.size(); i++ )
	{
		const archMouth *omo = &otherBody.archMouths[i];
		archMouths.push_back( archMouth() );
		archMouth *mo = &archMouths[archMouths.size()-1];
		
		mo->id		= omo->id;
		mo->x		= omo->x;
		mo->y		= omo->y;
		mo->z		= omo->z;
	}

	for ( unsigned int i=0; i < otherBody.archConstraints.size(); i++ )
	{
		const archConstraint *oco = &otherBody.archConstraints[i];
		archConstraints.push_back( archConstraint() );
		archConstraint *co = &archConstraints[archConstraints.size()-1];
		
		co->isMouthConstraint	= oco->isMouthConstraint;
		co->constraint_id1	= oco->constraint_id1;
		co->constraint_id2	= oco->constraint_id2;
		co->XYZ			= oco->XYZ;
		co->sign		= oco->sign;
		co->id_1		= oco->id_1;
		co->id_2		= oco->id_2;
		co->rot_x_1		= oco->rot_x_1;
		co->rot_x_2		= oco->rot_x_2;
		co->rot_y_1		= oco->rot_y_1;
		co->rot_y_2		= oco->rot_y_2;
		co->rot_z_1		= oco->rot_z_1;
		co->rot_z_2		= oco->rot_z_2;
		co->pos_x_1		= oco->pos_x_1;
		co->pos_x_2		= oco->pos_x_2;
		co->pos_y_1		= oco->pos_y_1;
		co->pos_y_2		= oco->pos_y_2;
		co->pos_z_1		= oco->pos_z_1;
		co->pos_z_2		= oco->pos_z_2;
		co->limit_1		= oco->limit_1;
		co->limit_2		= oco->limit_2;
	}
}

void Body::setArch(string* content)
{
//	cerr << *content << endl;

	string contentCopy = *content;
	string line = parseH->Instance()->returnUntillStrip( "\n", contentCopy );
	while ( !line.empty() )
	{
		if ( parseH->Instance()->beginMatchesStrip( "b ", line ) )
		{
			// b 99999 box 0 75 75 200

// 			cerr << "bodypart" << endl;

			archBodyparts.push_back( archBodypart() );
			archBodypart *bp = &archBodyparts[archBodyparts.size()-1];
			
			string bodypartID = Parser::Instance()->returnUntillStrip( " ", line );
			if(EOF == sscanf(bodypartID.c_str(), "%d", &bp->id)) cerr << "error in parsing body" << endl;
			string bodypartShape = Parser::Instance()->returnUntillStrip( " ", line );
			if ( bodypartShape == "box" )
			{
				// type = box
					bp->type = 0;

				// materialID
					string materialID = Parser::Instance()->returnUntillStrip( " ", line );
					if(EOF == sscanf(materialID.c_str(), "%d", &bp->materialID)) cerr << "error in parsing body" << endl;

				// dimesions X Y Z
					string X = Parser::Instance()->returnUntillStrip( " ", line );
					string Y = Parser::Instance()->returnUntillStrip( " ", line );
					string Z = line;
					if(EOF == sscanf(X.c_str(), "%f", &bp->x)) cerr << "error in parsing body" << endl;
					if(EOF == sscanf(Y.c_str(), "%f", &bp->y)) cerr << "error in parsing body" << endl;
					if(EOF == sscanf(Z.c_str(), "%f", &bp->z)) cerr << "error in parsing body" << endl;


/*				cerr << endl << " id " << bp->id << endl;
				cerr << " type " << bp->type << endl;
				cerr << " material " << bp->materialID << endl;
				cerr << " x " << bp->x << endl;
				cerr << " y " << bp->y << endl;
				cerr << " z " << bp->z << endl;*/
			}
		}
		else if ( parseH->Instance()->beginMatchesStrip( "c ", line ) )
		{
			// c 99999 1.5707963 0 0 0 0 -0.25 99998 1.5707963 0 0 0 0 0.25
// 			cm 0 1 1000 1001 1000 1.115 -0.752 -0.102 0.258 0.089 -0.133 -0.1103 1000 -1.4 -1.007 -1.287 -0.258 0.039 0.137 0.1103
// 			cerr << "constraint" << endl;

			archConstraint CO;
			archConstraints.push_back( CO );
			archConstraint *co = &archConstraints[archConstraints.size()-1];
			
			// XYZ & sign
				string XYZ = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(XYZ.c_str(), "%d", &co->XYZ)) cerr << "error in parsing body" << endl;
				string SIGN = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(SIGN.c_str(), "%d", &co->sign)) cerr << "error in parsing body" << endl;

			// CONSTRAINT IDS
				string ID = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(ID.c_str(), "%d", &co->constraint_id1)) cerr << "error in parsing body" << endl;
				ID = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(ID.c_str(), "%d", &co->constraint_id2)) cerr << "error in parsing body" << endl;

			// CONNECTION TO BODYPART 1
				string ID_1 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(ID_1.c_str(), "%d", &co->id_1)) cerr << "error in parsing body" << endl;

			// ROTATION
				string ROT_X_1 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(ROT_X_1.c_str(), "%f", &co->rot_x_1)) cerr << "error in parsing body" << endl;
				string ROT_Y_1 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(ROT_Y_1.c_str(), "%f", &co->rot_y_1)) cerr << "error in parsing body" << endl;
				string ROT_Z_1 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(ROT_Z_1.c_str(), "%f", &co->rot_z_1)) cerr << "error in parsing body" << endl;

			// POSITION
				string POS_X_1 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(POS_X_1.c_str(), "%f", &co->pos_x_1)) cerr << "error in parsing body" << endl;
				string POS_Y_1 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(POS_Y_1.c_str(), "%f", &co->pos_y_1)) cerr << "error in parsing body" << endl;
				string POS_Z_1 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(POS_Z_1.c_str(), "%f", &co->pos_z_1)) cerr << "error in parsing body" << endl;

			// LIMIT
				string LIMIT_1 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(LIMIT_1.c_str(), "%f", &co->limit_1)) cerr << "error in parsing body" << endl;

			// CONNECTION TO BODYPART 2
				string ID_2 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(ID_2.c_str(), "%d", &co->id_2)) cerr << "error in parsing body" << endl;

			// ROTATION
				string ROT_X_2 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(ROT_X_2.c_str(), "%f", &co->rot_x_2)) cerr << "error in parsing body" << endl;
				string ROT_Y_2 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(ROT_Y_2.c_str(), "%f", &co->rot_y_2)) cerr << "error in parsing body" << endl;
				string ROT_Z_2 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(ROT_Z_2.c_str(), "%f", &co->rot_z_2)) cerr << "error in parsing body" << endl;

			// POSITION
				string POS_X_2 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(POS_X_2.c_str(), "%f", &co->pos_x_2)) cerr << "error in parsing body" << endl;
				string POS_Y_2 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(POS_Y_2.c_str(), "%f", &co->pos_y_2)) cerr << "error in parsing body" << endl;
				string POS_Z_2 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(POS_Z_2.c_str(), "%f", &co->pos_z_2)) cerr << "error in parsing body" << endl;

			// LIMIT
				string LIMIT_2 = line;
				if(EOF == sscanf(LIMIT_2.c_str(), "%f", &co->limit_2)) cerr << "error in parsing body" << endl;
		}
		else if ( parseH->Instance()->beginMatchesStrip( "cm ", line ) )
		{
			// cm 99999 1.5707963 0 0 0 0 -0.25 99998 1.5707963 0 0 0 0 0.25

// 			cerr << "constraint" << endl;

			archConstraint CO;
			archConstraints.push_back( CO );
			archConstraint *co = &archConstraints[archConstraints.size()-1];

			co->isMouthConstraint = true;

			// XYZ & sign
				string XYZ = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(XYZ.c_str(), "%d", &co->XYZ)) cerr << "error in parsing body" << endl;
				string SIGN = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(SIGN.c_str(), "%d", &co->sign)) cerr << "error in parsing body" << endl;

			// CONSTRAINT IDS
				string ID = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(ID.c_str(), "%d", &co->constraint_id1)) cerr << "error in parsing body" << endl;
				ID = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(ID.c_str(), "%d", &co->constraint_id2)) cerr << "error in parsing body" << endl;

			// CONNECTION TO BODYPART 1
				string ID_1 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(ID_1.c_str(), "%d", &co->id_1)) cerr << "error in parsing body" << endl;

			// ROTATION
				string ROT_X_1 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(ROT_X_1.c_str(), "%f", &co->rot_x_1)) cerr << "error in parsing body" << endl;
				string ROT_Y_1 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(ROT_Y_1.c_str(), "%f", &co->rot_y_1)) cerr << "error in parsing body" << endl;
				string ROT_Z_1 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(ROT_Z_1.c_str(), "%f", &co->rot_z_1)) cerr << "error in parsing body" << endl;

			// POSITION
				string POS_X_1 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(POS_X_1.c_str(), "%f", &co->pos_x_1)) cerr << "error in parsing body" << endl;
				string POS_Y_1 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(POS_Y_1.c_str(), "%f", &co->pos_y_1)) cerr << "error in parsing body" << endl;
				string POS_Z_1 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(POS_Z_1.c_str(), "%f", &co->pos_z_1)) cerr << "error in parsing body" << endl;

			// LIMIT
				string LIMIT_1 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(LIMIT_1.c_str(), "%f", &co->limit_1)) cerr << "error in parsing body" << endl;

			// CONNECTION TO BODYPART 2
				string ID_2 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(ID_2.c_str(), "%d", &co->id_2)) cerr << "error in parsing body" << endl;

			// ROTATION
				string ROT_X_2 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(ROT_X_2.c_str(), "%f", &co->rot_x_2)) cerr << "error in parsing body" << endl;
				string ROT_Y_2 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(ROT_Y_2.c_str(), "%f", &co->rot_y_2)) cerr << "error in parsing body" << endl;
				string ROT_Z_2 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(ROT_Z_2.c_str(), "%f", &co->rot_z_2)) cerr << "error in parsing body" << endl;

			// POSITION
				string POS_X_2 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(POS_X_2.c_str(), "%f", &co->pos_x_2)) cerr << "error in parsing body" << endl;
				string POS_Y_2 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(POS_Y_2.c_str(), "%f", &co->pos_y_2)) cerr << "error in parsing body" << endl;
				string POS_Z_2 = Parser::Instance()->returnUntillStrip( " ", line );
				if(EOF == sscanf(POS_Z_2.c_str(), "%f", &co->pos_z_2)) cerr << "error in parsing body" << endl;

			// LIMIT
				string LIMIT_2 = line;
				if(EOF == sscanf(LIMIT_2.c_str(), "%f", &co->limit_2)) cerr << "error in parsing body" << endl;
		}
		else if ( parseH->Instance()->beginMatchesStrip( "m ", line ) )
		{
			// m 99999 50, 50, 100
// 			cerr << "constraint" << endl;

			archMouth MO;
			archMouths.push_back( MO );
			archMouth *mo = &archMouths[archMouths.size()-1];

			string ID = Parser::Instance()->returnUntillStrip( " ", line );
			if(EOF == sscanf(ID.c_str(), "%d", &mo->id)) cerr << "error in parsing body" << endl;

			string X = Parser::Instance()->returnUntillStrip( " ", line );
			if(EOF == sscanf(X.c_str(), "%f", &mo->x)) cerr << "error in parsing body" << endl;

			string Y = Parser::Instance()->returnUntillStrip( " ", line );
			if(EOF == sscanf(Y.c_str(), "%f", &mo->y)) cerr << "error in parsing body" << endl;

			string Z = line;
			if(EOF == sscanf(Z.c_str(), "%f", &mo->z)) cerr << "error in parsing body" << endl;
		}
		line = parseH->Instance()->returnUntillStrip( "\n", contentCopy );
	}
}


string* Body::getArch()
{
	stringstream buf;

	// neuron info
		for ( unsigned int i=0; i < archBodyparts.size(); i++ )
		{
			archBodypart *bp = &archBodyparts[i];
			buf << "b" << " " << bp->id << " " << "box" << " " << bp->materialID << " " << bp->x << " " << bp->y << " " << bp->z << "\n";
		}

		for ( unsigned int i=0; i < archMouths.size(); i++ )
		{
			archMouth *mo = &archMouths[i];
			buf << "m" << " " << mo->id << " " << mo->x << " " << mo->y << " " << mo->z << "\n";
		}

		for ( unsigned int i=0; i < archConstraints.size(); i++ )
		{
			archConstraint *co = &archConstraints[i];
			if ( co->isMouthConstraint )
				buf << "cm";
			else
				buf << "c";
			buf << " " << co->XYZ << " " << co->sign;
			buf << " " << co->constraint_id1 << " " << co->constraint_id2 << " ";
			buf << co->id_1 << " " << co->rot_x_1 << " " << co->rot_y_1 << " " << co->rot_z_1 << " " << co->pos_x_1 << " " << co->pos_y_1 << " " << co->pos_z_1 << " " << co->limit_1 << " ";
			buf << co->id_2 << " " << co->rot_x_2 << " " << co->rot_y_2 << " " << co->rot_z_2 << " " << co->pos_x_2 << " " << co->pos_y_2 << " " << co->pos_z_2 << " " << co->limit_2;
			buf << "\n";
		}

	archBuffer = buf.str();
	return &archBuffer;
}

// void Body::addConstraint(unsigned int bodypartID1, unsigned int bodypartID2, btTransform& localA, btTransform& localB, double limitA, double limitB)
// {
// 	// Now setup the constraints
// 	Constraint *c = new Constraint(m_ownerWorld);
// 	constraints.push_back( c );
// 
// 	btHingeConstraint* cons = new btHingeConstraint(*bodyparts[bodypartID1]->body, *bodyparts[bodypartID2]->body, localA, localB);
// 	cons->setLimit(limitA, limitB);
// 
// 	c->hinge = cons;
// 	c->type = 0;
// 	m_ownerWorld->addConstraint(c->hinge, true);
// }

// void Body::addConeTwistConstraint(unsigned int bodypartID1, unsigned int bodypartID2, btTransform& localA, btTransform& localB, double limitA, double limitB, double limitC)
// {
// 	// Now setup the constraints
// 	Constraint *c = new Constraint(m_ownerWorld);
// 	constraints.push_back( c );
// 
// 	btConeTwistConstraint* cons = new btConeTwistConstraint(*bodyparts[bodypartID1]->body, *bodyparts[bodypartID2]->body, localA, localB);
// 	cons->setLimit(limitA, limitB, limitC);
// 	c->hinge = cons;
// 	c->type = 1;
// 	m_ownerWorld->addConstraint(c->hinge, true);
// }

/*void Body::add6DConstraint(unsigned int bodypartID1, unsigned int bodypartID2, btTransform& localA, btTransform& localB, const btVector3& lowerLimit, const btVector3& upperLimit)
{
	// Now setup the constraints
	Constraint *c = new Constraint(m_ownerWorld);
	constraints.push_back( c );

	btGeneric6DofConstraint* joint6DOF = new btGeneric6DofConstraint(*bodyparts[bodypartID1]->body, *bodyparts[bodypartID2]->body, localA, localB, true);
	joint6DOF->setAngularLowerLimit( lowerLimit );
	joint6DOF->setAngularUpperLimit( upperLimit );
	c->hinge = joint6DOF;
	c->type = 2;
	m_ownerWorld->addConstraint(c->hinge, true);
}*/


Body::~Body()
{
// 		for ( unsigned int i=0; i < archBodyparts.size(); i++ )
// 			delete archBodyparts[i];

		for ( unsigned int i=0; i < bodyparts.size(); i++ )
			delete bodyparts[i];

		for ( unsigned int i=0; i < mouths.size(); i++ )
			delete mouths[i];

		for ( unsigned int i=0; i < constraints.size(); i++ )
			delete constraints[i];
}


