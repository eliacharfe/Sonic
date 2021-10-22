#pragma once
#include "StaticObjectVariable.h"

class Emerald : public StaticObjectVariable
{
public:
	Emerald(const char c, const sf::Sprite& sprite);
	Emerald(const Emerald&) = default;
	Emerald& operator=(const Emerald&) = default;
	Emerald(Emerald&&) = default;
	Emerald& operator=(Emerald&&) = default;
	~Emerald();

	static int getEmerald() { return m_emerald; }

private:
	static int m_emerald;
	static bool m_registerit;
};