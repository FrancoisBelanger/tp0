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

#include "zone_transit.h"

class Pipeline
{
	//int nbFiles;
	ZoneTransit* prev;
	ZoneTransit* next;

public:
	//Pipeline(int nbFiles, ZoneTransit& next, condition_variable& cv, mutex& mut)
	//	: nbFiles(nbFiles)
	//	, next(next)
	//	, cv(cv)
	//	, mut(mut)
	//{}

	template<class F>
	void operator() (F f)
	{
		unique_lock<mutex> lock(mut);
		cv.wait(lock);

		for (int i = 0; i < nbFiles; ++i)
		{
			next->enqueue(f(prev->deque()));
		}
	}
/*
	void operator()(F f)
	{
	unique_lock<mutex> lock(mut);
	cv.wait(lock);

	for (int fileIndex = 0; fileIndex < nbFiles; ++fileIndex)
	{
	next.put(f(fileIndex));
	}
}*/

}; //struct Pipeline

#endif //_PIPELINE_H