#include "Wall.h"
#include "FactoryStatic.h"

bool Wall::m_registerit = FactoryStatic::registerit('#', [](const char c, const sf::Sprite& sprite) -> unique_ptr<StaticObject>
	{ return make_unique<Wall>(c,sprite); });

Wall::Wall(const char c, const sf::Sprite& sprite)
	: StaticObjectConst::StaticObjectConst(c,sprite)
{ }
//-----------------------------------------------







