#include "Springboard.h"
#include "FactoryStatic.h"

bool Springboard::m_registerit = FactoryStatic::registerit('u', [](const char c, const sf::Sprite& sprite) -> unique_ptr<StaticObject>
	{ return make_unique<Springboard>(c, sprite); });

Springboard::Springboard(const char c, const sf::Sprite& sprite)
	: StaticObjectConst::StaticObjectConst(c,sprite)
{
}
//-----------------------------------------------
