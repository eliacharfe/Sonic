#pragma once
#include "StaticObjectConst.h"

class Pole : public StaticObjectConst
{
public:
	Pole(const char c, const sf::Sprite& sprite);
	Pole(const Pole&) = default;
	Pole& operator=(const Pole&) = default;
	Pole(Pole&&) = default;
	Pole& operator=(Pole&&) = default;

private:
	static bool m_registerit;
};