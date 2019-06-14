#pragma once
#include "include.h"
#include <math.h>

class Location
{
public:
	int x, y;
	Location(int x, int y);
	Location(Location*);
	void Set(int x, int y);
	void Set(Location*);
	bool IsSame(Location*);
	inline Real GetDistance(Location loc)
	{
		return sqrt(x * loc.x + y * loc.y);
	}
};