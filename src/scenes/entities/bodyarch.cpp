#include "bodyarch.h"

BodyArch::BodyArch()
{
	settings = Settings::Instance();
	totalWeight = 0.0f;
	bodypartspacer = 2.2f;
}

void BodyArch::buildArch()
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

	// add random more
		unsigned int runs = randgen->Instance()->get( 0, settings->getCVar("body_maxbodypartsatbuildtime")-1 ); // -1 -> central bodypart
		for ( unsigned int i=0; i < runs; i++ )
			addRandomBodypart();

		addRandomMouth();
}

void BodyArch::removeBodypart(unsigned int id)
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

void BodyArch::removeMouth(unsigned int id)
{
// 	cerr << "removing mouth " << id << endl;
	archMouths.erase(archMouths.begin()+id);
}

void BodyArch::addRandomMouth()
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

void BodyArch::addRandomBodypart()
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

void BodyArch::addRandomConstraint(unsigned int connID1, unsigned int connID2, bool isMouth)
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

void BodyArch::randomConstraintPosition(archConstraint* co, unsigned int OneOrTwo, unsigned int connID)
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

void BodyArch::mutate(unsigned int runs)
{
	for ( unsigned int i=0; i < runs; i++ )
	{
		unsigned int tsum = 	settings->getCVar("body_percentmutateeffectaddbodypart")
					+ settings->getCVar("body_percentmutateeffectremovebodypart")
					+ settings->getCVar("body_percentmutateeffectresizebodypart")
					+ settings->getCVar("body_percentmutateeffectresizebodypart_slightly")
					+ settings->getCVar("body_percentmutateeffectresizehead")
					+ settings->getCVar("body_percentmutateeffectresizehead_slightly")
					+ settings->getCVar("body_percentmutateeffectchangeconstraintlimits")
					+ settings->getCVar("body_percentmutateeffectchangeconstraintlimits_slightly")
					+ settings->getCVar("body_percentmutateeffectchangeconstraintangles")
					+ settings->getCVar("body_percentmutateeffectchangeconstraintangles_slightly")
					+ settings->getCVar("body_percentmutateeffectchangeconstraintposition")
					+ settings->getCVar("body_percentmutateeffectchangeconstraintposition_slightly")
					+ settings->getCVar("body_percentmutateeffectrepositionhead")
				;

		unsigned int mode = randgen->Instance()->get(1,tsum);
		
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

					unsigned int axismode = randgen->Instance()->get(0,2);
					if ( axismode == 0 )
						bp->x = randgen->Instance()->get( settings->getCVar("body_minbodypartsize"), settings->getCVar("body_maxbodypartsize") );
					else if ( axismode == 1 )
						bp->y = randgen->Instance()->get( settings->getCVar("body_minbodypartsize"), settings->getCVar("body_maxbodypartsize") );
					else
						bp->z = randgen->Instance()->get( settings->getCVar("body_minbodypartsize"), settings->getCVar("body_maxbodypartsize") );

					// reposition the constraints back to the resized bodypart
					repositiontoConstraints(bp);

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
					archBodypart* bp = &archBodyparts[bid];

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

					// reposition the constraints back to the resized bodypart
					repositiontoConstraints(bp);

// 				cerr << "done resize bodypart" << endl;
				continue;
			}

		// RESIZE HEAD
			modesum += settings->getCVar("body_percentmutateeffectresizehead");
			if ( mode <= modesum )
			{
// 				cerr << "resize mouth" << endl;

					// pick a random head
					unsigned int mid = randgen->Instance()->get( 0, archMouths.size()-1 );
					archMouth* head = &archMouths[mid];

					unsigned int axismode = randgen->Instance()->get(0,2);
					if ( axismode == 0 )
						head->x = randgen->Instance()->get( settings->getCVar("body_minheadsize"), settings->getCVar("body_maxheadsize") );
					else if ( axismode == 1 )
						head->y = randgen->Instance()->get( settings->getCVar("body_minheadsize"), settings->getCVar("body_maxheadsize") );
					else
						head->z = randgen->Instance()->get( settings->getCVar("body_minheadsize"), settings->getCVar("body_maxheadsize") );

					// reposition the constraints back to the resized bodypart
					repositiontoConstraints(head);

// 				cerr << "done resize head" << endl;
				continue;
			}

		// RESIZE HEAD SLIGHTLY
			modesum += settings->getCVar("body_percentmutateeffectresizehead_slightly");
			if ( mode <= modesum )
			{
// 				cerr << "resize head slightly" << endl;

					// pick a random head
					unsigned int mid = randgen->Instance()->get( 0, archMouths.size()-1 );
					archMouth* head = &archMouths[mid];

					unsigned int axismode = randgen->Instance()->get(0,2);
					unsigned int direction = randgen->Instance()->get(0,1);
					if ( axismode == 0 )
					{
						if ( direction == 0 )
							head->x += randgen->Instance()->get( 1, settings->getCVar("body_maxheadsize") / 10 );
						else
							head->x -= randgen->Instance()->get( 1, settings->getCVar("body_maxheadsize") / 10 );
					}
					else if ( axismode == 1 )
					{
						if ( direction == 0 )
							head->y += randgen->Instance()->get( 1, settings->getCVar("body_maxheadsize") / 10 );
						else
							head->y -= randgen->Instance()->get( 1, settings->getCVar("body_maxheadsize") / 10 );
					}
					else
					{
						if ( direction == 0 )
							head->z += randgen->Instance()->get( 1, settings->getCVar("body_maxheadsize") / 10 );
						else
							head->z -= randgen->Instance()->get( 1, settings->getCVar("body_maxheadsize") / 10 );
					}

					// see that they didn't go over their limits
					if ( head->x < settings->getCVar("body_minheadsize") )
						head->x = settings->getCVar("body_minheadsize");
					else if ( head->x > settings->getCVar("body_maxheadsize") )
						head->x = settings->getCVar("body_minheadsize");

					if ( head->y < settings->getCVar("body_minheadsize") )
						head->y = settings->getCVar("body_minheadsize");
					else if ( head->y > settings->getCVar("body_maxheadsize") )
						head->y = settings->getCVar("body_minheadsize");

					if ( head->z < settings->getCVar("body_minheadsize") )
						head->z = settings->getCVar("body_minheadsize");
					else if ( head->z > settings->getCVar("body_maxheadsize") )
						head->z = settings->getCVar("body_minheadsize");

					// reposition the constraints back to the resized bodypart
					repositiontoConstraints(head);

// 				cerr << "done resize head" << endl;
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
	
		// CHANGE CONSTRAINT LIMITS SLIGHTLY
			modesum += settings->getCVar("body_percentmutateeffectchangeconstraintlimits_slightly");
			if ( mode <= modesum )
			{
// 				cerr << "changing constraint limits" << endl;

				unsigned int cid = randgen->Instance()->get( 0, archConstraints.size()-1 );
				archConstraint* co = &archConstraints[cid];
				
				unsigned int direction = randgen->Instance()->get(0,1);

				if ( direction == 0 )
					co->limit_1 += 0.01f;
				else
					co->limit_1 -= 0.01f;
				// check limits limits, ya
				if ( co->limit_1 > 0.0f )
					co->limit_1 = 0.0f;
				if ( co->limit_1 < -0.7853f )
					co->limit_1 = -0.7853f;

				co->limit_2 = -1.0f * co->limit_1;

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

		// CHANGE CONSTRAINT ANGLES SLIGHTLY
			modesum += settings->getCVar("body_percentmutateeffectchangeconstraintangles_slightly");
			if ( mode <= modesum )
			{
// 				cerr << "changing constraint angles" << endl;

				unsigned int cid = randgen->Instance()->get( 0, archConstraints.size()-1 );
				archConstraint* co = &archConstraints[cid];

				unsigned int XYZ = randgen->Instance()->get(0,2);
				unsigned int direction = randgen->Instance()->get(0,1);
				if ( direction == 0 )
				{
					if ( XYZ == 0 )
						co->rot_x_1 += 0.01f;
					else if ( XYZ == 1 )
						co->rot_y_1 += 0.01f;
					else
						co->rot_z_1 += 0.01f;
				}
				else
				{
					if ( XYZ == 0 )
						co->rot_x_1 -= 0.01f;
					else if ( XYZ == 1 )
						co->rot_y_1 -= 0.01f;
					else
						co->rot_z_1 -= 0.01f;
				}

				XYZ = randgen->Instance()->get(0,2);
				direction = randgen->Instance()->get(0,1);
				if ( direction == 0 )
				{
					if ( XYZ == 0 )
						co->rot_x_2 += 0.01f;
					else if ( XYZ == 1 )
						co->rot_y_2 += 0.01f;
					else
						co->rot_z_2 += 0.01f;
				}
				else
				{
					if ( XYZ == 0 )
						co->rot_x_2 -= 0.01f;
					else if ( XYZ == 1 )
						co->rot_y_2 -= 0.01f;
					else
						co->rot_z_2 -= 0.01f;
				}

				if ( co->rot_x_1 < -0.1571f )
					co->rot_x_1 = -0.1571f;
				if ( co->rot_x_1 > 0.1571f )
					co->rot_x_1 = 0.1571f;
				if ( co->rot_y_1 < -0.1571f )
					co->rot_y_1 = -0.1571f;
				if ( co->rot_y_1 > 0.1571f )
					co->rot_y_1 = 0.1571f;
				if ( co->rot_z_1 < -0.1571f )
					co->rot_z_1 = -0.1571f;
				if ( co->rot_z_1 > 0.1571f )
					co->rot_z_1 = 0.1571f;

				if ( co->rot_x_2 < -0.1571f )
					co->rot_x_2 = -0.1571f;
				if ( co->rot_x_2 > 0.1571f )
					co->rot_x_2 = 0.1571f;
				if ( co->rot_y_2 < -0.1571f )
					co->rot_y_2 = -0.1571f;
				if ( co->rot_y_2 > 0.1571f )
					co->rot_y_2 = 0.1571f;
				if ( co->rot_z_2 < -0.1571f )
					co->rot_z_2 = -0.1571f;
				if ( co->rot_z_2 > 0.1571f )
					co->rot_z_2 = 0.1571f;

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
				unsigned int body1or2 = randgen->Instance()->get( 1, 2 );

				if ( body1or2 == 1 )
					randomConstraintPosition(co, 1, connID1);
				else
					randomConstraintPosition(co, 2, connID2);

// 				cerr << "done changing constraint position" << endl;
				continue;
			}

		// REPOSITION A CONSTRAINT SLIGHTLY
			modesum += settings->getCVar("body_percentmutateeffectchangeconstraintposition_slightly");
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
				unsigned int body1or2 = randgen->Instance()->get( 1, 2 );
				unsigned int direction = randgen->Instance()->get( 0, 1 );
				unsigned int axis1or2 = randgen->Instance()->get( 0, 1 );

				if ( body1or2 == 1 ) {
					// now we know the plane to connect to, determine positions
					if ( co->XYZ == 0 ) { // X
						if ( direction == 0 ) {
							if ( axis1or2 == 0 )	co->pos_y_1 += archBodyparts[connID1].y / 100000;
							else			co->pos_z_1 += archBodyparts[connID1].z / 100000;
						} else {
							if ( axis1or2 == 0 )	co->pos_y_1 -= archBodyparts[connID1].y / 100000;
							else			co->pos_z_1 -= archBodyparts[connID1].z / 100000;
						}
					}
					else if ( co->XYZ == 1 ) { // Y
						if ( direction == 0 ) {
							if ( axis1or2 == 0 )	co->pos_x_1 += archBodyparts[connID1].x / 100000;
							else			co->pos_z_1 += archBodyparts[connID1].z / 100000;
						} else {
							if ( axis1or2 == 0 )	co->pos_x_1 -= archBodyparts[connID1].x / 100000;
							else			co->pos_z_1 -= archBodyparts[connID1].z / 100000;
						}
					}
					else { // Z
						if ( direction == 0 ) {
							if ( axis1or2 == 0 )	co->pos_x_1 += archBodyparts[connID1].x / 100000;
							else			co->pos_y_1 += archBodyparts[connID1].y / 100000;
						} else {
							if ( axis1or2 == 0 )	co->pos_x_1 -= archBodyparts[connID1].x / 100000;
							else			co->pos_y_1 -= archBodyparts[connID1].y / 100000;
						}
					}
					if ( co->pos_x_1 < archBodyparts[connID1].x/-2000 )
						co->pos_x_1 = archBodyparts[connID1].x/-2000;
					if ( co->pos_x_1 > archBodyparts[connID1].x/2000 )
						co->pos_x_1 = archBodyparts[connID1].x/2000;
					if ( co->pos_y_1 < archBodyparts[connID1].y/-2000 )
						co->pos_y_1 = archBodyparts[connID1].y/-2000;
					if ( co->pos_y_1 > archBodyparts[connID1].y/2000 )
						co->pos_y_1 = archBodyparts[connID1].y/2000;
					if ( co->pos_z_1 < archBodyparts[connID1].z/-2000 )
						co->pos_z_1 = archBodyparts[connID1].z/-2000;
					if ( co->pos_z_1 > archBodyparts[connID1].z/2000 )
						co->pos_z_1 = archBodyparts[connID1].z/2000;
				}
				else {
					if ( !co->isMouthConstraint ) {
						// now we know the plane to connect to, determine positions
						if ( co->XYZ == 0 ) { // X
							if ( direction == 0 ) {
								if ( axis1or2 == 0 )	co->pos_y_2 += archBodyparts[connID2].y / 100000;
								else			co->pos_z_2 += archBodyparts[connID2].z / 100000;
							} else {
								if ( axis1or2 == 0 )	co->pos_y_2 -= archBodyparts[connID2].y / 100000;
								else			co->pos_z_2 -= archBodyparts[connID2].z / 100000;
							}
						}
						else if ( co->XYZ == 1 ) { // Y
							if ( direction == 0 ) {
								if ( axis1or2 == 0 )	co->pos_x_2 += archBodyparts[connID2].x / 100000;
								else			co->pos_z_2 += archBodyparts[connID2].z / 100000;
							} else {
								if ( axis1or2 == 0 )	co->pos_x_2 -= archBodyparts[connID2].x / 100000;
								else			co->pos_z_2 -= archBodyparts[connID2].z / 100000;
							}
						}
						else { // Z
							if ( direction == 0 ) {
								if ( axis1or2 == 0 )	co->pos_x_2 += archBodyparts[connID2].x / 100000;
								else			co->pos_y_2 += archBodyparts[connID2].y / 100000;
							} else {
								if ( axis1or2 == 0 )	co->pos_x_2 -= archBodyparts[connID2].x / 100000;
								else			co->pos_y_2 -= archBodyparts[connID2].y / 100000;
							}
						}
						if ( co->pos_x_2 < archBodyparts[connID2].x/-2000 )
							co->pos_x_2 = archBodyparts[connID2].x/-2000;
						if ( co->pos_x_2 > archBodyparts[connID2].x/2000 )
							co->pos_x_2 = archBodyparts[connID2].x/2000;
						if ( co->pos_y_2 < archBodyparts[connID2].y/-2000 )
							co->pos_y_2 = archBodyparts[connID2].y/-2000;
						if ( co->pos_y_2 > archBodyparts[connID2].y/2000 )
							co->pos_y_2 = archBodyparts[connID2].y/2000;
						if ( co->pos_z_2 < archBodyparts[connID2].z/-2000 )
							co->pos_z_2 = archBodyparts[connID2].z/-2000;
						if ( co->pos_z_2 > archBodyparts[connID2].z/2000 )
							co->pos_z_2 = archBodyparts[connID2].z/2000;
					}
					else {
						if ( co->XYZ == 0 ) { // X
							if ( direction == 0 ) {
								if ( axis1or2 == 0 )	co->pos_y_2 += archMouths[connID2].y / 100000;
								else			co->pos_z_2 += archMouths[connID2].z / 100000;
							} else {
								if ( axis1or2 == 0 )	co->pos_y_2 -= archMouths[connID2].y / 100000;
								else			co->pos_z_2 -= archMouths[connID2].z / 100000;
							}
						}
						else if ( co->XYZ == 1 ) { // Y
							if ( direction == 0 ) {
								if ( axis1or2 == 0 )	co->pos_x_2 += archMouths[connID2].x / 100000;
								else			co->pos_z_2 += archMouths[connID2].z / 100000;
							} else {
								if ( axis1or2 == 0 )	co->pos_x_2 -= archMouths[connID2].x / 100000;
								else			co->pos_z_2 -= archMouths[connID2].z / 100000;
							}
						}
						else { // Z
							if ( direction == 0 ) {
								if ( axis1or2 == 0 )	co->pos_x_2 += archMouths[connID2].x / 100000;
								else			co->pos_y_2 += archMouths[connID2].y / 100000;
							} else {
								if ( axis1or2 == 0 )	co->pos_x_2 -= archMouths[connID2].x / 100000;
								else			co->pos_y_2 -= archMouths[connID2].y / 100000;
							}
						}
						if ( co->pos_x_2 < archMouths[connID2].x/-2000 )
							co->pos_x_2 = archMouths[connID2].x/-2000;
						if ( co->pos_x_2 > archMouths[connID2].x/2000 )
							co->pos_x_2 = archMouths[connID2].x/2000;
						if ( co->pos_y_2 < archMouths[connID2].y/-2000 )
							co->pos_y_2 = archMouths[connID2].y/-2000;
						if ( co->pos_y_2 > archMouths[connID2].y/2000 )
							co->pos_y_2 = archMouths[connID2].y/2000;
						if ( co->pos_z_2 < archMouths[connID2].z/-2000 )
							co->pos_z_2 = archMouths[connID2].z/-2000;
						if ( co->pos_z_2 > archMouths[connID2].z/2000 )
							co->pos_z_2 = archMouths[connID2].z/2000;
					}
				}
					
// 					randomConstraintPosition(co, 2, connID2);

// 				cerr << "done changing constraint position" << endl;
				continue;
			}

		// REMOVE AND ADD MOUTH
			modesum += settings->getCVar("body_percentmutateeffectrepositionhead");
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

void BodyArch::repositiontoConstraints( archBodypart* bp )
{
	// reposition the constraints back to the resized bodypart / mouth
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
}

void BodyArch::repositiontoConstraints( archMouth* bp )
{
	// reposition the constraints back to the resized bodypart / mouth
	for ( int i = 0; i < (int)archConstraints.size(); i++ )
	{
		archConstraint* co = &archConstraints[i];
		if ( co->isMouthConstraint && findBodypart( co->id_2 ) == (int)bp->id )
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
}

int BodyArch::findBodypart( unsigned int id )
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

int BodyArch::findMouth( unsigned int id )
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

unsigned int BodyArch::getUniqueBodypartID()
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

unsigned int BodyArch::getUniqueConstraintID()
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

void BodyArch::copyFrom(const BodyArch* otherBody)
{
	for ( unsigned int i=0; i < otherBody->archBodyparts.size(); i++ )
	{
		const archBodypart *obp = &otherBody->archBodyparts[i];
		archBodyparts.push_back( archBodypart() );
		archBodypart *bp = &archBodyparts[archBodyparts.size()-1];
		
		bp->id		= obp->id;
		bp->type	= obp->type;
		bp->materialID	= obp->materialID;
		bp->x		= obp->x;
		bp->y		= obp->y;
		bp->z		= obp->z;
	}

	for ( unsigned int i=0; i < otherBody->archMouths.size(); i++ )
	{
		const archMouth *omo = &otherBody->archMouths[i];
		archMouths.push_back( archMouth() );
		archMouth *mo = &archMouths[archMouths.size()-1];
		
		mo->id		= omo->id;
		mo->x		= omo->x;
		mo->y		= omo->y;
		mo->z		= omo->z;
	}

	for ( unsigned int i=0; i < otherBody->archConstraints.size(); i++ )
	{
		const archConstraint *oco = &otherBody->archConstraints[i];
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

void BodyArch::setArch(string* content)
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


string* BodyArch::getArch()
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

BodyArch::~BodyArch()
{
}
