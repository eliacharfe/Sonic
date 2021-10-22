#pragma once
#include "StaticObjectVariable.h"

class Ring : public StaticObjectVariable
{
public:
	Ring(const char c, const sf::Sprite& sprite);
	Ring(const Ring&) = default;
	Ring& operator=(const Ring&) = default;
	Ring(Ring&&) = default;
	Ring& operator=(Ring&&) = default;
	~Ring();

	static int getRings() { return m_rings; }

private:
	static int m_rings;
	static bool m_registerit;
};