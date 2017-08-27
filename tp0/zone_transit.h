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
#define _ZONE_TRANSIT_H_

#include <string>
#include <deque>
#include <mutex>
#include <condition_variable>

class ZoneTransit
{
	std::deque<std::string> buffer;
	std::mutex mut;
	std::condition_variable cv;

	bool done = false;
	std::unique_lock<std::mutex> acquire() volatile
	{
		std::unique_lock<std::mutex> token(const_cast<std::mutex&>(mut));
		return token;
	}

public:
	void enqueue(std::string &data)
	{
		{
			auto token = acquire();
			buffer.push_back(data);
		}
		cv.notify_one();
	}

	std::string deque()
	{
		auto token = acquire();

		if (buffer.empty())
		{
			cv.wait(token, [&]() {return !buffer.empty(); });
		}
		std::string retVal = std::move(buffer.front());
		buffer.pop_front();
		return retVal;
	}

	void terminate()
	{
		auto token = acquire();
		done = true;
	}

	bool is_done()
	{
		auto token = acquire();
		return done;
	}
};

#endif // !_ZONE_TRANSIT_H_