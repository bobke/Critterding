#ifndef BRAINSTORE_H
#define BRAINSTORE_H

#include <pthread.h>
#include <vector>
#include <brainz.h>
#include "../utils/randgen.h"

struct brainuser
{
	bool processed;
	unsigned int results;
	unsigned int misses;
	float weightedresult;

	Brainz		brain;
};

struct query
{
	vector<int>* question;
	unsigned int answer;
};


class brainstore
{
	public:
		brainstore();
		~brainstore();

		RandGen				randgen;

		unsigned int			selectBrains;
	
		void				load(unsigned int inputs, unsigned int outputs);
		void				load(string* arch);
		void				process();
		void				setQuery(vector<int>* question, unsigned int answer);
		void				resetCorrCounts();

		vector<int>*			currentPicture;

		vector<struct brainuser*>	brainusers;
		pthread_mutex_t			brainusers_mutex;

		vector<struct query*>		queries;

		// threading
		pthread_cond_t			condition_startthreads;
		pthread_mutex_t			condition_startthreads_mutex;

		pthread_cond_t			condition_threadsdone;
		pthread_mutex_t			condition_threadsdone_mutex;

		unsigned int			nthreads;
		unsigned int			registeredThreads;
		unsigned int			busyThreads;
		pthread_mutex_t			busyThreads_mutex;

		vector<pthread_t>		threads;

		unsigned int			weightCounter;
		bool				weightDoSmall;

	private:



};

#endif
