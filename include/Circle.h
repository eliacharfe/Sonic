#pragma once
#include "StaticObjectConst.h"

class Circle : public StaticObjectConst
{
public:
	Circle(const char c, const sf::Sprite& sprite);
	Circle(const Circle&) = default;
	Circle& operator=(const Circle&) = default;
	Circle(Circle&&) = default;
	Circle& operator=(Circle&&) = default;

private:
	static bool m_registerit;
};