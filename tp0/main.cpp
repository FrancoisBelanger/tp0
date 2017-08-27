//
//  Francois Belanger 94 245 437
//
//  main.cpp
//  tp0
//
//  Created by François Bélanger on 17-05-15.
//  Copyright © 2017. All rights reserved.
//

//TODO: fbr to remove
#include <iostream>

#include <vector>
#include <chrono>
#include <thread>
#include <algorithm>

#include "transform.h"
#include "zone_transit.h"
#include "Pipeline.h"

using namespace std;
using namespace chrono;

int main(int argc, const char * argv[])
{
	//FIXME remplacer par un enum
	const int nbStep = 6;
	int numberOfRepeat = 1;
	int numberOfFiles = 1000;
	string fname = "main.cpp";
	vector<thread> threads;
	vector<ZoneTransit>zoneTransit(nbStep);
	condition_variable cv;
	mutex mut;

	if (argc >= 2)
	{
		//TODO: initialiser un vecteur avec tout les nom de fichier
		fname = argv[1];
	}
	else
	{
		//TODO: initialiser un vecteur de nom de fichier
	}

	//FIXME placer ailleur
	KEYWORDS;
	//Traitement sequentiel

	high_resolution_clock::time_point before, after;
	//for (int j = 0; j < numberOfRepeat; ++j)
	//{
	//	before = high_resolution_clock::now();

	//	for (int i = 0; i < numberOfFiles; ++i)
	//		t5(t4(t3(t2(t1(t0_seq(fname)), keywords))));

	//	after = high_resolution_clock::now();
	//	cout << "total" << j + 1 << ": " << duration_cast<milliseconds>(after - before).count() << endl;
	//}

	//Traitement parallele
	//TODO: to finish
	vector<string> filenames(numberOfRepeat, fname);
	
	//threads.emplace_back(thread(Pipeline(zoneTransit[0], zoneTransit[1]), [](string fName) -> string { return t0_seq(fName); }));
	//threads.emplace_back(thread(Pipeline(zoneTransit[0], zoneTransit[1]), [&filenames](int index) -> string { return t0_seq(filenames[index]); }));
	threads.emplace_back(thread(PipelineEntry(filenames.size(), zoneTransit[0], cv, mut), [&filenames](int index) -> string { return t0_par(filenames[index]); }));
	threads.emplace_back(thread(Pipeline(filenames.size(), zoneTransit[0], zoneTransit[1]), [](string data) -> string { return t1(data); }));
	threads.emplace_back(thread(Pipeline(filenames.size(), zoneTransit[1], zoneTransit[2]), [&keywords](string data) -> string { return t2(data, keywords); }));
	threads.emplace_back(thread(Pipeline(filenames.size(), zoneTransit[2], zoneTransit[3]), [](string data) -> string { return t3(data); }));
	threads.emplace_back(thread(Pipeline(filenames.size(), zoneTransit[3], zoneTransit[4]), [](string data) -> string { return t4(data); }));
	//threads.emplace_back(thread(Pipeline(zoneTransit[5], zoneTransit[6]), [](string data) { return t5(data); }));
	threads.emplace_back(thread(PipelineExit(filenames.size(), zoneTransit[4]), [](string data) { return t5(data); }));

	before = high_resolution_clock::now();
	cv.notify_one();
	for (auto &th : threads)
	{
		th.join();
	}

	after = high_resolution_clock::now();
	cout << "total parallel" << ": " << duration_cast<milliseconds>(after - before).count() << endl;

	//cout << "t0 " << totalT0.count() << endl;
	//cout << "t1 " << totalT1.count() << endl;
	//cout << "t2 " << totalT2.count() << endl;
	//cout << "t3 " << totalT3.count() << endl;
	//cout << "t4 " << totalT4.count() << endl;
	//cout << "t5 " << totalT5.count() << endl;*/
	char a;
	cin >> a;
}