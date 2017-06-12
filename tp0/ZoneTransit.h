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

#include <deque>

class ZoneTransit
{
	std::deque<std::string> buffer;

public:
	ZoneTransit();
	~ZoneTransit();
};

#endif // !_ZONE_TRANSIT_H_
