#include "Pole.h"
#include "FactoryStatic.h"

bool Pole::m_registerit = FactoryStatic::registerit('-', [](const char c, const sf::Sprite& sprite) -> unique_ptr<StaticObject>
	{ return make_unique<Pole>(c, sprite); });

Pole::Pole(const char c, const sf::Sprite& sprite)
	: StaticObjectConst::StaticObjectConst(c,sprite)
{
}
//------------------------------------------------