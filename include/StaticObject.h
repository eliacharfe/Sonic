#pragma once
#include "GameObject.h"

class StaticObject : public GameObject
{
public:
	StaticObject(const char c, const sf::Sprite& sprite);
	StaticObject(const StaticObject&) = default;
	StaticObject& operator=(const StaticObject&) = default;
	StaticObject(StaticObject&&) = default;
	StaticObject& operator=(StaticObject&&) = default;

protected:

private:

};