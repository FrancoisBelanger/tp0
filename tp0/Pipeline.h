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

//FIXME to rename
//FIXME to integrate
class BeginThread
{
	ZoneTransit& next;

public:

	BeginThread(ZoneTransit& next)
		: next(next)
	{}

	template<class F>
	void operator()(F f)
	{
		//for (int fileIndex = 0; fileIndex < nbFiles; ++fileIndex)
		{
			next.enqueue(f(fileIndex));
		}
	}
};

class Pipeline
{
	//int nbFiles;
	ZoneTransit& prev;
	ZoneTransit& next;

public:
	Pipeline(ZoneTransit& prev, ZoneTransit& next): prev(prev) ,next(next){}

	template<class F>
	void operator() (F f)
	{
		next.enqueue(f(prev.deque()));
	}


}; //struct Pipeline

//FIXME to rename
//FIXME to integrate
class EndThread
{
	ZoneTransit& prev;

public:

	EndThread(ZoneTransit& prev)
		: prev(prev)
	{}

	template<class F>
	void operator()(F f)
	{
		for (int fileIndex = 0; fileIndex < nbFiles; ++fileIndex)
		{
			f(fileIndex, prev.get());
		}
	}
};
#endif //_PIPELINE_H