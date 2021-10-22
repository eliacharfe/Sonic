#include "Spikes.h"
#include "FactoryStatic.h"

bool Spikes::m_registerit = FactoryStatic::registerit('^', [](const char c, const sf::Sprite& sprite) -> unique_ptr<StaticObject>
	{ return make_unique<Spikes>(c, sprite); });

Spikes::Spikes(const char c, const sf::Sprite& sprite)
	: StaticObjectConst::StaticObjectConst(c,sprite)
{
}
//------------------------------------------------
