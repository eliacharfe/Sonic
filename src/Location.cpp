#include "Location.h"

Location::Location(float x = 0, float y = 0)
	: _x(x), _y(y)
{ }
//-----------------------------------------
Location vecTotLocation(const sf::Vector2f & loc) 
{
	return Location(loc.x, loc.y);
}
//--------------------------------------
sf::Vector2f locationToVector(const Location& location)
{
	return sf::Vector2f(move(location._x), move(location._y));
}
