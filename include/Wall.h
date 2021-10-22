#pragma once
#include "StaticObjectConst.h"

class Wall : public StaticObjectConst
{
public:
	Wall(const char c, const sf::Sprite& sprite);
	Wall(const Wall&) = default;
	Wall& operator=(const Wall&) = default;
	Wall(Wall&&) = default;
	Wall& operator=(Wall&&) = default;

private:
	static bool m_registerit;
};