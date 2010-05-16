#include "bodypart.h"

Bodypart::Bodypart(btDynamicsWorld* ownerWorld, void* owner, const btVector3& dimensions, float weight, btTransform& offset, btTransform& transform)
{
	m_ownerWorld = ownerWorld;

	shape = new btBoxShape( dimensions );

	btVector3 localInertia(0,0,0);
	if (weight != 0.f) // weight of non zero = dynamic
		shape->calculateLocalInertia(weight,localInertia);

	myMotionState = new btDefaultMotionState(offset*transform);
	
	btRigidBody::btRigidBodyConstructionInfo rbInfo(weight,myMotionState,shape,localInertia);
	body = new btRigidBody(rbInfo);

	body->setUserPointer(owner);
// 	body->setDamping(0.05, 0.85);
	body->setDamping(0.05, 0.85);
	body->setDeactivationTime(0.001);
	body->setSleepingThresholds(1.6, 2.5);

	m_ownerWorld->addRigidBody(body);
	sc = 0;
}

ShapeCache* Bodypart::cache(btConvexShape* shape)
{
	if(!sc)
	{
		sc = new(btAlignedAlloc(sizeof(ShapeCache),16)) ShapeCache(shape);
		sc->m_shapehull.buildHull(shape->getMargin());

		/* Build edges	*/ 
		const int			ni=sc->m_shapehull.numIndices();
		const int			nv=sc->m_shapehull.numVertices();
		const unsigned int*	pi=sc->m_shapehull.getIndexPointer();
		const btVector3*	pv=sc->m_shapehull.getVertexPointer();
		btAlignedObjectArray<ShapeCache::Edge*>	edges;
		sc->m_edges.reserve(ni);
		edges.resize(nv*nv,0);
		for(int i=0;i<ni;i+=3)
		{
			const unsigned int* ti=pi+i;
			const btVector3		nrm=btCross(pv[ti[1]]-pv[ti[0]],pv[ti[2]]-pv[ti[0]]).normalized();
			for(int j=2,k=0;k<3;j=k++)
			{
				const unsigned int	a=ti[j];
				const unsigned int	b=ti[k];
				ShapeCache::Edge*&	e=edges[btMin(a,b)*nv+btMax(a,b)];
				if(!e)
				{
					sc->m_edges.push_back(ShapeCache::Edge());
					e=&sc->m_edges[sc->m_edges.size()-1];
					e->n[0]=nrm;e->n[1]=-nrm;
					e->v[0]=a;e->v[1]=b;
				}
				else
				{
					e->n[1]=nrm;
				}
			}
		}
	}
	return(sc);
}

Bodypart::~Bodypart()
{
	// Remove all bodies and shapes
	m_ownerWorld->getBroadphase()->getOverlappingPairCache()->cleanProxyFromPairs(body->getBroadphaseHandle(),m_ownerWorld->getDispatcher());
	m_ownerWorld->removeRigidBody(body);
	delete myMotionState;
	delete shape;
// 	delete body->getMotionState();
	delete body;

	if (sc)
	{
		sc->~ShapeCache();
		btAlignedFree(sc);
	}
}


