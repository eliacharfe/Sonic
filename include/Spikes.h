#pragma once
#include "StaticObjectConst.h"
class Spikes : public StaticObjectConst
{
public:
	Spikes(const char c, const sf::Sprite& sprite);
	Spikes(const Spikes&) = default;
	Spikes& operator=(const Spikes&) = default;
	Spikes(Spikes&&) = default;
	Spikes& operator=(Spikes&&) = default;

private:
	static bool m_registerit;
};