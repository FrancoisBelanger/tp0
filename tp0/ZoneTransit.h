//
//  Francois Belanger 94 245 437
//
//  ZoneTransit.h
//  tp0
//
//  Created by François Bélanger on 17-05-15.
//  Copyright © 2017. All rights reserved.
//

#ifndef _ZONE_TRANSIT_H_

#include <string>
#include <deque>
#include <mutex>

class ZoneTransit
{
	std::deque<std::string> buffer;
	std::mutex lock;

public:
	ZoneTransit();
	~ZoneTransit();

	//TODO: parametre par mouvement?
	void enqueue(std::string &&data)
	{
		//TODO faire la syncro
		//TODO enfiler par nouvement
		buffer.emplace_back(data);
	}

	//TODO: retour par mouvement?
	std::string deque()
	{
		std::string retVal;
		//TODO: faire la syncro
		buffer.emplace_front(retVal);
		buffer.pop_front();
		return retVal;
	}
};

#endif // !_ZONE_TRANSIT_H_

/*
#include <deque>
#include <mutex>
#include <string>
#include <condition_variable>

using namespace std;

class ZoneTransit
{
mutex mut;
condition_variable cv;

deque<string> data;

unique_lock<mutex> verrouiller() volatile
{
unique_lock<mutex> lock(const_cast<mutex&>(mut));
return lock;
}

public:

void put(string& content)
{
{
auto lock = verrouiller();
data.push_front(content);
}
cv.notify_one();
}

string get()
{
auto lock = verrouiller();
if (data.empty())
{
cv.wait(lock, [&](){ return !data.empty(); });
}
string s = move(data.back());
data.pop_back();

return s;
}
};
*/