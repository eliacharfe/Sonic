#include "Ring.h"
#include "FactoryStatic.h"

bool Ring::m_registerit = FactoryStatic::registerit('o', [](const char c, const sf::Sprite& sprite) -> unique_ptr<StaticObject>
	{ return make_unique<Ring>(c, sprite); });
int Ring::m_rings = 0;

Ring::Ring(const char c, const sf::Sprite& sprite)
	: StaticObjectVariable::StaticObjectVariable(c,sprite)
{
	++m_rings;
}
//------------------------------------
Ring::~Ring()
{
	--m_rings;
}
//------------------------------------------------
