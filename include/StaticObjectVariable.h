#pragma once
#include "StaticObject.h"

class StaticObjectVariable : public StaticObject
{
public:
	StaticObjectVariable(const char c, const sf::Sprite& sprite);
	StaticObjectVariable(const StaticObjectVariable&) = default;
	StaticObjectVariable& operator=(const StaticObjectVariable&) = default;
	StaticObjectVariable(StaticObjectVariable&&) = default;
	StaticObjectVariable& operator=(StaticObjectVariable&&) = default;

private:

};