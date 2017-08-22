//
//  Francois Belanger 94 245 437
//
//  main.cpp
//  tp0
//
//  Created by Fran�ois B�langer on 17-05-15.
//  Copyright � 2017. All rights reserved.
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
	vector<ZoneTransit>zoneTransit(nbStep+1);

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
	for (int j = 0; j < numberOfRepeat; ++j)
	{
		before = high_resolution_clock::now();

		for (int i = 0; i < numberOfFiles; ++i)
			t5(fname, t4(t3(t2(t1(t0(fname)), keywords))), false);

		after = high_resolution_clock::now();
		cout << "total" << j + 1 << ": " << duration_cast<milliseconds>(after - before).count() << endl;
	}

	//Traitement parallele
	//TODO: to finish
	//vector<string> filenames(numberOfRepeat, fname);
	//threads.emplace_back(thread(Pipeline(zoneTransit[0], zoneTransit[1]), [](string fName) -> string { return t0(fName); }));
	//threads.emplace_back(thread(Pipeline(zoneTransit[1], zoneTransit[2]), [](string data) -> string { return t1(data); }));
	//threads.emplace_back(thread(Pipeline(zoneTransit[2], zoneTransit[3]), [&keywords](string data) -> string { return t2(data, keywords); }));
	//threads.emplace_back(thread(Pipeline(zoneTransit[3], zoneTransit[4]), [](string data) -> string { return t3(data); }));
	//threads.emplace_back(thread(Pipeline(zoneTransit[4], zoneTransit[5]), [](string data) -> string { return t4(data); }));
	//threads.emplace_back(thread(Pipeline(zoneTransit[5], zoneTransit[6]), [](string data) { return t5("test.html", data, true); }));

	//for_each(begin(threads), end(threads), [](thread t) { t.join(); });

	//cout << "t0 " << totalT0.count() << endl;
	//cout << "t1 " << totalT1.count() << endl;
	//cout << "t2 " << totalT2.count() << endl;
	//cout << "t3 " << totalT3.count() << endl;
	//cout << "t4 " << totalT4.count() << endl;
	//cout << "t5 " << totalT5.count() << endl;
	char a;
	cin >> a;
}