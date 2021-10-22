#pragma once
#include "StaticObjectConst.h"

class Springboard : public StaticObjectConst
{
public:
	Springboard(const char c, const sf::Sprite& sprite);
	Springboard(const Springboard&) = default;
	Springboard& operator=(const Springboard&) = default;
	Springboard(Springboard&&) = default;
	Springboard& operator=(Springboard&&) = default;

private:
	static bool m_registerit;
};