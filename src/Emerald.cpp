#include "Emerald.h"
#include "FactoryStatic.h"

bool Emerald::m_registerit = FactoryStatic::registerit('E', [](const char c, const sf::Sprite& sprite) -> unique_ptr<StaticObject>
	{ return make_unique<Emerald>(c, sprite); });
int Emerald::m_emerald = 0;

Emerald::Emerald(const char c, const sf::Sprite& sprite)
	: StaticObjectVariable::StaticObjectVariable(c, sprite)
{
	++m_emerald;
}
//---------------------------
Emerald::~Emerald()
{
	--m_emerald;
}
//------------------------------------------------
//void Emerald::handleCollision(GameObject& gameObject)
//{
//	if (&gameObject == this) return;
//	gameObject.handleCollision(*this);
//}
////----------------------------------------
//void Emerald::handleCollision(Player& player)
//{
//	Sounds::instance().makeSound(RING);
//	m_isDisposed = true; // for delete
//	player.handleCollision(*this);
//}
////------------------------------------------
