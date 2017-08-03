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

using namespace std;
using namespace chrono;

int main(int argc, const char * argv[])
{
	auto before = chrono::high_resolution_clock::now();
	string fname = "main.cpp";
	vector<thread> threads;

	if (argc >= 2)
	{
		//TODO: initialiser un vecteur avec tout les nom de fichier
		fname = argv[1];
	}
	else
	{
		//TODO: initialiser un vecteur de nom de fichier
	}

	//TODO: to finish
	threads.emplace_back(thread());

	//FIXME placer ailleur
	KEYWORDS;
	//Traitement sequentiel
	for (int j = 0; j < 10; ++j)
	{
		auto before = chrono::high_resolution_clock::now();

		for (int i = 0; i < 1000; ++i)
			t5(fname, t4(t3(t2(t1(t0(fname)), keywords))), false);

		cout << "total" << j+1 << ": " << duration_cast<milliseconds>(high_resolution_clock::now() - before).count() << endl;
	}

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