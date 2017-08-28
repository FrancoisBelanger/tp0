//
//  Francois Belanger 94 245 437
//
//  ZoneTransit.h
//  tp0
//
//  Created by François Bélanger on 17-05-15.
//  Copyright © 2017. All rights reserved.
//

#ifndef _PIPELINE_H_
#define _PIPELINE_H_

#include <mutex>
#include <condition_variable>
#include "zone_transit.h"

class Pipeline
{
protected:
	//int nbFiles;
	ZoneTransit& prev;
	ZoneTransit& next;
	size_t nbFiles;

public:
	Pipeline(size_t nb, ZoneTransit& prev, ZoneTransit& next): nbFiles(nb), prev(prev) ,next(next){}

	template<class F>
	void operator() (F f)
	{
		//for (size_t i = 0; i < nbFiles; ++i)
		if (!prev.is_done())
			next.enqueue(f(prev.deque()));
		else
			next.terminate();
	}


}; //struct Pipeline

class PipelineEntry
{
	size_t nbFiles;
	ZoneTransit& next;
	std::mutex& mut;
	std::condition_variable& cv;

public:

	PipelineEntry(size_t nb, ZoneTransit& next, std::condition_variable& cv, std::mutex& mut)
		:nbFiles(nb)
		, next(next)
		, cv(cv)
		, mut(mut)
	{}

	template<class F>
	void operator()(F f)
	{
		unique_lock<mutex> token(mut);
		cv.wait(token);

		for (int i = 0; i < nbFiles; ++i)
		{
			next.enqueue(f(i));
		}

		next.terminate();
	}
};


class PipelineExit
{
	ZoneTransit& prev;
	size_t nbFiles;

public:

	PipelineExit(size_t nb, ZoneTransit& prev)
		: prev(prev)
		, nbFiles(nb)
	{}

	template<class F>
	void operator()(F f)
	{
		//for (size_t i = 0; i < nbFiles; ++i)
		if (!prev.is_done())
			f(prev.deque());
		//else
		//	terminate();
	}
};
#endif //_PIPELINE_H