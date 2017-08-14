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
#include <condition_variable>

class ZoneTransit
{
	std::deque<std::string> buffer;
	std::mutex token;
	std::condition_variable cv;

	std::unique_lock<std::mutex> acquire() volatile
	{
		return std::unique_lock<std::mutex>{const_cast<std::mutex&>(token)};
	}

public:
	ZoneTransit();
	~ZoneTransit();

	//TODO: parametre par mouvement?
	void enqueue(std::string &&data)
	{
		{
			auto token = acquire();
			buffer.emplace_back(data);
		}
		cv.notify_one();
	}

	std::string deque()
	{
		auto lock = acquire();

		if (buffer.empty())
		{
			cv.wait(lock, [&]() {return !buffer.empty(); });
		}
		std::string retVal = std::move(buffer.front());
		buffer.pop_front();
		return retVal;
	}
};

#endif // !_ZONE_TRANSIT_H_