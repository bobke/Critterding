#include "clnbody.h"

CLNBody::CLNBody()
{
	cl = CLContext::Instance();

	delT = 0.0001f;
 	espSqr = 1.0f;
//         delT = 1.0f;
// 	espSqr = 100000.0f;
	numParticles = 8192;//8192;

	cl_int status;

	pos = NULL;
	vel = NULL;
	refPos = NULL;
	refVel =NULL;
	initVel = NULL;
	initPos = NULL;

	// make sure numParticles is multiple of group size
/*	numParticles = (cl_int)(((size_t)numParticles < groupSize) ? groupSize : numParticles);
	numParticles = (cl_int)((numParticles / groupSize) * groupSize);*/
	numBodies = numParticles;
	cerr << "bodies: " << numBodies << endl;

	initPos = (cl_float*)malloc(numBodies * sizeof(cl_float4));
	if(initPos == NULL) { cout << "Failed to allocate host memory. (initPos)" << endl; exit(1); }

	initVel = (cl_float*)malloc(numBodies * sizeof(cl_float4));
	if(initVel == NULL) { cout << "Failed to allocate host memory. (initVel)" << endl; exit(1); }

	#ifdef _WIN32
		pos = (cl_float*)_aligned_malloc(numBodies * sizeof(cl_float4), 16);
		vel = (cl_float*)_aligned_malloc(numBodies * sizeof(cl_float4), 16);
	#else
		pos = (cl_float*)memalign(16, numBodies * sizeof(cl_float4));
		vel = (cl_float*)memalign(16, numBodies * sizeof(cl_float4));
	#endif
	if(pos == NULL) { cout << "Failed to allocate host memory. (pos)" << endl; exit(1); }
	if(vel == NULL) { cout << "Failed to allocate host memory. (vel)" << endl; exit(1); }

	// Create and initialize memory objects
		/* Create memory objects for position */
		cl->createBuffer(updatedPos, numBodies * sizeof(cl_float4), pos, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR);
		/* Create memory objects for velocity */
		cl->createBuffer(updatedVel, numBodies * sizeof(cl_float4), vel, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR);
		/* get a kernel object handle for a kernel with the given name */
		cl->createKernel( kernel, "critterding_sim");
	
	// Set appropriate arguments to the kernel
		/* Particle positions */
		cl->setKernelArg( kernel, 0, sizeof(cl_mem), (void*)&updatedPos);
		/* Particle velocity */
		cl->setKernelArg( kernel, 1, sizeof(cl_mem), (void*)&updatedVel);
		/* numBodies */
		cl->setKernelArg( kernel, 2, sizeof(cl_int), (void*)&numBodies);
		/* time step */
		cl->setKernelArg( kernel, 3, sizeof(cl_float), (void*)&delT);
		/* upward Pseudoprobability */
		cl->setKernelArg( kernel, 4, sizeof(cl_float), (void*)&espSqr);
		/* local memory, localPos */ 
		cl->setKernelArg( kernel, 5, GROUP_SIZE * 4 * sizeof(float), NULL);

	cl->checkLocalMemsize(kernel);
	cl->checkWorkGroupsize(kernel);

	/* initialization of inputs */
	for(int i = 0; i < numBodies; ++i)
	{
		int index = 4 * i;
		// First 3 values are position in x,y and z direction
		for(int j = 0; j < 3; ++j)
			initPos[index + j] = randgen->Instance()->get(300, 1300);
		// Mass value
		initPos[index + 3] = randgen->Instance()->get(50, 700);
		// First 3 values are velocity in x,y and z direction
		for(int j = 0; j < 3; ++j)
			initVel[index + j] = randgen->Instance()->get(0, 0);
		// unused
		initVel[3] = 0.0f;
	}
	memcpy(pos, initPos, 4 * numBodies * sizeof(cl_float));
	memcpy(vel, initVel, 4 * numBodies * sizeof(cl_float));	

}

void CLNBody::process()
{
	cl_int status;

	size_t globalThreads[] = {numBodies};
	size_t localThreads[] = {cl->groupSize};
	if(localThreads[0] > cl->maxWorkItemSizes[0] || localThreads[0] > cl->maxWorkGroupSize) { std::cout << "Unsupported: Device does not support requested number of work items."; exit(1); }

	// Enqueue a kernel run call
	cl->enqueueNDRangeKernel( cl->commandQueue, kernel, 1, NULL, globalThreads, localThreads, 0, NULL, NULL);

//  	cl->flushCL(cl->commandQueue);
	cl->finish(cl->commandQueue);
	/* Enqueue readBuffer*/
	
	cl->enqueueReadBuffer( cl->commandQueue, updatedPos, CL_TRUE, 0, numBodies* sizeof(cl_float4), pos, 0, NULL, &cl->events[0]);
	/* Wait for the read buffer to finish execution */
	cl->waitForEvents(1, &cl->events[0]);
}

void CLNBody::draw()
{
	glColor3f(1.0f,1.6f,1.0f);
	glPointSize(1.0);
	glBegin(GL_POINTS);
	for(int i=0; i < numBodies; ++i)
		glVertex3d(pos[i*4+0]/100, pos[i*4+1]/100, pos[i*4+2]/100);
	glEnd();
}

CLNBody::~CLNBody()
{
	clReleaseKernel(kernel);
	clReleaseMemObject(updatedPos);
	clReleaseMemObject(updatedVel);
	free(initPos);
	free(initVel);
	#if defined _WIN32
		_aligned_free(pos);
		_aligned_free(vel);
	#else
		free(pos);
		free(vel);
	#endif
	free(refPos);
	free(refVel);
}
