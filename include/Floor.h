#pragma once
#include "StaticObjectConst.h"

class Floor : public StaticObjectConst
{
public:
	Floor(const char c, const sf::Sprite& sprite);
	Floor(const Floor&) = default;
	Floor& operator=(const Floor&) = default;
	Floor(Floor&&) = default;
	Floor& operator=(Floor&&) = default;
private:
	static bool m_registerit;
};