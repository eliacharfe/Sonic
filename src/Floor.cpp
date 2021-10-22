#include "Floor.h"
#include "FactoryStatic.h"

bool Floor::m_registerit = FactoryStatic::registerit('F', [](const char c, const sf::Sprite& sprite) -> unique_ptr<StaticObject>
	{ return make_unique<Floor>(c, sprite); });

Floor::Floor(const char c, const sf::Sprite& sprite)
	: StaticObjectConst::StaticObjectConst(c,sprite)
{
}
//------------------------------------------------
