#include "Circle.h"
#include "FactoryStatic.h"

bool Circle::m_registerit = FactoryStatic::registerit('O', [](const char c, const sf::Sprite& sprite) -> unique_ptr<StaticObject> 
	{ return make_unique<Circle>(c, sprite); });

Circle::Circle(const char c, const sf::Sprite& sprite)
	: StaticObjectConst::StaticObjectConst(c, sprite)
{
	m_sprite.setOrigin(RADIUS, RADIUS);
}
//--------------------------------------------------------
