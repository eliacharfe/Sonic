#pragma once
#include "StaticObject.h"

class StaticObjectConst : public StaticObject
{
public:
	StaticObjectConst(const char c, const sf::Sprite& sprite);
	StaticObjectConst(const StaticObjectConst&) = default;
	StaticObjectConst& operator=(const StaticObjectConst&) = default;
	StaticObjectConst(StaticObjectConst&&) = default;
	StaticObjectConst& operator=(StaticObjectConst&&) = default;

private:

};