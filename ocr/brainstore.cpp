#include "brainstore.h"

extern "C" void *procCritters( void *ptr )
{

	brainstore *b = static_cast<brainstore *>(ptr);

	// register this thread
	unsigned int threadID;
	pthread_mutex_lock( &b->busyThreads_mutex );
		threadID = b->registeredThreads++;
	pthread_mutex_unlock( &b->busyThreads_mutex );

	while (1)
	{
		// thread stuff
			pthread_mutex_lock( &b->condition_startthreads_mutex );
	
				pthread_mutex_lock( &b->busyThreads_mutex );
					b->busyThreads--;
					if ( b->busyThreads == 0 )
					{
						pthread_mutex_lock( &b->condition_threadsdone_mutex );
							//cerr << "signaling threads done" << endl;
							pthread_cond_signal( &b->condition_threadsdone );
						pthread_mutex_unlock( &b->condition_threadsdone_mutex );
					}
				pthread_mutex_unlock( &b->busyThreads_mutex );
	
			pthread_cond_wait( &b->condition_startthreads, &b->condition_startthreads_mutex );
					//cerr << "thread " << threadID << " initiated" << endl;
			pthread_mutex_unlock( &b->condition_startthreads_mutex );


		// process

			for ( unsigned int i=threadID; i < b->selectBrains; i+=b->nthreads )
			{
				// insert a copy and mutate it
// 					unsigned int nid = b->copyandmutate(i);

					brainuser *bu = new brainuser;
				
					pthread_mutex_lock( &b->brainusers_mutex );
						brainuser *other = b->brainusers[i];
						b->brainusers.push_back( bu );
					pthread_mutex_unlock( &b->brainusers_mutex );
				
					string* arch = other->brain.getArch();
					bu->brain.setArch(arch);
				
					bu->brain.mutate( b->randgen.get( 1, 10 ) );
				
					bu->brain.wireArch();
				
					bu->results = 0;
					bu->misses = 0;
					bu->weightedresult = 0.0f;

				// ask this brain ALL questions
					for ( unsigned int p = 0; p < b->queries.size(); p++ )
					{
						query* q = b->queries.at(p);

/*					// first link inputs to picture
						for ( unsigned int j=0; j < q->question->size(); j++ )
						{
							if ( q->question->at(j) > 0 )
							{
								bu->brain.Inputs[j].output = 1;
							}
							else
							{
								bu->brain.Inputs[j].output = 0;
							}
						}*/

						for ( unsigned int j=0; j < q->question->size(); j++ )
						{
							unsigned target = j * 10;
							unsigned int NeuronToFire = (unsigned int)(((float)q->question->at(j) / 256.0f) * 10);
							for ( unsigned int z=0; z < 10; z++ )
							{
								if ( q->question->at(j)>0 && z == NeuronToFire  )	bu->brain.Inputs[target+z].output = 1;
								else							bu->brain.Inputs[target+z].output = 0;
							}
						}
//cerr << "hi" << endl;

				
					// process brain
						bu->brain.processTillAnswer();

					// check the answer
						bool Correct = true;
						for ( unsigned int j = 0; j < bu->brain.numberOfOutputs; j++ )
						{
		//					cerr << j << ": " << bstore->brains[i]->Outputs[j].output << endl;;
		
							// if output is YES but it ISN'T expected
							if ( bu->brain.Outputs[j].output > 0 && j != q->answer )
								bu->misses += bu->brain.Outputs[j].output;
		
							// if output is NO but it IS expected
							else if ( bu->brain.Outputs[j].output == 0 && j == q->answer )
								Correct = false;

							// if output is YES
							else if ( bu->brain.Outputs[j].output > 0 && j == q->answer )
							{
								Correct = true;
								// account too many as misses
								bu->misses += bu->brain.Outputs[j].output-1;
							}
						}
		
						if ( Correct)
							bu->results++;
					}

				// (re)calculate both their weights
					bu->weightedresult = (1.0f * bu->results) - (0.09f * bu->misses);
					other->weightedresult = (1.0f * other->results) - (0.09f * other->misses);

					if ( b->weightDoSmall )
					{
// 						bu->weightedresult	-= (float)(bu->brain.totalNeurons + (3*bu->brain.totalSynapses) + bu->brain.neuronsFired)/10000.0f;
// 						other->weightedresult	-= (float)(other->brain.totalNeurons + (3*other->brain.totalSynapses) + other->brain.neuronsFired)/10000.0f;

						bu->weightedresult	-= (float)bu->brain.totalSynapses/10000.0f;
						other->weightedresult	-= (float)other->brain.totalSynapses/10000.0f;
					}
			}
	}
	return 0;
}

brainstore::brainstore()
{
	selectBrains			= 0;

	weightCounter			= 0;
	weightDoSmall			= false;

	// threads
	nthreads			= 3;
	registeredThreads		= 0;
	busyThreads			= nthreads;

	pthread_mutex_init (&condition_startthreads_mutex, NULL);
	pthread_cond_init (&condition_startthreads, NULL);

	pthread_mutex_init (&condition_threadsdone_mutex, NULL);
	pthread_cond_init (&condition_threadsdone, NULL);

	pthread_mutex_init (&busyThreads_mutex, NULL);

	pthread_mutex_init (&brainusers_mutex, NULL);


	// init threads
	for ( unsigned int i = 0; i < nthreads; i++ )
	{
		threads.push_back( pthread_t() );
		pthread_create( &threads[i], NULL, ::procCritters, (void *) this );
		pthread_detach( threads[i] );
	}

	// wait untill all threads are created before continuing
	pthread_mutex_lock( &busyThreads_mutex );
	while ( busyThreads > 0 )
	{
		pthread_mutex_unlock( &busyThreads_mutex );
			usleep (100);
		pthread_mutex_lock( &busyThreads_mutex );
	}
	pthread_mutex_unlock( &busyThreads_mutex );


}

void brainstore::load(unsigned int inputs, unsigned int outputs)
{
	brainuser *buser = new brainuser;

	buser->brain.numberOfInputs = inputs;
	buser->brain.numberOfOutputs = outputs;

	buser->brain.minSynapses				= 1;
	buser->brain.minNeuronsAtBuildtime			= 1;
	buser->brain.maxNeurons					= 100;
	buser->brain.maxNeuronsAtBuildtime			= 1;
	buser->brain.minSynapsesAtBuildtime			= 1;
	buser->brain.maxSynapses				= 20;
	buser->brain.maxSynapsesAtBuildtime			= 20;
	buser->brain.percentMutation				= 1;
	buser->brain.percentChanceInhibitoryNeuron		= 50;
	buser->brain.percentChanceConsistentSynapses		= 0;
	buser->brain.percentChanceInhibitorySynapses		= 50;
	buser->brain.percentChanceMotorNeuron			= 50;
	buser->brain.percentChancePlasticNeuron			= 0;
	buser->brain.percentChanceSensorySynapse		= 50;
	buser->brain.minFiringThreshold				= 3;
	buser->brain.maxFiringThreshold				= 10;
	buser->brain.maxDendridicBranches			= 3;
	buser->brain.percentMutateEffectAddNeuron		= 39;
	buser->brain.percentMutateEffectRemoveNeuron		= 1;
	buser->brain.percentMutateEffectAlterNeuron		= 20;
	buser->brain.percentMutateEffectAddSynapse		= 39;
	buser->brain.percentMutateEffectRemoveSynapse		= 1;

	buser->brain.buildArch();
	buser->brain.wireArch();

	buser->results = 0;
	buser->misses = 0;
	buser->weightedresult = 0.0f;

	brainusers.push_back( buser );
}

void brainstore::load(string* arch)
{
	brainuser *buser = new brainuser;

	buser->brain.setArch(arch);

	buser->brain.wireArch();

	buser->results = 0;
	buser->misses = 0;
	buser->weightedresult = 0.0f;

	brainusers.push_back( buser );
}

void brainstore::setQuery(vector<int>* question, unsigned int answer)
{
	query* q = new query();
	q->question = question;
	q->answer = answer;
	queries.push_back(q);
}

void brainstore::process()
{

	weightDoSmall = true;
	weightCounter++;
	if ( weightCounter > 101 )
	{
		weightDoSmall = false;
		cerr << "UNWEIGHTED" << endl;

		if ( weightCounter == 104 )
			weightCounter = 0;
	}

	// tell threads to start & wait for end
		busyThreads = nthreads;

		pthread_mutex_lock( &condition_threadsdone_mutex );
		// start the threads
			pthread_mutex_lock( &condition_startthreads_mutex );
				//cerr << "signaling start threads" << endl;
				pthread_cond_broadcast( &condition_startthreads );
			pthread_mutex_unlock( &condition_startthreads_mutex );

		// wait for threads to end
			pthread_cond_wait( &condition_threadsdone, &condition_threadsdone_mutex );
		pthread_mutex_unlock( &condition_threadsdone_mutex );



}

brainstore::~brainstore()
{
}


