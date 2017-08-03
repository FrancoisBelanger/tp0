//
//  Francois Belanger 94 245 437
//
//  ZoneTransit.h
//  tp0
//
//  Created by Fran�ois B�langer on 17-05-15.
//  Copyright � 2017. All rights reserved.
//

#ifndef _PIPELINE_H_
#define _PIPELINE_H_

class Pipeline
{
	//int nbFiles;
	//ZoneTransit& next;

	//mutex& mut;
	//condition_variable& cv;

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

		for (int fileIndex = 0; fileIndex < nbFiles; ++fileIndex)
		{
			next.put(f(fileIndex));
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