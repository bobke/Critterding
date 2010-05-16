#include "concavefloor.h"

Concavefloor::Concavefloor()
{
	gVertices = 0;
	gIndices = 0;
	trimeshShape = 0;
	m_indexVertexArrays = 0;
	fixedGround = 0;
	serializer = 0;

	aabbMin = btVector3(-1000,-1000,-1000);
	aabbMax = btVector3(1000,1000,1000);

	serializer = new btDefaultSerializer(1024*1024*5);
// 		serializer->setSerializationFlags(BT_SERIALIZE_NO_BVH);//	or BT_SERIALIZE_NO_TRIANGLEINFOMAP
}

void Concavefloor::init()
{
	worldsizeZ = settings->getCVarPtr("worldsizeZ");

	makeFloor();

	if ( settings->getCVar("autoload") )
		loadAllCritters();
	if ( settings->getCVar("autoloadlastsaved") )
		loadAllLastSavedCritters();
}

void Concavefloor::process()
{
	if ( !pause )
	{
		killHalf();
		expireFood();
		autoinsertFood();
		expireCritters();
		autoexchangeCritters();
		autosaveCritters();
		autoinsertCritters();
		
		if ( *critter_raycastvision == 0 )
		{
			renderVision();
			grabVision();
		}

		// do a bullet step
			m_dynamicsWorld->stepSimulation(0.016667f, 0, 0.016667f);

		int lmax = (int)critters.size();
		CritterB *c;
		float freeEnergyc = 0.0f;

		// FIXME USE FROM WORLDB
		omp_set_num_threads( *threads );
		#pragma omp parallel for ordered shared(freeEnergyc, lmax) private(c) // ordered 
		for( int i=0; i < lmax; i++)
		{
			c = critters[i];
			
			omp_set_lock(&my_lock1);
				checkCollisions(  c );
			omp_unset_lock(&my_lock1);

			// process
				c->process();

			// record critter used energy
				freeEnergyc += c->energyUsed;

			// process Output Neurons
				eat(c);

			// procreation if procreation energy trigger is hit
			omp_set_lock(&my_lock1);
				procreate(c);
			omp_unset_lock(&my_lock1);
		}

		freeEnergy += freeEnergyc;

		getGeneralStats();
	}
}

void Concavefloor::setVertexPositions(float waveheight, float offset)
{
	for ( int i=0;i<NUM_VERTS_X;i++ )
		for ( int j=0;j<NUM_VERTS_Y;j++ )
			gVertices[ i+j*NUM_VERTS_X ].setValue( (i-NUM_VERTS_X*0.5f) * TRIANGLE_SIZE, waveheight*sinf((float)i+offset)*cosf((float)j+offset), (j-NUM_VERTS_Y*0.5f)*TRIANGLE_SIZE );
}

void Concavefloor::makeFloor()
{
// 	for ( unsigned int i=0; i < walls.size(); i++ )	
// 		delete walls[i];
// 	walls.clear();
	for ( int i=0; i < entities.size(); i++ )
	{
		if ( entities[i]->type == WALL )
		{
			delete entities[i];
			entities.erase(entities.begin()+i);
			i--;
		}
	}

	// Wall Constants
		float WallWidth = 0.5f;
		float WallHalfWidth = WallWidth/2.0f;
		float WallHeight = 2.0f;
		float WallHalfHeight = WallHeight/2.0f;

		border = 1;
		waveheight = (float)*worldsizeZ / 10; // 5.0f
		TRIANGLE_SIZE = 1.0f; // 8.f
// 		NUM_VERTS_X = *worldsizeX/3 + 1 + border*2;  // 30
// 		NUM_VERTS_Y = *worldsizeY/3 + 1 + border*2;  // 30
		NUM_VERTS_X = *worldsizeX + 1;  // 30
		NUM_VERTS_Y = *worldsizeY + 1;  // 30
		totalVerts = NUM_VERTS_X*NUM_VERTS_Y;

	// Ground Floor
// 		btVector3 position( *worldsizeX/2.0f, -WallHalfWidth - waveheight, *worldsizeY/2.0f );
// 		Wall* w = new Wall( *worldsizeX, WallWidth, *worldsizeY, position, m_dynamicsWorld );
// 		w->color.r = 0.30f; w->color.g = 0.20f; w->color.b = 0.10f;
// 		walls.push_back(w);
	
	if ( settings->getCVar("worldwalls") )
	{
		// Left Wall
			btVector3 position = btVector3 ( 0.0f-WallHalfWidth, WallHalfHeight-WallWidth, *worldsizeY/2.0f );
			Wall* w = new Wall( WallWidth, WallHeight, *worldsizeY, position, m_dynamicsWorld );
			w->color.r = 0.34f; w->color.g = 0.25f; w->color.b = 0.11f;
			entities.push_back(w);
		// Right Wall
			position = btVector3 ( *worldsizeX+WallHalfWidth, WallHalfHeight-WallWidth, *worldsizeY/2.0f );
			w = new Wall( WallWidth, WallHeight, *worldsizeY, position, m_dynamicsWorld );
			w->color.r = 0.34f; w->color.g = 0.25f; w->color.b = 0.11f;
			entities.push_back(w);
		// Top Wall
			position = btVector3 ( *worldsizeX/2.0f, WallHalfHeight-WallWidth, 0.0f-WallHalfWidth );
			w = new Wall( *worldsizeX+(WallWidth*2), WallHeight, WallWidth, position, m_dynamicsWorld );
			w->color.r = 0.34f; w->color.g = 0.25f; w->color.b = 0.11f;
			entities.push_back(w);
		// Bottom Wall
			position = btVector3 ( *worldsizeX/2.0f, WallHalfHeight-WallWidth, *worldsizeY+WallHalfWidth );
			w = new Wall( *worldsizeX+(WallWidth*2), WallHeight, WallWidth, position, m_dynamicsWorld );
			w->color.r = 0.34f; w->color.g = 0.25f; w->color.b = 0.11f;
			entities.push_back(w);
	}
 
	if ( trimeshShape > 0 )
		delete trimeshShape;
	if ( fixedGround > 0 )
	{
		m_dynamicsWorld->removeRigidBody(fixedGround);
		delete fixedGround;
	}
	if ( m_indexVertexArrays > 0 )
		delete m_indexVertexArrays;
	if ( gVertices > 0 )
		delete gVertices;
	if ( gIndices > 0 )
		delete gIndices;

	int vertStride = sizeof(btVector3);
	int indexStride = 3*sizeof(int);
	const int totalTriangles = 2*(NUM_VERTS_X-1)*(NUM_VERTS_Y-1);
	gVertices = new btVector3[totalVerts];
	gIndices = new int[totalTriangles*3];
	setVertexPositions(waveheight,0.f);

	int index=0;
	for ( int i=0;i<NUM_VERTS_X-1;i++ )
	{
		for ( int j=0;j<NUM_VERTS_Y-1;j++ )
		{
			gIndices[index++] = j*NUM_VERTS_X+i;
			gIndices[index++] = j*NUM_VERTS_X+i+1;
			gIndices[index++] = (j+1)*NUM_VERTS_X+i+1;

			gIndices[index++] = j*NUM_VERTS_X+i;
			gIndices[index++] = (j+1)*NUM_VERTS_X+i+1;
			gIndices[index++] = (j+1)*NUM_VERTS_X+i;
		}
	}

	m_indexVertexArrays = new btTriangleIndexVertexArray(totalTriangles, gIndices, indexStride, totalVerts,(btScalar*) &gVertices[0].x(),vertStride);
	trimeshShape = new btBvhTriangleMeshShape(m_indexVertexArrays,true,aabbMin,aabbMax);

	serializer->startSerialization();
//		trimeshShape->serializeSingleShape(serializer);
	trimeshShape->serializeSingleBvh(serializer);
	serializer->finishSerialization();
	
	groundTransform.setIdentity();
	groundTransform.setOrigin( btVector3((float)*worldsizeX/2 + 0.5f, 0, (float)*worldsizeY/2 + 0.5f) );

	fixedGround = new btRigidBody(0,0,trimeshShape,btVector3(0,0,0));	
	fixedGround->setWorldTransform(groundTransform);
	m_dynamicsWorld->addRigidBody(fixedGround);
}


void Concavefloor::drawWithGrid()
{
	glClear(GL_STENCIL_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

 	drawfloor(1.0f);
	for( unsigned int i=0; i < critters.size(); i++)
		critters[i]->draw(true);

	for( unsigned int i=0; i < entities.size(); i++)
		entities[i]->draw();

	if ( *drawshadows )
	{
		btVector3 aabbMin,aabbMax;
		m_dynamicsWorld->getBroadphase()->getBroadphaseAabb(aabbMin,aabbMax);
		aabbMin-=btVector3(BT_LARGE_FLOAT,BT_LARGE_FLOAT,BT_LARGE_FLOAT);
		aabbMax+=btVector3(BT_LARGE_FLOAT,BT_LARGE_FLOAT,BT_LARGE_FLOAT);
		btScalar mmatrix[16];
		btVector3 sundir = btVector3(0.3f, -1.0f, 0.3f);


		glDisable(GL_LIGHTING);
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_STENCIL_TEST);
		glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
		glStencilFunc(GL_ALWAYS,1,0xFFFFFFFFL);
		glFrontFace(GL_CCW);
		glStencilOp(GL_KEEP,GL_KEEP,GL_INCR);

		for( unsigned int i=0; i < critters.size(); i++)
		{
			for ( unsigned int bp = 0; bp < critters[i]->body.bodyparts.size(); bp++ )
			{
				critters[i]->body.bodyparts[bp]->myMotionState->m_graphicsWorldTrans.getOpenGLMatrix(mmatrix);
				drawShadow(mmatrix, sundir * critters[i]->body.bodyparts[bp]->myMotionState->m_graphicsWorldTrans.getBasis() ,critters[i]->body.bodyparts[bp]->shape, critters[i]->body.bodyparts[bp], aabbMin,aabbMax);
			}
		}
		for( unsigned int i=0; i < entities.size(); i++)
		{
			if ( entities[i]->type == FOOD )
			{
				Food* f = static_cast<Food*>(entities[i]);
				f->myMotionState->m_graphicsWorldTrans.getOpenGLMatrix(mmatrix);
				drawShadow(mmatrix,sundir * f->myMotionState->m_graphicsWorldTrans.getBasis(),f->body.bodyparts[0]->shape, f->body.bodyparts[0], aabbMin, aabbMax);

			}
		}

		glFrontFace(GL_CW);
		glStencilOp(GL_KEEP,GL_KEEP,GL_DECR);

		for( unsigned int i=0; i < critters.size(); i++)
		{
			for ( unsigned int bp = 0; bp < critters[i]->body.bodyparts.size(); bp++ )
			{
				critters[i]->body.bodyparts[bp]->myMotionState->m_graphicsWorldTrans.getOpenGLMatrix(mmatrix);
				drawShadow(mmatrix, sundir * critters[i]->body.bodyparts[bp]->myMotionState->m_graphicsWorldTrans.getBasis() ,critters[i]->body.bodyparts[bp]->shape, critters[i]->body.bodyparts[bp], aabbMin,aabbMax);
			}
		}
		for( unsigned int i=0; i < entities.size(); i++)
		{
			if ( entities[i]->type == FOOD )
			{
				Food* f = static_cast<Food*>(entities[i]);
				f->myMotionState->m_graphicsWorldTrans.getOpenGLMatrix(mmatrix);
				drawShadow(mmatrix,sundir * f->myMotionState->m_graphicsWorldTrans.getBasis(),f->body.bodyparts[0]->shape, f->body.bodyparts[0], aabbMin, aabbMax);

			}
		}

		glDepthMask(GL_TRUE);
		glFrontFace(GL_CCW);
		glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glStencilFunc( GL_NOTEQUAL, 0, 0xFFFFFFFFL );
		glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );
		glDisable(GL_LIGHTING);

		for( unsigned int i=0; i < critters.size(); i++)
			critters[i]->drawDimmed(0.6f);

		for( unsigned int i=0; i < entities.size(); i++)
			entities[i]->drawDimmed(0.6f);
		drawfloor(0.1f);

	}
	glDisable(GL_STENCIL_TEST);
	glDisable(GL_CULL_FACE);
}

// void Concavefloor::childPositionOffset(btVector3* v)
// {
// 	*v+= (v->normalized()*insertHight);
// }

// btVector3 Concavefloor::findPosition()
// {
// 	return btVector3(	((float)randgen->Instance()->get( 0, 200 )-100.0f) / 100,
// 				((float)randgen->Instance()->get( 0, 200 )-100.0f) / 100,
// 				((float)randgen->Instance()->get( 0, 200 )-100.0f) / 100
// 	).normalized() * ( *worldsizeX + insertHight);
// }

void Concavefloor::drawfloor(float dim)
{
	glPushMatrix(); 
		glTranslatef((float)*worldsizeX/2 + 0.5f, 0, (float)*worldsizeY/2 + 0.5f);
		glColor4f( 0.3f * dim, 0.2f * dim, 0.1f * dim, 0.0f );
		trimeshShape->processAllTriangles(&drawCallback,aabbMin,aabbMax);
	glPopMatrix(); 
// 	for( unsigned int i=0; i < walls.size(); i++)
// 		walls[i]->draw();
}

Concavefloor::~Concavefloor()
{
	m_dynamicsWorld->removeRigidBody(fixedGround);
	delete fixedGround;
	delete m_indexVertexArrays;
	delete gVertices;
	delete gIndices;
	delete trimeshShape;
	delete serializer;
}
