#include "Location.h"

Location::Location(int x, int y)
{
	this->x = x;
	this->y = y;
}
Location::Location(Location* l)
{
	this->x = l->x;
	this->y = l->y;
}
void Location::Set(int a, int b)
{
	x = a;
	y = b;
}
void Location::Set(Location* loc)
{
	this->x = loc->x;
	this->y = loc->y;
}
bool Location::IsSame(Location* loc)
{
	return this->x == loc->x && this->y == loc->y;
}