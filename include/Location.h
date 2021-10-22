#pragma once
#include "Utilities.h"

class Location
{
public:
	Location(float x, float y);
	Location(const Location&) = default;
	Location& operator=(const Location&) = default;
	Location(Location&&) = default;
	Location& operator=(Location&&) = default;
	float _x;
	float _y;

private:
	
};

Location vecTotLocation(const sf::Vector2f& loc) ;
sf::Vector2f locationToVector(const Location& location) ;


